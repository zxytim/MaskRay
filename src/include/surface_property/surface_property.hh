/*
 * $File: surface_property.hh
 * $Date: Tue Jun 18 22:40:46 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "ray.hh"
#include "material.hh"
#include "intersect_info.hh"
#include "intensity.hh"

class SurfaceProperty
{
	public:
		// Lambertian surface with no energy loss by default
		// bounce either reflect or refract rays (BSSRDF, but with the flaw of not emitting both of them)
		virtual void ray_bounce(const Ray &incident, const Vector &normal, 
				shared_ptr<Material> material,
				Vector &direction, real_t &energy);

		// no emisssion by default
		virtual Intensity get_emission(IntersectInfo &intersect_info);
};

class LambertianSurfaceProperty : public SurfaceProperty
{
};
/**
 * vim: syntax=cpp11 foldmethod=marker
 */

