/**
 * Header file for constants.
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

#include <math.h>

#ifndef _HPP_CONSTANTS
#define _HPP_CONSTANTS

namespace fr {

  namespace constants {
    const double pi = atan2(1.0, 1.0) * 4.0;
    const double secs_per_ut1_day = 86400.0;
    const double ut1_sideral_day_ratio = 1.002737811906;
  };

};

#endif
