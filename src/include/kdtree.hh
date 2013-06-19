/*
 * $File: kdtree.hh
 * $Date: Wed Jun 19 19:08:43 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

/**
 * methods that a primitive needs:
 *		
 */
template<Primitive>
class KDTree
{
	protected:
		struct AABB {
			real_t x[2], y[2], z[2];
		};
		struct Node
		{
			Node *ch[2];
			int split_dim;
			real_t split_coord;
		};

		Node *root;

	public:
		KDTree() {
			root = NULL;
		}

		void set_attribute(const string &attr, void *val);
		template<T>
			void build_tree(T elem) {
			}
};


/**
 * vim: syntax=cpp11 foldmethod=marker
 */

