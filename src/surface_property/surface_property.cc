/*
 * $File: surface_property.cc
 * $Date: Wed Jun 19 20:59:31 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "surface_property/surface_property.hh"
#include "emission_property/emission_property.hh"

#include "math.hh"

SurfaceProperty::SurfaceProperty(shared_ptr<EmissionProperty> emission_property) :
	emission_property(emission_property) {
		if (this->emission_property == nullptr)
			this->emission_property = shared_ptr<EmissionProperty>(new EmissionProperty());
	}
// Lambertian surface by default
Ray SurfaceProperty::ray_bounce(const Ray &incident, real_t dist, const Vector &normal, shared_ptr<Material> material)
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
