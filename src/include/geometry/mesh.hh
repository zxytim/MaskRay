/*
 * $File: mesh.hh
 * $Date: Wed Jun 19 22:17:58 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "geometry/geometry.hh"
#include <vector>
#include <cstring>

class Mesh;
class MeshIntersectInfo;


class Mesh : public Geometry
{
	public:
		Mesh();
		virtual bool is_finite() const {
			return true;
		}
		virtual std::shared_ptr<GeometryIntersectInfo> intersect(const Ray &ray);


		Mesh &translate(const Vector &delta);
		Mesh &translate(real_t dx, real_t dy, real_t dz);
		Mesh &scale(real_t ratio);
		Mesh &normalize(); // normalized mesh is at origin
		Mesh &to_origin();

	public:

		// all vectors are labeled from 1
		std::vector<Vector> v;
		std::vector<Vector> vn;
		std::vector<Vector2D> vt;

		struct Face
		{
			// -1 means none
			int v[3];
			int vn[3];
			int vt[3];
			Face(const std::vector<int> &v = std::vector<int>(),
					const std::vector<int> &vn = std::vector<int>(),
					const std::vector<int> &vt = std::vector<int>()) {
				memset(this, -1, sizeof(Face));
				for (size_t i = 0; i < v.size() && i < 3; i ++)
					this->v[i] = v[i];
				for (size_t i = 0; i < vn.size() && i < 3; i ++)
					this->vn[i] = vn[i];
				for (size_t i = 0; i < vt.size() && i < 3; i ++)
					this->vt[i] = vt[i];
			}
		};

		std::vector<Face> face;
};

class MeshIntersectInfo : public GeometryIntersectInfo
{
	public:
		virtual real_t get_dist() { return dist; }
		virtual Vector get_normal() { return normal; }

		real_t dist;
		Vector normal;
		Mesh::Face *face;
		Mesh *mesh;

		virtual ~MeshIntersectInfo(){}
};

Mesh *mesh_read_from_file(const std::string &fname);

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

