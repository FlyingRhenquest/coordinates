/**
 * xyz coordinates with a velocity component (dx, dy, dz)
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

#include "xyz_coordinate.hpp"
#include <Eigen/Core>

#ifndef _HPP_XYZ_VELOCITY
#define _HPP_XYZ_VELOCITY

namespace fr {

  namespace coordinates {

    class xyz_velocity : public xyz_coordinate {
    protected:      
      double dx, dy, dz;
    public:
      typedef xyz_coordinate super; // I kind of like implicit super in languages that support that...

      xyz_velocity(const double &x, const double &y, const double &z, const double &dx, const double &dy, const double &dz) : super(x,y,z), dx(dx), dy(dy), dz(dz) 
      {
      }

      xyz_velocity(const xyz_velocity &copy) : super(copy.get_x(), copy.get_y(), copy.get_z()), dx(copy.dx), dy(copy.dy), dz(copy.dz)
      {
      }

      // Initializes deltas to zero in this case

      xyz_velocity(const xyz_coordinate &copy) : super(copy.get_x(), copy.get_y(), copy.get_z()), dx(0.0), dy(0.0), dz(0.0)
      {
      }

      // Converting the other way will lose some information, but I'll just
      // assume you wanted to do that.

      virtual operator xyz_coordinate()
      {
	xyz_coordinate retval(x,y,z);
	return retval;
      }

      virtual ~xyz_velocity()
      {
      }

      double get_dx() const { return dx; }
      double get_dy() const { return dy; }
      double get_dz() const { return dz; }

      Eigen::Vector3d get_deltas() const
      {
	Eigen::Vector3d retval;
	retval << dx,dy,dz;
	return retval;
      }

      Eigen::Matrix<double,6,1> get_vector() const
      {
	Eigen::Matrix<double,6,1> retval;
	retval << x,y,z,dx,dy,dz;
	return retval;
      }

    };

  }
}

#endif
