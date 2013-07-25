/**
 *@file:   scene.cc
 *@date:   Sun Jun 23 20:22:20 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "scene.hh"


/**
 *@brief:     This function is used to add object to the scene.
 *@author:    Xinyu Zhou <zxytim[at]gmail[dot]com>
 *@date:      Sun Jun 23 20:22:20 2013 +0800
 *@param[in]  renderable : The object that need to be added .
 *@return:    a scene after add the object .
 * add the object into renderable , if the object is self-luminous object , add it into emissive_renderable.
 */
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

