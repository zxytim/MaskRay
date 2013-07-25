/**
 *@file:   surface_property/surface_property.hh
 *@date:   Thu Jun 27 03:36:10 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "ray.hh"
#include "material.hh"
#include "intersect_info.hh"
#include "intensity.hh"
#include "random.hh"
#include "emission_property/emission_property.hh"

/*
 * Surface Property may work together with TextureMapper to achieve
 * advanced visual effect, such as anisotropic surface reflection property, etc.
 *
 * ray_bounce is actually corresponds to BSSRDF.
 */

/**
 *@class   SurfaceProperty surface_property.h "src/include/surface_property/surface_property.hh"
 *@date:   Thu Jun 27 03:36:10 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 *
 * Surface Property may work together with TextureMapper to achieve
 * advanced visual effect, such as anisotropic surface reflection property, etc.
 *
 * ray_bounce is actually corresponds to BSSRDF.
 */

class SurfaceProperty
{
	public:

		SurfaceProperty(EmissionProperty * emission_property = nullptr);
		// Lambertian surface with no energy loss by default
		// bounce either reflect or refract rays (BSSRDF, but with the flaw of not emitting both of them)
		virtual Ray ray_bounce(const Ray &incident, real_t dist, const Vector &normal,
				Material * material);           ///< Get the reflect ray.


		// whether emissive
		virtual bool is_emissive() const {      ///< whether emissive.
			return false;
		}

		// no emisssion by default
		// emission can be heterogenous
		// @intersect_info is the ray shoot to this object
		virtual Intensity get_emission(IntersectInfo &intersect_info);      ///< no emisssion by default,emission can be heterogenous,intersect_info is the ray shoot to this object.

		EmissionProperty * emission_property;                               ///< emission property.

		virtual ~SurfaceProperty() {
			if (emission_property)
				delete emission_property;
		}

		Random random;
};

/**
 *@class   LambertianSurfaceProperty surface_property.h "src/include/surface_property/surface_property.hh"
 *@date:   Thu Jun 27 03:36:10 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 *
 *  Lambertian surface with no energy loss by default.
 */

class LambertianSurfaceProperty : public SurfaceProperty
{
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

