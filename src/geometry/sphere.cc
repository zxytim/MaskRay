/*
 * $File: sphere.cc
 * $Date: Wed Jun 19 16:14:47 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "geometry/sphere.hh"
#include "math.hh"

shared_ptr<GeometryIntersectInfo> Sphere::intersect(const Ray &ray)
{
	auto d = ray.o - this->o;
	real_t b = d.dot(ray.dir);
	real_t c = d.dot(d) - this->radius * this->radius;
	real_t dist2 = b * b - c;
	real_t dist = 0;
	if (dist2 > 0)
		dist = -b - sqrt(dist2);
	else 
		return nullptr;
	if (dist < 0)
		return nullptr;

	Vector normal = (ray.o + ray.dir * dist - this->o).normalize();
	return shared_ptr<GeometryIntersectInfo>(new SphereIntersectInfo(dist, normal));
}

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

