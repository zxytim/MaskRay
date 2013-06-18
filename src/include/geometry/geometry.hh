/*
 * $File: geometry.hh
 * $Date: Tue Jun 18 22:30:59 2013 +0800
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
};

class Geometry
{
	public:
		virtual bool is_finite() const {
			return false;
		}
		virtual std::shared_ptr<GeometryIntersectInfo> intersect(const Ray &ray) = 0;
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

