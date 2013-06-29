/*
 * $File: mono_glowing_lambertian_sp.hh
 * $Date: Sun Jun 23 22:33:40 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once
#include "surface_property/surface_property.hh"

class MonoGlowingLambertianSurfaceProperty : public SurfaceProperty
{
	public:
		
		MonoGlowingLambertianSurfaceProperty(const Intensity &emission) :
			emission(emission) {}
		bool is_emissive() const override { 
			return true;
		}
		Intensity get_emission(IntersectInfo &) override {
			return emission;
		}

		Intensity emission;
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

