/**
 * Six point version of ecef, with velocities. This doesn't inherit
 * from ecef because there's nothing actually unique in ecef.
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

#include "ecef.hpp"
#include "xyz_velocity.hpp"

#ifndef _HPP_ECEF_VEL
#define _HPP_ECEF_VEL

namespace fr {

  namespace coordinates {

    class ecef_vel : public xyz_velocity {
    public:
      typedef xyz_velocity super;

      ecef_vel(const double &x, const double &y, const double &z, const double &dx, const double &dy, const double &dz) : xyz_velocity(x,y,z,dx,dy,dz)
      {
      }

      ecef_vel(const ecef_vel &copy) : xyz_velocity(copy.x, copy.y, copy.z, copy.dx, copy.dy, copy.dz) 
      {
	
      }

      ecef_vel() : xyz_velocity(0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
      {
      }

      virtual ~ecef_vel()
      {
      }

    };

  }
}

#endif
