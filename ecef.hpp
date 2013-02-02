/**
 * Earth Centered Earth Fixed coordinates
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

#ifndef _HPP_ECEF
#define _HPP_ECEF

namespace fr {

  namespace coordinates {

    class ecef : public xyz_coordinate {

    public:
      typedef xyz_coordinate super;

      ecef(const double &x, const double &y, const double &z) : super(x,y,z)
      {
      }

      ecef(const ecef &copy) : super(copy.get_x(), copy.get_y(), copy.get_z())
      {
      }

      virtual ~ecef()
      {
      }

    };

  }

}

#endif
