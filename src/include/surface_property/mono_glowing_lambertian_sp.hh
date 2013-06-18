/*
 * $File: mono_glowing_lambertian_sp.hh
 * $Date: Wed Jun 19 02:31:37 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once
#include "surface_property/surface_property.hh"

class MonoGlowingLambertianSurfaceProperty : public SurfaceProperty
{
	public:
		
		MonoGlowingLambertianSurfaceProperty(const Intensity &intensity) :
			intensity(intensity) {}
		virtual Intensity get_emission(IntersectInfo &intersect_info) {
			return intensity;
		}

		Intensity intensity;
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

