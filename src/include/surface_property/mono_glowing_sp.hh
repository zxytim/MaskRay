/**
 *@file:   mono_glowing_sp.hh
 *@date:   Sun Jun 23 20:18:11 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once
#include "surface_property/surface_property.hh"

/**
 *@class   MonoGlowingSurfaceProperty mono_glowing_sp.hh "src/include/surface_property/mono_glowing_sp.h"
 *@date:   Sun Jun 23 20:18:11 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 *@brief:  This is emission surface.
 */

class MonoGlowingSurfaceProperty : public SurfaceProperty
{
	public:
		MonoGlowingSurfaceProperty(const Intensity &intensity = Intensity(1.0, 1.0, 1.0)) :
			intensity(intensity) {}

		virtual bool is_emissive() const override {                ///< whether emissive.
			return true;
		}

		virtual Intensity get_emission(IntersectInfo &) override { ///< return emission intensity.
			return intensity;
		}

		Intensity intensity;                                       ///< emission intensity.
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

