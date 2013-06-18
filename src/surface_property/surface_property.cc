/*
 * $File: surface_property.cc
 * $Date: Wed Jun 19 01:02:43 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "surface_property/surface_property.hh"

#include "math.hh"

// Lambertian surface by default
void SurfaceProperty::ray_bounce(const Ray &, const Vector &normal, shared_ptr<Material> , Vector &dir, real_t &energy)
{
	do {
		dir.x = rand_real() * 2.0 - 1.0;
		dir.y = rand_real() * 2.0 - 1.0;
		dir.z = rand_real() * 2.0 - 1.0;
	} while (dir.lengthsqr() > 1.0); // it is of no important using direct comparason between real numbers

	dir.to_normalized();

	if (dir.dot(normal) < 0.0)
		dir *= -1;

	energy = 1.0;
}

Intensity SurfaceProperty::get_emission(IntersectInfo &)
{
	return Intensity(0, 0, 0);
}

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

