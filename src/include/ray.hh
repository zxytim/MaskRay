/**
 *@file: ray.hh
 *@date: Wed Jun 19 14:41:57 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "vector.hh"
#include "material.hh"

/**
 *@class   Ray ray.hh "src/include/ray.hh"
 *@date:   Wed Jun 19 14:41:57 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 *@brief:  the class of ray.
 */

class Ray
{
	public:
		Vector o,   ///< stating point of the ray.
			   dir; ///< direction of the ray. it is need to assure that @dir is a unit vector

		real_t energy;  ///< energy of the ray( light ).

		Ray() : energy(1.0){}
		Ray(const Vector &o, const Vector &dir, real_t energy = 1.0) :
			o(o), dir(dir), energy(energy) {}

};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

