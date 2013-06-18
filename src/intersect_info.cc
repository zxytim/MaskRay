/*
 * $File: intersect_info.cc
 * $Date: Tue Jun 18 21:47:39 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "intersect_info.hh"
#include "renderable.hh"

#include <cmath>

real_t IntersectInfo::get_dist() {
	return intersect_info->get_dist();
}


Ray IntersectInfo::ray_bounce(const Ray &incident)
{
	Vector normal = intersect_info->get_normal();

	Vector direction;
	real_t energy;

	renderable->surface_property->ray_bounce(incident, normal, renderable->material, direction, energy);

	return Ray(incident.o + incident.dir * get_dist(), direction, energy);
}

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

