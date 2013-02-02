/**
 * Conversion routines. Convert from coordinate type to coordinate type
 * via from_type foo = converter<to_type>()(from_type bar)
 *
 * Copyright 2013 Bruce Ide
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

#include "coordinates.hpp"
#include <Eigen/Core>
#include <type_traits>

#ifndef _HPP_CONVERTS
#define _HPP_CONVERTS

namespace fr {

  namespace coordinates {

    template <typename convert_to>
    struct converter {

    };

    /***************************************************************
     * Put convert to lat_long bits here
     */

    template <>
    struct converter<lat_long> {
     
      // Converting from lat_long to lat_long is kind of odd, but I'll
      // cover the case anyway
      template <typename convert_from>
      typename std::enable_if<std::is_same<convert_from,lat_long>::value,lat_long>::type
	operator()(const convert_from &c)
      {
	return c;
      }

      // ECEF to Latlong
      template <typename convert_from>
      typename std::enable_if<std::is_same<convert_from,ecef>::value,lat_long>::type 
      operator()(const convert_from &xyz, const ellipsoid_parameters &e = WGS84_ELLIPSOID, double tolerance = 0.0000000001 )
      {
	double diff = 2 * tolerance;
	double t = e.ee * xyz.get_z();
	double n = 0.0;
	double nph = 0.0;
	double sinPhi = 0.0;
	double lat;
	double longitude;
	double alt;

	longitude = atan2(xyz.get_y(), xyz.get_x()) * 180 / fr::constants::pi;
	while(diff > tolerance) {
	  double zT = xyz.get_z() + t;
	  nph = sqrt(pow(xyz.get_x(), 2) + pow(xyz.get_y(), 2) + pow(zT, 2));
	  sinPhi = zT / nph;
	  n = e.ae / sqrt(1 - e.ee * sinPhi * sinPhi);
	  double told = t;
	  t = n * e.ee * sinPhi;
	  diff = fabs(t - told);
	}
	
	lat = asin(sinPhi) * 180 / fr::constants::pi;
	alt = nph - n;
	lat_long retval(lat, longitude, alt);
	return retval;
      }

      // ecef_vel to lat_long (Loses velocity information)
      
      template <typename convert_from>
      typename std::enable_if<std::is_same<convert_from,ecef_vel>::value,lat_long>::type
      operator()(const convert_from &c, const ellipsoid_parameters &e = WGS84_ELLIPSOID)
      {
	ecef interim = converter<ecef>()(c);
	lat_long retval = converter<lat_long>()(interim, e);
	return retval;
      }

      // tod_eci_vel to latlong (Loses velocity information)
      template <typename convert_from>
      typename std::enable_if<std::is_same<convert_from,tod_eci_vel>::value,lat_long>::type
      operator()(const convert_from &c, const double &t, const ellipsoid_parameters e = WGS84_ELLIPSOID)
      {
	// Convert from tod_eci to ecef_vel
	ecef_vel interim = converter<ecef_vel>()(c,t);
	// Then use the function before this one to convert to lat/long
	lat_long retval = converter<lat_long>()(interim, e);
	return retval;
      }
      
    };

    /*********************************************************
     * Put convert to ECEF bits here
     */

    template <>
    struct converter<ecef> {
      
      // ECEF to ECEF conversion. 
      template <typename convert_from>
      typename std::enable_if<std::is_same<convert_from,ecef>::value,ecef>::type
      operator()(const convert_from &c)
      {
	return c;
      }

      // latlong to ecef
      template <typename convert_from>
      typename std::enable_if<std::is_same<convert_from,lat_long>::value,ecef>::type
      operator()(const convert_from &c, const ellipsoid_parameters &e = WGS84_ELLIPSOID)
      {
	double x,y,z;
	const double &pi = fr::constants::pi;
	double slat = sin(c.get_lat() * pi / 180);
	double clat = cos(c.get_lat() * pi / 180);
	double slon = sin(c.get_long() * pi / 180);
	double clon = cos(c.get_long() * pi / 180);
	double n = e.ae / sqrt(1.0 - e.ee * pow(slat, 2));
	x = (n + c.get_alt()) * clat * clon;
	y = (n + c.get_alt()) * clat * slon;
	z = (n * (1.0 - e.ee) + c.get_alt()) * slat;
	ecef retval(x,y,z);
	return retval;
      }

      // ecef_vel to ecef (loses velocity information)
      template <typename convert_from>
      typename std::enable_if<std::is_same<convert_from,ecef_vel>::value,ecef>::type
      operator()(const convert_from &c)
      {
	ecef retval(c.get_x(), c.get_y(), c.get_z());
	return retval;
      }

      // tod_eci to ecef (Requires time coordinate was measured)
      template <typename convert_from>
      typename std::enable_if<std::is_same<convert_from,tod_eci>::value,ecef>::type
      operator()(const convert_from &c, const double &at_time)
      {
	eci_to_ecef conversion_matrix(at_time);
	Eigen::Vector3d c_vec = c.get_xyz();
	Eigen::Matrix3d c_mat = conversion_matrix.get();
	Eigen::Vector3d interim = c_mat * c_vec;
	ecef retval(interim(0), interim(1), interim(2));
	return retval;
      }
      
    };


    /**********************************************************
     * Put tod_eci stuff here
     */

    template<>
    struct converter<tod_eci> {
      
      // ECI to ECI conversion

      template <typename convert_from>
      typename std::enable_if<std::is_same<convert_from,tod_eci>::value,tod_eci>::type
      operator()(const convert_from &c)
      {
	return c;
      }

      // ecef to tod_eci (Requires time coordinate was measured)
      template <typename convert_from>
      typename std::enable_if<std::is_same<convert_from,ecef>::value,tod_eci>::type
      operator()(const convert_from &c, const double &time_at)
      {
	ecef_to_eci conversion_matrix(time_at);
	Eigen::Vector3d c_vec = c.get_xyz();
	Eigen::Matrix3d c_mat = conversion_matrix.get();
	Eigen::Vector3d interim = c_mat * c_vec;
	tod_eci retval(interim(0), interim(1), interim(2));
	return retval;
      }

    };

    /***************************************************************
     * Put ecef_vel stuff here
     */

    template<>
    struct converter<ecef_vel> {
      // ecef_vel to ecef_vel conversion
      template <typename convert_from>
      typename std::enable_if<std::is_same<convert_from,ecef_vel>::value,ecef_vel>::type
      operator()(const convert_from &c)
      {
	return c;
      }

      // tod_eci_vel to ecef_vel (requires time component)
      template <typename convert_from>
      typename std::enable_if<std::is_same<convert_from,tod_eci_vel>::value,ecef_vel>::type
      operator()(const convert_from &c, const double &time_at)
      {
	Eigen::Matrix<double,6,1> vec = c.get_vector();
	eci_to_ecef cm(time_at);
	Eigen::Matrix<double,6,6> c_mat = cm.get_xyz_vel();
	Eigen::Matrix<double,6,1> interim = c_mat * vec;
	ecef_vel retval(interim(0), interim(1), interim(2), interim(3), interim(4), interim(5));
	return retval;
      }      

    };

    /********************************************************************
     * Put tod_eci_vel stuff here
     */

    template<>
    struct converter<tod_eci_vel> {
      
      // From tod_eci_vel to tod_eci_vel
      template <typename convert_from>
      typename std::enable_if<std::is_same<convert_from,tod_eci_vel>::value,tod_eci_vel>::type
      operator()(const convert_from &c)
      {
	return c;
      }

      // from ecef_vel to tod_eci_vel
      template <typename convert_from>
      typename std::enable_if<std::is_same<convert_from,ecef_vel>::value,tod_eci_vel>::type
      operator()(const convert_from &c, const double &t)
      {
	ecef_to_eci cm(t);
	Eigen::Matrix<double,6,1> vec = c.get_vector();
	Eigen::Matrix<double,6,6> c_mat = cm.get_xyz_vel();
	Eigen::Matrix<double,6,1> interim = c_mat * vec;
	tod_eci_vel retval(interim(0), interim(1), interim(2), interim(3), interim(4), interim(5));
	return retval;			   
      }

    };
    
  }

}

#endif
