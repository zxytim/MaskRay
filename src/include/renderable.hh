/*
 * $File: renderable.hh
 * $Date: Wed Jun 19 21:36:32 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "geometry/geometry.hh"
#include "intersect_info.hh"
#include "surface_property/surface_property.hh"
#include "texture_mapper/texture_mapper.hh"
#include "material.hh"

#include <string>

class Renderable
{
	public:
		/*
		 * TODO:
		 *		Bouding Box
		 */

		std::string name;
		shared_ptr<Geometry> geometry;
		shared_ptr<SurfaceProperty> surface_property;
		shared_ptr<TextureMapper> texture_mapper;
		shared_ptr<Material> material;

		Renderable(std::string name, 
				shared_ptr<Geometry> geometry,
				shared_ptr<SurfaceProperty> surface_property,
				shared_ptr<TextureMapper> texture_mapper = nullptr,
				shared_ptr<Material> material = nullptr);

		Ray ray_bounce(const Ray &incident, const Ray &normal);
		shared_ptr<IntersectInfo> intersect(const Ray &ray);

};


/**
 * vim: syntax=cpp11 foldmethod=marker
 */
