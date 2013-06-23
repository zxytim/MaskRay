/*
 * $File: scene.cc
 * $Date: Sun Jun 23 20:22:20 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "scene.hh"

Scene &Scene::add_renderable(Renderable *renderable)
{
	this->renderable.push_back(renderable);
	if (renderable->is_emissive())
		this->emissive_renderable.push_back(renderable);
	return *this;
}

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

