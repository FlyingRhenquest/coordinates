/**
 * Tests conversion from coordinate to coordinate
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

#include <cppunit/extensions/HelperMacros.h>
#include "coordinates.hpp"
#include <iostream>
#include <iomanip>

class converter_test : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(converter_test);
  CPPUNIT_TEST(test_to_latlong);
  CPPUNIT_TEST(test_to_ecef);
  CPPUNIT_TEST(test_eci_to_ecef);
  CPPUNIT_TEST_SUITE_END();
public:
  
  void test_to_latlong()
  {
    fr::coordinates::lat_long denver(39.75, 104.87, 1609.344);
    fr::coordinates::lat_long also_denver = fr::coordinates::converter<fr::coordinates::lat_long>()(denver);
    fr::coordinates::ecef denver_ecef(-1260484.206487,4747249.668167,4057711.884932);
    fr::coordinates::lat_long denver2 = fr::coordinates::converter<fr::coordinates::lat_long>()(denver_ecef);
    CPPUNIT_ASSERT(denver.get_lat() == also_denver.get_lat());
    CPPUNIT_ASSERT(denver.get_long() == also_denver.get_long());
    CPPUNIT_ASSERT(denver.get_alt() == also_denver.get_alt());

    CPPUNIT_ASSERT(denver.get_lat() - denver2.get_lat() < .000001 );
    CPPUNIT_ASSERT(denver.get_long() - denver2.get_long() < .000001);
    CPPUNIT_ASSERT(denver.get_alt() - denver2.get_alt() < .000001);

    fr::coordinates::ecef_vel denver_vel(-1260484.206487,4747249.668167,4057711.884932,0.0,0.0,0.0); // Velocities get lost anyway
    fr::coordinates::lat_long denver3 = fr::coordinates::converter<fr::coordinates::lat_long>()(denver_vel);

    CPPUNIT_ASSERT(denver.get_lat() - denver3.get_lat() < .000001 );   
    CPPUNIT_ASSERT(denver.get_long() - denver3.get_long() < .000001);
    CPPUNIT_ASSERT(denver.get_alt() - denver3.get_alt() < .000001);

  }

  void test_to_ecef()
  {
    fr::coordinates::ecef denver_ecef(-1260484.206487,4747249.668167,4057711.884932);
    fr::coordinates::lat_long denver(39.75, 104.87, 1609.344);
    fr::coordinates::ecef also_denver_ecef = fr::coordinates::converter<fr::coordinates::ecef>()(denver_ecef);
    CPPUNIT_ASSERT(denver_ecef.get_x() == also_denver_ecef.get_x());
    CPPUNIT_ASSERT(denver_ecef.get_y() == also_denver_ecef.get_y());
    CPPUNIT_ASSERT(denver_ecef.get_z() == also_denver_ecef.get_z());
    fr::coordinates::ecef denver2_ecef = fr::coordinates::converter<fr::coordinates::ecef>()(denver);
    CPPUNIT_ASSERT(denver_ecef.get_x() - denver2_ecef.get_x() < .000001);
    CPPUNIT_ASSERT(denver_ecef.get_y() - denver2_ecef.get_y() < .000001); 
    CPPUNIT_ASSERT(denver_ecef.get_z() - denver2_ecef.get_z() < .000001);
   
    fr::coordinates::ecef_vel vel(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    fr::coordinates::ecef vel_less_vel = fr::coordinates::converter<fr::coordinates::ecef>()(vel);
    CPPUNIT_ASSERT(vel_less_vel.get_x() == vel.get_x());
    CPPUNIT_ASSERT(vel_less_vel.get_y() == vel.get_y());    
    CPPUNIT_ASSERT(vel_less_vel.get_z() == vel.get_z());
  }

  // TODO: Find some test values for eci to ecef. Right now
  // I'm just going to verify that I can rotate from ecef
  // to eci and then back to ecef and the numbers at the
  // end are the same as the numbers at the start.

  void test_eci_to_ecef()
  {
    fr::coordinates::ecef denver_ecef(-1260484.206487,4747249.668167,4057711.884932);
    fr::coordinates::tod_eci denver_eci = fr::coordinates::converter<fr::coordinates::tod_eci>()(denver_ecef,0.0);
    fr::coordinates::ecef denver2_ecef = fr::coordinates::converter<fr::coordinates::ecef>()(denver_eci,0.0);

    CPPUNIT_ASSERT(denver_ecef.get_x() - denver2_ecef.get_x() < .000001);
    CPPUNIT_ASSERT(denver_ecef.get_y() - denver2_ecef.get_y() < .000001);
    CPPUNIT_ASSERT(denver_ecef.get_z() - denver2_ecef.get_z() < .000001);
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(converter_test);
