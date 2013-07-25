/**
 *@file:   renderable.hh
 *@date:   Mon Jun 24 02:11:47 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 *@brief:  renderable is object.
 */

#pragma once

#include "geometry/geometry.hh"
#include "intersect_info.hh"
#include "surface_property/surface_property.hh"
#include "texture_mapper/texture_mapper.hh"
#include "material.hh"

#include <string>

/**
 *@class   Renderable renderable.hh "src/include/renderable.hh"
 *@brief:  renderable is abstract of object.
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 *@date:   Mon Jul 22 14:56:58 CST 2013
 */

class Renderable
{
	public:
		/*
		 * TODO:
		 *		Bouding Box
		 */

		std::string name;                                           ///< Name of the object.
		Geometry * geometry;                                        ///< Geometry of the object.
		SurfaceProperty * surface_property;                         ///< surface of the object.
		TextureMapper * texture_mapper;                             ///< texture mapper.
		Material * material;                                        ///< Material of the object.

		Renderable(std::string name,
				Geometry * geometry,
				SurfaceProperty * surface_property,
				TextureMapper * texture_mapper = nullptr,
				Material * material = nullptr);

		Ray ray_bounce(const Ray &incident, const Ray &normal);     ///< Get a reflect ray.

		IntersectInfo * intersect(const Ray &ray);                  ///< intersect with a ray.

        /**
         *@brief:   if the object is self-luminous object return true , else return false.
         */
		bool is_emissive() const {
			return surface_property->is_emissive();
		}

		int id;                                                     ///< this id is set by scene automatically

		~Renderable();
};


/**
 * vim: syntax=cpp11 foldmethod=marker
 */

