/*
 * $File: scene.cc
 * $Date: Mon Jun 17 19:40:50 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "scene.hh"

Scene &Scene::add_renderable(Renderable *renderable)
{
	this->renderable.push_back(renderable);
	return *this;
}

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

