/*
 * $File: ray.hh
 * $Date: Tue Jun 18 21:37:10 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "vector.hh"

class Ray
{
	public:
		Vector o,
			   dir; // it is need to assure that @dir is a unit vector

		real_t energy;

		Ray() {}
		Ray(const Vector &o, const Vector &dir, real_t energy = 1.0) :
			o(o), dir(dir), energy(energy) {}
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

