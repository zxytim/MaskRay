/*
 * $File: mono_glowing_sp.hh
 * $Date: Tue Jun 18 22:49:51 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once
#include "surface_property/surface_property.hh"

class MonoGlowingSurfaceProperty : public SurfaceProperty
{
	public:
		MonoGlowingSurfaceProperty(const Intensity &intensity = Intensity(1.0, 1.0, 1.0)) :
			intensity(intensity) {}

		virtual Intensity get_emission(IntersectInfo &) {
			return intensity;
		}

		Intensity intensity;
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

