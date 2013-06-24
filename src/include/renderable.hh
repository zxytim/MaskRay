/*
 * $File: renderable.hh
 * $Date: Mon Jun 24 02:11:47 2013 +0800
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
		Geometry * geometry;
		SurfaceProperty * surface_property;
		TextureMapper * texture_mapper;
		Material * material;

		Renderable(std::string name, 
				Geometry * geometry,
				SurfaceProperty * surface_property,
				TextureMapper * texture_mapper = nullptr,
				Material * material = nullptr);

		Ray ray_bounce(const Ray &incident, const Ray &normal);
		IntersectInfo * intersect(const Ray &ray);

		bool is_emissive() const {
			return surface_property->is_emissive();
		}

		int id; // this id is set by scene automatically

		~Renderable();
};


/**
 * vim: syntax=cpp11 foldmethod=marker
 */

