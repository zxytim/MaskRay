/*
 * $File: mesh.hh
 * $Date: Mon Jun 24 21:45:24 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "geometry/geometry.hh"
#include <vector>
#include <cstring>

#include "kdtree.hh"

class Mesh;
class MeshIntersectInfo;

struct MeshConf
{
	/**
	 * 0 disable
	 * 1 enable
	 * 2 auto
	 */
	int use_kdtree;

	MeshConf() : 
		use_kdtree(0)
	{}
};

class Mesh : public Geometry
{
	public:
		Mesh(const MeshConf &conf = MeshConf());
		virtual bool is_finite() const {
			return true;
		}
		virtual GeometryIntersectInfo * intersect(const Ray &ray);

		GeometryIntersectInfo *brute_force_intersect(const Ray &ray);
		GeometryIntersectInfo *kdtree_intersect(const Ray &ray);


		Mesh &translate(const Vector &delta);
		Mesh &translate(real_t dx, real_t dy, real_t dz);
		Mesh &scale(real_t ratio);
		Mesh &normalize(); // normalized mesh is at origin
		Mesh &rotate(int axis, real_t angle);
		Mesh &rotate_deg(int axis, real_t angle);
		Mesh &to_origin();

		/**
		 * IMPORTANT:
		 *		This method must be invoked if 
		 *		kdtree is enabled
		 */
		void finish();

		void build_kdtree();

	public:

		struct Face
		{
			// -1 means none
			int v[3];
			int vn[3];
			int vt[3];

			int id;

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
			Face(int *v, int *vn, int *vt) {
				memcpy(this->v, v, sizeof(this->v));
				memcpy(this->vt, vt, sizeof(this->vt));
				memcpy(this->vn, vn, sizeof(this->vn));
			}
		};

		// all vectors are labeled from 1
		std::vector<Vector> v;
		std::vector<Vector> vn;
		std::vector<Vector2D> vt;
		std::vector<Face> face;

		MeshConf conf;


		/**
		 * KDTree use
		 */
		class KDTreeFace : public Geometry {
			public:
				virtual GeometryIntersectInfo * intersect(const Ray &ray);
				virtual bool is_finite() const { return true; }
				virtual void get_shape(real_t *x, real_t *y, real_t *z);

				int id;
				Mesh *mesh;

		};
		KDTree *kdtree;
		friend class KDTree;

		GeometryIntersectInfo *face_intersect(int id, const Ray &ray);
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

