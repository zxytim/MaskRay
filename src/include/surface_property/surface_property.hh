/*
 * $File: surface_property.hh
 * $Date: Sun Jun 23 20:26:09 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "ray.hh"
#include "material.hh"
#include "intersect_info.hh"
#include "intensity.hh"
#include "emission_property/emission_property.hh"

/*
 * Surface Property may work together with TextureMapper to achieve
 * advanced visual effect, such as anisotropic surface reflection property, etc.
 *
 * ray_bounce is actually corresponds to BSSRDF.
 */
class SurfaceProperty
{
	public:

		SurfaceProperty(shared_ptr<EmissionProperty> emission_property = nullptr);
		// Lambertian surface with no energy loss by default
		// bounce either reflect or refract rays (BSSRDF, but with the flaw of not emitting both of them)
		virtual Ray ray_bounce(const Ray &incident, real_t dist, const Vector &normal, 
				shared_ptr<Material> material);


		// whether emissive
		virtual bool is_emissive() const {
			return false;
		}

		// no emisssion by default
		// emission can be heterogenous
		// @intersect_info is the ray shoot to this object
		virtual Intensity get_emission(IntersectInfo &intersect_info);

		shared_ptr<EmissionProperty> emission_property;
};

class LambertianSurfaceProperty : public SurfaceProperty
{
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

