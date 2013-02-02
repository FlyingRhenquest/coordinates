/**
 * Could really represent any coordinate that has X/Y/Z axises.
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
#include <Eigen/Geometry>

#ifndef _HPP_XYZ_COORDINATE
#define _HPP_XYZ_COORDINATE

namespace fr {

  namespace coordinates {

    class xyz_coordinate {
    protected:
      double x,y,z;

      inline double limit(double val, double lower, double upper)
      {
	assert(upper > lower);
	double retval = val;
	if (val > upper) {
	  retval = upper;
	} else if (val < lower) {
	  retval = lower;
	}
	return retval;
      }

      inline Eigen::Vector3d unit_vec(const Eigen::Vector3d &vec)
      {
	Eigen::Vector3d retval;
	double nrm = vec.norm();
	retval = vec / nrm;
	return retval;
      }

      // Generic interpolate between two points

      Eigen::Vector3d interpolate_3x3(const Eigen::Vector3d &this_vec, const double &time_now, const Eigen::Vector3d &next_vec, const double &time_other, const double &time_between)
      {
	Eigen::Quaternion<double> quat(1.0, 0.0, 0.0, 0.0);
	double this_norm = this_vec.norm();
	double next_norm = next_vec.norm();
	Eigen::Vector3d this_uv = unit_vec(this_vec);
	Eigen::Vector3d next_uv = unit_vec(next_vec);
	double x = this_uv.dot(next_uv);
	double y = limit(x,-1.0, 1.0);
	double theta = acos(y);
	double adjust = (time_between - time_now) / (time_other - time_now);
	double factor = ((next_norm - this_norm) * adjust + this_norm) / this_norm;
	theta = theta * adjust;
	double sto2 = sin(theta / 2.0);
	Eigen::Vector3d ax = next_vec.cross(this_vec);
	Eigen::Vector3d ax_uv = unit_vec(ax);
	double qx, qy, qz, qw;
	qx = ax_uv(0) * sto2;
	qy = ax_uv(1) * sto2;
	qz = ax_uv(2) * sto2;
	qw = cos(theta/2.0);
	quat = Eigen::Quaternion<double>(qw,qx,qy,qz);
	Eigen::Vector3d z = this_vec * factor;
	Eigen::Quaternion<double> z_q(0.0, z(0), z(1), z(2));
	Eigen::Quaternion<double> q1 = z_q * quat;
	Eigen::Quaternion<double> retaq = quat.inverse();
	Eigen::Quaternion<double> q2 = retaq * q1;
	return q2.vec();
      }

    public:
      xyz_coordinate(const double &x, const double &y, const double &z) : x(x), y(y), z(z) 
      {
      }

      xyz_coordinate(const xyz_coordinate &copy) : x(copy.get_x()), y(copy.get_y()), z(copy.get_z())
      {
      }

      // Ah ah, ah ha! Yep, I'm planning children classes!
      virtual ~xyz_coordinate()
      {
      }

      virtual double get_x() const { return x; }
      virtual double get_y() const { return y; }
      virtual double get_z() const { return z; }

      virtual Eigen::Vector3d get_xyz() const
      {
	Eigen::Vector3d retval;
	retval << x,y,z;
	return retval;
      }

    };

  }
}

#endif
