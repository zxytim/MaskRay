/**
 *@file: glass_sp.hh
 *@date: Thu Jun 27 03:36:18 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "surface_property/surface_property.hh"

/**
 *@class   GlassSurfaceProperty glass_sp.h "src/include/surface_property/glass_sp.hh"
 *@date:   Thu Jun 27 03:36:18 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 *@brief:  glass surface.
 */

class GlassSurfaceProperty : public SurfaceProperty
{
	public:
		GlassSurfaceProperty(real_t reflectance = 0.05) :
			reflectance(reflectance) {}
		virtual Ray ray_bounce(const Ray &incident, real_t dist, const Vector &normal,      ///< product a reflect ray.
				Material * material) override;

		real_t reflectance;                                                                 ///< reflect ratio.
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

