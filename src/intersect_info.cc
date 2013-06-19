/*
 * $File: intersect_info.cc
 * $Date: Wed Jun 19 13:50:27 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "intersect_info.hh"
#include "renderable.hh"

#include "math.hh"
#include <cassert>

real_t IntersectInfo::get_dist() {
	return intersect_info->get_dist();
}


Ray IntersectInfo::ray_bounce(const Ray &incident)
{
	assert(le(incident.dir.lengthsqr(), 1.0));
	return renderable->surface_property->ray_bounce(incident, 
			intersect_info->get_dist(), intersect_info->get_normal(),
			renderable->material);
}

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

