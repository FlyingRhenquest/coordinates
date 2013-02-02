/**
 * Latitude/Longitude coordinate. Optional altitude (Specified in meters
 * if you want to communicate it to Google Earth.)
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

#ifndef _HPP_LATLONG
#define _HPP_LATLONG

namespace fr {

  namespace coordinates {

    class lat_long {
      double latitude;
      double longitude;
      double altitude;

    public:


      lat_long(const double &latitude, const double &longitude, const double &altitude = 0.0) : latitude(latitude), longitude(longitude), altitude(altitude)
      {
      }

      lat_long(const lat_long &copy) : latitude(copy.latitude), longitude(copy.longitude), altitude(copy.altitude)
      {
      }

      lat_long() : latitude(0.0), longitude(0.0), altitude(0.0)
      {
      }

      ~lat_long()
      {
      }

      // I'm still trying to get over the java-ism of making accessors
      // for everything, but I want my coordinate classes to be const
      // once created.

      double get_lat() const
      {
	return latitude;
      }

      double get_long() const
      {
	return longitude;
      }

      double get_alt() const
      {
	return altitude;
      }
      
    };

  }
}

#endif
