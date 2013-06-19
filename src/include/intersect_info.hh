/*
 * $File: intersect_info.hh
 * $Date: Wed Jun 19 13:23:35 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "geometry/geometry.hh"
#include <memory>

class Renderable;
struct IntersectInfo
{
	shared_ptr<GeometryIntersectInfo> intersect_info; // get_dist, get_normal
	Renderable *renderable;
	real_t get_dist();
	
	// random by default, which is a Lambertian surface
	Ray ray_bounce(const Ray &incident);
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

