/*
 * $File: geometry.hh
 * $Date: Mon Jun 24 08:29:22 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "vector.hh"
#include "ray.hh"

#include <memory>

class GeometryIntersectInfo
{
	public:
		virtual real_t get_dist() = 0;
		virtual Vector get_normal() = 0;
		virtual ~GeometryIntersectInfo() {}
};

class Geometry
{
	public:
		virtual bool is_finite() const {
			return false;
		}
		virtual void get_shape(real_t *x, real_t *y, real_t *z);
		virtual GeometryIntersectInfo * intersect(const Ray &ray) = 0;
		virtual ~Geometry() {}
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

