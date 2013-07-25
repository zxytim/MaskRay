/**
 *@file:   geometry/sphere.hh
 *@date:   Tue Jun 18 22:38:09 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 *@brief:  sphere.
 */

#pragma once

#include "geometry.hh"

/**
 *@class   SphereIntersectInfo sphere.h "src/include/geometry/sphere.hh"
 *@brief:  This is sphere's intersect information.
 *@date:   Tue Jun 18 22:38:09 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

class SphereIntersectInfo : public GeometryIntersectInfo
{
	public:
		virtual real_t get_dist() override { return dist; }
		virtual Vector get_normal() override { return normal; }
		SphereIntersectInfo(const real_t &dist, const Vector &normal) :
			dist(dist), normal(normal) {}

	protected:
		real_t dist;
		Vector normal;
};

/**
 *@class   Sphere sphere.h "src/include/geometry/sphere.hh"
 *@brief:  This is sphere.
 *@date:   Tue Jun 18 22:38:09 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

class Sphere : public Geometry
{
	public:
		virtual GeometryIntersectInfo * intersect(const Ray &ray) override;

	public:
		Vector o;                                       ///< center of the sphere.
		real_t radius;                                  ///< radius of the sphere.
		Sphere(const Vector &o, real_t radius) :
			o(o), radius(radius) {}
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

