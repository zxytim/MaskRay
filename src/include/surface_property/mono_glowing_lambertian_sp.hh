/**
 *@file: mono_glowing_lambertian_sp.hh
 *@date: Sun Jun 23 22:33:40 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once
#include "surface_property/surface_property.hh"

/**
 *@class   MonoGlowingLambertianSurfaceProperty mono_glowing_lambertian_sp.hh "src/include/surface_property/mono_glowing_lambertian_sp.h"
 *@date:   Sun Jun 23 22:33:40 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 *@brief:  This is emission surface.
 */


class MonoGlowingLambertianSurfaceProperty : public SurfaceProperty
{
	public:

		MonoGlowingLambertianSurfaceProperty(const Intensity &emission) :
			emission(emission) {}
		virtual bool is_emissive() const override {                 ///< whether emissive.
			return true;
		}
		virtual Intensity get_emission(IntersectInfo &) override {  ///< return emission intensity.
			return emission;
		}

		Intensity emission;                                         ///< emission intensity.
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

