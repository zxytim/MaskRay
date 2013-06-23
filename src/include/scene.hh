/*
 * $File: scene.hh
 * $Date: Sun Jun 23 20:22:09 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "renderable.hh"
#include <vector>

class Scene
{
	public:
		Scene &add_renderable(Renderable* renderable);

		std::vector<Renderable *> renderable;

		// emissive objects, a subset of renderable
		std::vector<Renderable *> emissive_renderable; 
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

