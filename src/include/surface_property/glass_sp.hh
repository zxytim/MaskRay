/*
 * $File: glass_sp.hh
 * $Date: Thu Jun 27 03:36:18 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "surface_property/surface_property.hh"

class GlassSurfaceProperty : public SurfaceProperty
{
	public:
		GlassSurfaceProperty(real_t reflectance = 0.05) :
			reflectance(reflectance) {}
		Ray ray_bounce(const Ray &incident, real_t dist, const Vector &normal,
				Material * material) override;

		real_t reflectance;
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

