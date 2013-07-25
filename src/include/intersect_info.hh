/**
 *@file: intersect_info.hh
 *@date: Mon Jun 24 03:20:20 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "geometry/geometry.hh"
#include <memory>

class Renderable;

/**
 *@class   IntersectInfo intersect_info.hh "src/include/intersect_info.hh"
 *@date:   Mon Jun 24 03:20:20 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */
struct IntersectInfo
{
	GeometryIntersectInfo * intersect_info; // get_dist, get_normal
	Renderable *renderable;
	real_t get_dist();

	// random by default, which is a Lambertian surface
	Ray ray_bounce(const Ray &incident);

	virtual ~IntersectInfo();
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

