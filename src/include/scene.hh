/*
 * $File: scene.hh
 * $Date: Mon Jun 17 19:35:19 2013 +0800
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

};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

