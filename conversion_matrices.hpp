/**
 * ECI to ECEF conversion matrices
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
#include "gmst.hpp"

#ifndef _HPP_CONVERSION_MATRICES
#define _HPP_CONVERSION_MATRICES

namespace fr {

  namespace coordinates {

    // 6x6 population is the same for both classes, so may as well
    // only write it once.
    class ec_conversion_matrix_interface {
    public:
      ec_conversion_matrix_interface()
      {
      }

      virtual Eigen::Matrix3d get() = 0;
      virtual Eigen::Matrix3d get_dot() = 0;

      virtual Eigen::Matrix<double,6,6> get_xyz_vel()
      {
	Eigen::Matrix3d mat = get();
	Eigen::Matrix3d mat_dot = get_dot();
	Eigen::Matrix<double,6,6> retval;
	
	for (register int i = 0; i < 3; ++i) {
	  for (register int j = 0; j < 3; ++j) {
	    retval(i,j) = mat(i,j);
	    retval(i,j+3) = 0;
	    retval(i+3,j) = mat_dot(i,j);
	    retval(i+3,j+3) = mat(i,j);
	  }
	}
	return retval;
      }
    };

    /**
     * This class requires a time at which the coordinate was observed.
     */

    class eci_to_ecef : public ec_conversion_matrix_interface {
      double at_time;
      double gha_rad;
      double st,ct;
      double we;
      
    public:
      eci_to_ecef(const double &at_time) : at_time(at_time)
      {
	fr::time::gmst time_gmst(at_time);
	gha_rad = time_gmst.get_gmst() * 2.0 * fr::constants::pi / fr::constants::secs_per_ut1_day;
	st = sin(gha_rad);
	ct = cos(gha_rad);
	we = fr::constants::ut1_sideral_day_ratio * 2.0 * fr::constants::pi / fr::constants::secs_per_ut1_day;
      }

      ~eci_to_ecef()
      {
      }

      Eigen::Matrix3d get()
      {
	Eigen::Matrix3d retval;
	retval << ct,st,0.0,
	  -1.0 * st,ct,0.0,
	  0.0,0.0,1.0;
	return retval;
      }

      Eigen::Matrix3d get_dot()
      {
	Eigen::Matrix3d retval;
	retval << (-1.0 * we) * st, we * ct, 0.0,
	  (-1.0 * we) * ct, -we * st, 0.0,
	  0.0,0.0,0.0;
	return retval;
      }

    };

    // We can just transpose the eci to ecef matrix to get the ecef to
    // eci matrix

    class ecef_to_eci : public ec_conversion_matrix_interface {
      eci_to_ecef worker;
    public:
      ecef_to_eci(const double &at_time) : worker(at_time)
      {
      }

      ~ecef_to_eci()
      {
      }

      Eigen::Matrix3d get()
      {
	Eigen::Matrix3d interim = worker.get();
	Eigen::Matrix3d retval = interim.transpose();
	return retval;
      }

      Eigen::Matrix3d get_dot()
      {
	Eigen::Matrix3d retval = worker.get_dot().transpose();
	return retval;
      }
      
    };

  }

}


#endif
