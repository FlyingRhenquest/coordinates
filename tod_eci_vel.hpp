/**
 * tod_eci with velocity component
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

 */

#include <Eigen/Core>
#include <Eigen/Geometry>
#include "xyz_velocity.hpp"

#ifndef _HPP_TOD_ECI_VEL
#define _HPP_TOD_ECI_VEL

namespace fr {

  namespace coordinates {

    class tod_eci_vel : public xyz_velocity {

    public:
      typedef xyz_velocity super;

      tod_eci_vel(const double &x, const double &y, const double &z, const double &dx, const double &dy, const double &dz) : super(x,y,z,dx,dy,dz)
      {
      }

      tod_eci_vel(const tod_eci_vel &copy) : super(copy.get_x(), copy.get_y(), copy.get_z(), copy.get_dx(), copy.get_dy(), copy.get_dz())
      {
      }

      tod_eci_vel() : super(0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
      {
      }

      virtual ~tod_eci_vel()
      {
      }

      /**
       * Interpolates a point between two points. Takes a time observed
       * at the current point, another tod_eci_vel, time observed at that
       * point and the time in between for the point you want.
       */

      virtual tod_eci_vel interpolate(const double &time_now, const tod_eci_vel &next_point, const double &time_then, const double &time_between) 
      {
	Eigen::Vector3d xyz_now = get_xyz();
	Eigen::Vector3d xyz_then = next_point.get_xyz();
	Eigen::Vector3d vel_now = get_deltas();
	Eigen::Vector3d vel_then = next_point.get_deltas();
	Eigen::Vector3d xyz_between = interpolate_3x3(xyz_now, time_now, xyz_then, time_then, time_between);
	Eigen::Vector3d vel_between = interpolate_3x3(vel_now, time_now, vel_then, time_then, time_between);
	tod_eci_vel retval(xyz_between(0), xyz_between(1), xyz_between(2), vel_between(0), vel_between(1), vel_between(2));
	return retval;
      }

    };

  }

}

#endif
