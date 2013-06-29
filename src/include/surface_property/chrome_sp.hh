/*
 * $File: chrome_sp.hh
 * $Date: Wed Jun 19 13:25:04 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once
#include "surface_property/surface_property.hh"

class ChromeSurfaceProperty : public SurfaceProperty
{
	public:
		virtual Ray ray_bounce(const Ray &incident, real_t dist, const Vector &normal,
				Material * material) override;
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

