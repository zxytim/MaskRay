/**
 *@file:   chrome_sp.cc
 *@date:   Tue Jun 25 21:26:23 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "surface_property/chrome_sp.hh"
#include "math.hh"

#include <cassert>

/**
 *@brief:   get a reflect ray as the result of perfect specular reflection.
 *@date:   Tue Jun 25 21:26:23 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

Ray ChromeSurfaceProperty::ray_bounce(const Ray &incident, real_t dist, const Vector &normal,
		Material * ) {

	assert(le(normal.lengthsqr(), 1.0));
	assert(le(incident.dir.lengthsqr(), 1.0));
	Ray ray;

	ray.o = incident.o + incident.dir * dist;

	real_t length = incident.dir.dot(normal);
	ray.dir = incident.dir - normal * (length * 2);

	assert(eq(ray.dir.lengthsqr(), 1.0));
	assert(eq(incident.dir.dot(normal), -ray.dir.dot(normal)));

	return ray;
}

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

