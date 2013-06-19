/*
 * $File: glass_sp.hh
 * $Date: Wed Jun 19 15:05:56 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "surface_property/surface_property.hh"

class GlassSurfaceProperty : public SurfaceProperty
{
	public:
		GlassSurfaceProperty(real_t reflectance = 0.05) :
			reflectance(reflectance) {}
		virtual Ray ray_bounce(const Ray &incident, real_t dist, const Vector &normal, 
				shared_ptr<Material> material);

		real_t reflectance;
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

