/*
 * $File: mesh.hh
 * $Date: Wed Jun 19 20:09:11 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#if 0
#pragma once

#include "geometry/geometry.hh"
#include <vector>

class MeshIntersectInfo : public GeometryIntersectInfo
{
	public:
		virtual real_t get_dist() { return dist; }
		virtual Vector get_normal() { return normal; }

		real_t dist;
		Vector normal;
		Face *face;
		Mesh *mesh;
};

class Mesh : public Geometry
{
	public:
		virtual bool is_finite() const {
			return true;
		}
		virtual std::shared_ptr<GeometryIntersectInfo> intersect(const Ray &ray);

	protected:

		std::vector<Vector> v;
		std::vector<Vector> vn;
		std::vector<Vector> vt;

		struct Face
		{
			int v[3];
			int vn[3];
			int vt[3];
		};

		std::vector<Face> face;
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

#endif
