/*
 * $File: kdtree.cc
 * $Date: Mon Jun 24 21:34:14 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "kdtree.hh"

real_t *KDTree::AABB::get_data(int axis) {
	if (axis == 0)
		return x;
	if (axis == 1)
		return y;
	return z;
}

KDTree::AABB &KDTree::AABB::modify(int axis, int type, real_t val) {
	real_t *coord = get_data(axis);
	coord[type] = val;
	return *this;
}

real_t KDTree::AABB::intersect(const Ray &ray) {
#define SWAP(x, y) ({real_t _t_ = x; x = y; y = _t_; })
	real_t dx = 1.0 / ray.dir.x;

	real_t tx0 = (x[0] - ray.o.x) * dx,
		   tx1 = (x[1] - ray.o.x) * dx;
	if (tx0 > tx1) SWAP(tx0, tx1);

	real_t dy = 1.0 / ray.dir.y;
	real_t ty0 = (y[0] - ray.o.y) * dy,
		   ty1 = (y[1] - ray.o.y) * dy;
	if (ty0 > ty1) SWAP(ty0, ty1);

	if (tx0 > ty1 || ty0 > tx1)
		return -1;

	real_t t0 = (tx0 > ty0 ? tx0 : ty0),
		   t1 = (tx1 < ty1 ? tx1 : ty1);

	real_t dz = 1.0 / ray.dir.z;
	real_t tz0 = (z[0] - ray.o.z) * dz,
		   tz1 = (z[1] - ray.o.z) * dz;

	if (tz0 > tz1) SWAP(tz0, tz1);

	if (t0 > tz1 || tz0 > t1)
		return -1;

	t0 = (tz0 > t0 ? tz0 : t0);
	t1 = (tz1 < t1 ? tz1 : t1);

	return (t0 > 0 
			? (t1 > 0
				?  (t0 < t1 ? t0 : t1)
				: t0
			  ) 
			: (t1 > 0
				? t1
				: -1));
#undef SWAP
}

void KDTree::AABB::set_null() {
	x[0] = y[0] = z[0] = 1e100; //std::numeric_limits<real_t>::max();
	x[1] = y[1] = z[1] = -1e100; //std::numeric_limits<real_t>::min();
}


KDTree::AABB &KDTree::AABB::extend(const AABB &ab) {
	if (ab.x[0] < x[0]) x[0] = ab.x[0];
	if (ab.y[0] < y[0]) y[0] = ab.y[0];
	if (ab.z[0] < z[0]) z[0] = ab.z[0];
	if (ab.x[1] > x[1]) x[1] = ab.x[1];
	if (ab.y[1] > y[1]) y[1] = ab.y[1];
	if (ab.z[1] > z[1]) z[1] = ab.z[1];
	return *this;
}

KDTree::AABB::AABB(real_t *x, real_t *y, real_t *z) {
	memcpy(this->x, x, sizeof(this->x));
	memcpy(this->y, y, sizeof(this->y));
	memcpy(this->z, z, sizeof(this->z));
}

void KDTree::AABB::get_coord_range(int axis, real_t &min_coord, real_t &max_coord) const
{
	if (axis == 0)
		min_coord = x[0], max_coord = x[1];
	else if (axis == 1)
		min_coord = y[0], max_coord = y[1];
	else
		min_coord = z[0], max_coord = z[1];
}

real_t KDTree::AABB::get_coord_min(int axis)
{
	if (axis == 0)
		return x[0];
	else if (axis == 1)
		return y[0];
	else return z[0];
}

real_t KDTree::AABB::get_coord_max(int axis)
{
	if (axis == 0)
		return x[1];
	else if (axis == 1)
		return y[1];
	else return z[1];
}

bool KDTree::AABB::contains(const Vector &pos) const
{
	return x[0] - EPS < pos.x && pos.x < x[1] + EPS
		&& y[0] - EPS < pos.y && pos.y < y[1] + EPS
		&& z[0] - EPS < pos.z && pos.z < z[1] + EPS;
}


GeometryIntersectInfo *KDTree::Node::intersect(const Ray &ray)
{
	GeometryIntersectInfo *ret = nullptr;
	real_t dist = 1e100;
	assert(primitive.size() > 0);
	for (auto &g: primitive) {
		GeometryIntersectInfo *gii = g->intersect(ray);
		if (gii == nullptr)
			continue;
		real_t tdist = gii->get_dist();
		assert(tdist > 0);
		if (!this->aabb.contains(ray.o + ray.dir * tdist)) {
			delete gii;
			continue;
		}
		if (tdist < dist) {
			if (ret != nullptr)
				delete ret;
			dist = tdist;
			ret = gii;
		}
	}
	if (ret)
		int asdf = 0;
	return ret;
}

void KDTree::build_tree(std::vector<Geometry *> primitive)
{
	std::vector<AABB> aabb;
	for (size_t i = 0; i < primitive.size(); i ++) {
		Geometry *p = primitive[i];
		assert(p->is_finite());

		real_t x[2], y[2], z[2];
		p->get_shape(x, y, z);
		AABB ab = AABB(x, y, z);
		ab.id = i;
		aabb.push_back(ab);
	}
	this->primitive = primitive;
	root = do_build_tree(aabb, union_aabb(aabb), 0);
}

#include "geometry/mesh.hh"
void KDTree::Node::insepct() {
	printf("primitives: ");
	for (auto &p: primitive) {
		printf(" %d", ((Mesh::KDTreeFace *)p)->id);
	}
	printf("\n");
}


KDTree::AABB KDTree::union_aabb(std::vector<AABB> &aabb)
{
	AABB ab;
	ab.set_null();
	for (auto &i: aabb) ab.extend(i);
	return ab;
}

KDTree::Node *KDTree::do_build_tree(std::vector<AABB> &aabb, const AABB &tree_aabb, int depth)
{
	if (aabb.size() == 0)
		return nullptr;
	Node *root = new Node();
	root->aabb_ray_test = union_aabb(aabb);
	root->aabb = tree_aabb;
	if (aabb.size() < 5 || depth == 25) {
		for (auto &ab: aabb)
			root->primitive.push_back(primitive[ab.id]);
		//root->insepct();
		return root;
	}

	int axis_to_split = depth % 3;
	root->split_axis = axis_to_split;
	root->split_coord = 
		(root->aabb.get_coord_min(axis_to_split) +
		 root->aabb.get_coord_max(axis_to_split)) * 0.5;
	std::vector<AABB> left, right;
	for (auto &ab: aabb) {
		if (ab.get_coord_min(axis_to_split) < root->split_coord + EPS)
			left.push_back(ab);
		if (ab.get_coord_max(axis_to_split) > root->split_coord - EPS)
			right.push_back(ab);
	}

	AABB aabb_left = tree_aabb,
		 aabb_right = tree_aabb;
	aabb_left.modify(axis_to_split, 1, root->split_coord);
	aabb_right.modify(axis_to_split, 0, root->split_coord);
	root->ch[0] = do_build_tree(left, aabb_left, depth + 1);
	root->ch[1] = do_build_tree(right, aabb_right, depth + 1);
	return root;

#if 0
	std::vector<int> index(aabb.size());
	for (size_t i = 0; i < index.size(); i ++) index[i] = i;
	std::sort(index.begin(), index.end(), [&](int i, int j) -> bool {
			AABB &a = aabb[i], &b = aabb[j];
			int min_a = a.get_coord_min(axis_to_split),
			min_b = b.get_coord_min(axis_to_split);
			if (min_a != min_b) return min_a < min_b;
			return a.get_coord_max(axis_to_split)
			< b.get_coord_max(axis_to_split);
			});
#endif
}

GeometryIntersectInfo *KDTree::do_intersect(Node *root, const Ray &ray)
{
	if (root->is_leaf())
		return root->intersect(ray);

	struct Child {
		Node *ch;
		real_t dist;
	} chd[2];
	int nchd = 0;
	for (int i = 0; i < 2; i ++ ) {
		if (!root->ch[i])
			continue;
		real_t d = root->ch[i]->aabb.intersect(ray);
		if (d < EPS)
			continue;
		chd[nchd].ch = root->ch[i];
		chd[nchd].dist = d;
		nchd ++;
	}
	if (!nchd)
		return nullptr;

	if (nchd == 2) {
		if (chd[0].dist > chd[1].dist)
			std::swap(chd[0], chd[1]);
		else if (fabs(chd[0].dist - chd[1].dist) < EPS) {
			if (root->ch[1]->aabb.contains(ray.o))
				std::swap(chd[0], chd[1]);
		}
	}

	for (int i = 0; i < nchd; i ++) {
		GeometryIntersectInfo *gii = do_intersect(chd[i].ch, ray);
		if (gii != nullptr)
			return gii;
	}
	return nullptr;
}

GeometryIntersectInfo *KDTree::intersect(const Ray &ray)
{
	return do_intersect(root, ray);
}

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

