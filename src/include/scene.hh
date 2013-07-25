/**
 *@file:   scene.hh
 *@date:   Sun Jun 23 20:22:09 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 *@brief:  This file is used to declare the class named Scene
 */

#pragma once

#include "renderable.hh"
#include <vector>

/**
 *@class:  Scene scene.hh "src/include/scene.hh"
 *@brief:  Scene is the container of objects
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 *@date:   Sun Jul 21 16:33:59 CST 2013
 */

class Scene
{
	public:
		Scene &add_renderable(Renderable* renderable);  ///< This function is used to add object to the scene.

		std::vector<Renderable *> renderable;           ///< renderable is a container of all objects.

		// emissive objects, a subset of renderable
		std::vector<Renderable *> emissive_renderable;  ///< emissive_renderable is a container of self-luminous objects, which is not used in path-tracing model but MLT model( not achieve yet ) , a subset of renderable.
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

