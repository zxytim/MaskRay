/**
 *@file: vector.hh
 *@date: Mon Jun 24 04:07:25 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "type.hh"
#include <xmmintrin.h>

#include <cmath>

/**
 *@class   Vector vector.hh "src/include/vector.hh"
 *@date:   Mon Jun 24 04:07:25 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 *@brief:  Vector is vector or point, this class define some operation.
 */

class Vector
{
	public:
		real_t x, y, z;
		Vector(){}
		Vector(real_t x, real_t y, real_t z) :
			x(x), y(y), z(z) {}
		inline Vector operator - (const Vector &v) const {
			return Vector(x - v.x, y - v.y, z - v.z);
		}
		inline Vector operator - () const {
			return *this * (-1);
		}
		inline Vector operator -= (const Vector &v) {
			x -= v.x;
		   	y -= v.y;
		   	z -= v.z;
			return *this;
		}
		inline Vector operator + (const Vector &v) const {
			return Vector(x + v.x, y + v.y, z + v.z);
		}
		inline Vector& operator += (const Vector &v) {
			x += v.x;
		   	y += v.y;
		   	z += v.z;
			return *this;
		}
		inline Vector operator * (real_t ratio) const {
			return Vector(x * ratio, y * ratio, z * ratio);
		}

		inline Vector operator / (real_t _ratio) const {
			register real_t ratio = 1.0 / _ratio;
			return Vector(x * ratio, y * ratio, z * ratio);
		}

		inline Vector& operator /= (real_t _ratio) {
			register real_t ratio = 1.0 / _ratio;
			x *= ratio;
			y *= ratio;
			z *= ratio;
			return *this;
		}

		inline Vector& operator *= (real_t ratio) {
			x *= ratio;
			y *= ratio;
			z *= ratio;
			return *this;
		}
		inline real_t dot(const Vector &v) const {
			return x * v.x + y * v.y + z * v.z;
		}
		inline Vector cross(const Vector &v) const {
			return Vector(y * v.z - z * v.y,
					z * v.x - x * v.z,
					x * v.y - y * v.x);
		}

		inline Vector normalize() const {
			return *this / length();
		}

		inline Vector& to_normalized() {
			*this /= length();
			return *this;
		}

		inline Vector length_of(real_t len) const {
			return *this / length() * len;
		}

		inline Vector &to_length(real_t len) {
			*this *= len / length();
			return *this;
		}

		inline real_t length() const {
			return sqrt(x * x + y * y + z * z);
		}

		inline real_t lengthsqr() const {
			return x * x + y * y + z * z;
		}
};

inline Vector operator * (real_t ratio, const Vector &v) {
	return v * ratio;
}


// TODO: use real 2D Vector
class Vector2D : public Vector
{
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

