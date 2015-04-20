/**
 * Returns bearing angle in degrees given two lat-longs.
 *
 * Copyright 2015 Bruce Ide
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

#ifndef _HPP_BEARING
#define _HPP_BEARING

#include "lat_long.hpp"
#include "constants.hpp"
#include <cmath>

namespace fr {

  namespace coordinates {

    class bearing {

    public:      

      double operator()(const lat_long &p1, const lat_long &p2)
      {
	double p1r = p1.get_lat() * fr::constants::pi / 180.0;
	double p2r = p2.get_lat() * fr::constants::pi / 180.0;
	double l1r = p1.get_long() * fr::constants::pi / 180.0;
	double l2r = p2.get_long() * fr::constants::pi / 180.0;
	double dlon = (p2.get_long() - p1.get_long()) * fr::constants::pi / 180.0;
	double y =- sin(l2r - l1r) * cos(p2r);
	double x = cos(p1r) * sin(p2r) - sin(p1r) * cos(p2r) * cos(l2r - l1r);
	double bearing = atan2(y, x) * 180.0 / fr::constants::pi;
	bearing += 360.0;
	bearing = fmod(bearing, 360.0);
	return bearing;
      }

    };

  }

}

#endif
