/*
 * $File: surface_property.cc
 * $Date: Tue Jun 25 21:25:48 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "surface_property/surface_property.hh"
#include "emission_property/emission_property.hh"

#include "math.hh"

SurfaceProperty::SurfaceProperty(EmissionProperty * emission_property) :
	emission_property(emission_property) {
		if (this->emission_property == nullptr)
			this->emission_property = new EmissionProperty();
	}
// Lambertian surface by default
Ray SurfaceProperty::ray_bounce(const Ray &incident, real_t dist, const Vector &normal, Material *)
{
	Ray ray;
	Vector &dir = ray.dir;
	do {
		dir.x = rand_real() * 2.0 - 1.0;
		dir.y = rand_real() * 2.0 - 1.0;
		dir.z = rand_real() * 2.0 - 1.0;
	} while (dir.lengthsqr() > 1.0); // it is of no important using direct comparason between real numbers

	dir.to_normalized();

	if (dir.dot(normal) < 0.0)
		dir *= -1;

	ray.energy = 1.0;
	ray.o = incident.o + incident.dir * dist;
	
	return ray;
}

Intensity SurfaceProperty::get_emission(IntersectInfo &intersect_info)
{
	return emission_property->get_emission(intersect_info);
}

/**
 * vim: syntax=cpp11 foldmethod=marker
 */
