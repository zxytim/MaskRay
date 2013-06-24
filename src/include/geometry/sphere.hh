/*
 * $File: sphere.hh
 * $Date: Tue Jun 18 22:38:09 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "geometry.hh"

class SphereIntersectInfo : public GeometryIntersectInfo
{
	public:
		virtual real_t get_dist() { return dist; }
		virtual Vector get_normal() { return normal; }
		SphereIntersectInfo(const real_t &dist, const Vector &normal) :
			dist(dist), normal(normal) {}

	protected:
		real_t dist;
		Vector normal;
};

class Sphere : public Geometry
{
	public:
		virtual GeometryIntersectInfo * intersect(const Ray &ray);

	public:
		Vector o;
		real_t radius;
		Sphere(const Vector &o, real_t radius) :
			o(o), radius(radius) {}
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

