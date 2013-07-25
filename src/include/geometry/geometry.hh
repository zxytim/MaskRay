/**
 *@file:   geometry/geometry.hh
 *@date:   Mon Jun 24 08:29:22 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 *@brief:  Geometry of objects and Geometry Intersect Information.
 */

#pragma once

#include "vector.hh"
#include "ray.hh"

#include <memory>

/**
 *@class   GeometryIntersectInfo geometry.hh "src/include/geometry/geometry.hh"
 *@brief:  This class contain intersect information, this is a base class.
 *@date:   Mon Jun 24 08:29:22 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

class GeometryIntersectInfo
{
	public:
		virtual real_t get_dist() = 0;          ///< get distance between camera and the object.
		virtual Vector get_normal() = 0;        ///< get normal vector of the collision point.
		virtual ~GeometryIntersectInfo() {}
};

/**
 *@class    Geometry geometry.hh "src/include/geometry/geometry.hh"
 *@brief:   This class is geometry of objects , this is base class.
 *@date:   Mon Jun 24 08:29:22 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

class Geometry
{
	public:
		virtual bool is_finite() const {
			return false;
		}
		virtual void get_shape(real_t *x, real_t *y, real_t *z);
		virtual GeometryIntersectInfo * intersect(const Ray &ray) = 0;  ///< get intersect information.
		virtual ~Geometry() {}
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

