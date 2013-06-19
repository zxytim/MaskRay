/*
 * $File: ray.hh
 * $Date: Wed Jun 19 14:41:57 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "vector.hh"
#include "material.hh"

class Ray
{
	public:
		Vector o,
			   dir; // it is need to assure that @dir is a unit vector

		real_t energy;

		Ray() : energy(1.0){}
		Ray(const Vector &o, const Vector &dir, real_t energy = 1.0) :
			o(o), dir(dir), energy(energy) {}

};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

