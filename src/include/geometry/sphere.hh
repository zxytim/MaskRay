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
		real_t get_dist() override { return dist; }
		Vector get_normal() override { return normal; }
		SphereIntersectInfo(const real_t &dist, const Vector &normal) :
			dist(dist), normal(normal) {}

	protected:
		real_t dist;
		Vector normal;
};

class Sphere : public Geometry
{
	public:
		GeometryIntersectInfo * intersect(const Ray &ray) override;

	public:
		Vector o;
		real_t radius;
		Sphere(const Vector &o, real_t radius) :
			o(o), radius(radius) {}
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

