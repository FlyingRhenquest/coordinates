/**
 * True-of-date ECI coordinates. This is just another xyz coordinate.
 * Most of the magic happens in converts.hpp and conversion_matrices.hpp
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
#include "xyz_coordinate.hpp"

#ifndef _HPP_TOD_ECI
#define _HPP_TOD_ECI

namespace fr {

  namespace coordinates {

    class tod_eci : public xyz_coordinate {

    public:
      typedef xyz_coordinate super;
      tod_eci(const double &x, const double &y, const double &z) : super(x,y,z)
      {
      }

      tod_eci(const tod_eci &copy) : super(copy.get_x(), copy.get_y(), copy.get_z())
      {
      }

      virtual ~tod_eci()
      {
      }

      /**
       * Interpolate between two points. Takes time observed at the current
       * point, another tod_eci and the time observed at that point,
       * and a time between the two points.
       */

      virtual tod_eci interpolate(const double &time_now, const tod_eci &next_point, const double &time_then, const double &time_between)
      {
	Eigen::Vector3d vec_now = get_xyz();
	Eigen::Vector3d next_vec = next_point.get_xyz();
	Eigen::Vector3d interim = interpolate_3x3(vec_now, time_now, next_vec, time_then, time_between);
	tod_eci retval(interim(0), interim(1), interim(2));
	return retval;
      }

    };

  }
}

#endif
