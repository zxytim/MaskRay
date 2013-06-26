/*
 * $File: kdtree.hh
 * $Date: Wed Jun 26 23:35:21 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include <vector>
#include <limits>
#include <cstring>
#include <algorithm>
#include <cassert>
#include "math.hh"
#include "geometry/geometry.hh"


/**
 * used for ray-to-primitive intersection test
 * methods that a primitive needs:
 *
 *		// each of the parameter is a int array of length 2
 *		void get_shape(real_t *x, real_t *y, real_t *z); 
 *
 *		IntersectInfo *intersect(const Ray &ray);
 *		
 */
class KDTree
{
	protected:
		static constexpr real_t REAL_T_MAX = std::numeric_limits<real_t>::max();
		struct AABB {
			real_t x[2], y[2], z[2];
			int id;
			// negative means no intersection
			real_t intersect(const Ray &ray);

			void set_null();
			AABB &extend(const AABB &ab);
			AABB &intersect(const AABB &ab);
			AABB() {}
			AABB(real_t *x, real_t *y, real_t *z);

			void get_coord_range(int axis, real_t &min_coord, real_t &max_coord) const;
			real_t get_coord_min(int axis);
			real_t get_coord_max(int axis);

			bool contains(const Vector &pos) const;

			AABB &modify(int axis, int type, real_t val);

			// helper
			real_t *get_data(int axis);
		};
		struct Node
		{
			Node *ch[2];
			int split_axis;
			real_t split_coord;
			AABB aabb; // AABB that partitioned the space
			AABB aabb_ray_test; // = merge_aabb(primtive.aabb) \intersect this->aabb
			Node() {ch[0] = ch[1] = nullptr;}
			std::vector<Geometry *> primitive;
			bool is_leaf() const { return ch[0] == nullptr && ch[1] == nullptr; }
			GeometryIntersectInfo *intersect(const Ray &ray); 

			void insepct();
		};

		Node *root;

	public:
		KDTree() {
			root = NULL;
		}
		virtual ~KDTree() {}

		void build_tree(std::vector<Geometry *> primitive);

	protected:

		static AABB merge_aabb(std::vector<AABB> &aabb);

		std::vector<Geometry *> primitive;
		Node *do_build_tree(std::vector<AABB> &aabb, const AABB &tree_aabb, int depth); 

		GeometryIntersectInfo *do_intersect(Node *root, const Ray &ray); 
		
	public:

		virtual GeometryIntersectInfo *intersect(const Ray &ray); 
};


/**
 * vim: syntax=cpp11 foldmethod=marker
 */

