/*
 * $File: glass_sp.cc
 * $Date: Thu Jun 27 03:35:36 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "surface_property/glass_sp.hh"

#include "math.hh"
#include <cassert>

Ray GlassSurfaceProperty::ray_bounce(const Ray &incident, real_t dist, const Vector &normal, 
		Material * material)
{
	assert(eq(incident.dir.lengthsqr(), 1.0));
	assert(eq(normal.lengthsqr(), 1.0));

	assert(lt0(incident.dir.dot(normal)));

	real_t cos_i = -incident.dir.dot(normal);
	assert(le(cos_i, 1.0) && gt(cos_i, 0.0));

	real_t rindex_in,
		   rindex_out;

	Ray ray;
	ray.o = incident.o + incident.dir * dist;
	ray.energy = 1.0;

	if (le(cos_i, 0.0)) {
		rindex_in = material->refractive_index;
		rindex_out = 1.0;
	} else {
		rindex_in = 1.0;
		rindex_out = material->refractive_index;
	}

	real_t delta = 1 - rindex_in * rindex_in * (1 - cos_i * cos_i) / (rindex_out * rindex_out);
	
	// no refract
	if (false && delta < 0)
		ray.dir = incident.dir + normal * (cos_i * 2.0); // reflect
	else {
		real_t cos_t = sqrt(delta);
		real_t rs = (rindex_in * cos_i - rindex_out * cos_t)
			/ (rindex_in * cos_i + rindex_out * cos_t);
		real_t rp = (rindex_out * cos_i - rindex_in * cos_t)
			/ (rindex_out * cos_i + rindex_in * cos_t);

		real_t reflection = rs * rs + rp * rp;
		// reflection
		if (random.rand_real() < reflection + this->reflectance)
			ray.dir = incident.dir + normal * (cos_i * 2.0);
		else {
			// refract
			assert(le(fabs(cos_t), 1.0));
			real_t ratio = rindex_in / rindex_out;
			ray.dir = incident.dir * ratio  + normal * (ratio * cos_i - cos_t);

			assert(gt(ray.dir.dot(incident.dir), 0));
			//ray.dir = (incident.dir + normal * cos_i) * ratio - normal * cos_t;
			//ray.dir.to_normalized();
		}
	}

	assert(eq(ray.dir.lengthsqr(), 1.0));
	return ray;
}

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

