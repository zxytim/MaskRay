/*
 * $File: sphere.cc
 * $Date: Tue Jun 18 22:33:33 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "geometry/sphere.hh"
#include "math.hh"

shared_ptr<GeometryIntersectInfo> Sphere::intersect(const Ray &ray)
{
	Vector e = this->o - ray.o;
	real_t a = e.dot(ray.dir);
	real_t c2 = e.lengthsqr();
	
	real_t b2 = c2 - a * a;
	real_t r2 = this->radius * radius;
	
	real_t f2 = r2 - b2;
	if (lt0(f2))
		return nullptr;

	return shared_ptr<GeometryIntersectInfo>(new SphereIntersectInfo(a - sqrt(f2), e * (-1)));
}


/**
 * vim: syntax=cpp11 foldmethod=marker
 */

