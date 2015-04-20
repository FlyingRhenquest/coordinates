/**
 * Computes the distance between two lat/lon coordinates. Does not take
 * into account altitude. This object doesn't care what the units are.
 * Whatever units you start with for the radius of the earth will be
 * the units that get used. For fr.coordinates.WGS84_ELLIPSOID.ae,
 * it will be in meters.
 *
 * I could just do this as a function, but then you have to remember to
 * link the library in if you ever use it, which generally speaking is
 * kind of a pain in the ass.
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

#ifndef _HPP_HAVERSINE_DISTANCE
#define _HPP_HAVERSINE_DISTANCE

#include "ellipsoid.hpp"
#include "lat_long.hpp"
#include "constants.hpp"
#include <cmath>

namespace fr {

  namespace coordinates {

    class haversine_distance {

      double earth_radius;
      
    public:

      // Default to meters

      haversine_distance(double earth_radius = WGS84_ELLIPSOID.ae) : earth_radius(earth_radius)
      {
      }

      double distance(const lat_long &p1, const lat_long &p2)
      {
	double p1r = p1.get_lat() * fr::constants::pi / 180.0;
	double p2r = p2.get_lat() * fr::constants::pi / 180.0;
	double dlat = (p2.get_lat() - p1.get_lat()) * fr::constants::pi / 180.0;
	double dlon = (p2.get_long() - p1.get_long()) * fr::constants::pi / 180.0;
	double a = sin(dlat/2.0) * sin(dlat / 2.0) + cos(p1r) * cos(p2r) * sin(dlon / 2.0) * sin(dlon / 2.0);
	double c = 2 * atan2(sqrt(a), sqrt(1.0 - a));
	return earth_radius * c;	
      }

    };

  }

}

#endif
