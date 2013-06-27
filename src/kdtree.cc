/*
 * $File: kdtree.cc
 * $Date: Thu Jun 27 12:33:50 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "kdtree.hh"
#include "util.hh"

#include <iostream>

using namespace std;

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

KDTree::AABB &KDTree::AABB::intersect(const AABB &ab) {
	if (ab.x[0] > x[0]) x[0] = ab.x[0];
	if (ab.y[0] > y[0]) y[0] = ab.y[0];
	if (ab.z[0] > z[0]) z[0] = ab.z[0];
	if (ab.x[1] < x[1]) x[1] = ab.x[1];
	if (ab.y[1] < y[1]) y[1] = ab.y[1];
	if (ab.z[1] < z[1]) z[1] = ab.z[1];
	assert(x[0] < x[1] + EPS);
	assert(y[0] < y[1] + EPS);
	assert(z[0] < z[1] + EPS);
	if (x[0] < x[1]) x[0] = x[1];
	if (y[0] < y[1]) y[0] = y[1];
	if (z[0] < z[1]) z[0] = z[1];
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

real_t KDTree::AABB::get_coord_min(int axis) const
{
	if (axis == 0)
		return x[0];
	else if (axis == 1)
		return y[0];
	else return z[0];
}

real_t KDTree::AABB::get_coord_max(int axis) const
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
	return ret;
}

void KDTree::build_tree(std::vector<Geometry *> primitive)
{
	printf("start building kd-tree ...\n"); fflush(stdout);
	free_node(root);
	long long start_time = get_time();
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
		root = do_build_tree(aabb, merge_aabb(aabb), 0);
	}
	long long end_time = get_time();
	
	printf("kd-tree build time: %lldms\n", end_time - start_time); fflush(stdout);
	print_stats();
}

#include "geometry/mesh.hh"
void KDTree::Node::insepct() {
	printf("primitives: ");
	for (auto &p: primitive) {
		printf(" %d", ((Mesh::KDTreeFace *)p)->id);
	}
	printf("\n");
}


KDTree::AABB KDTree::merge_aabb(std::vector<AABB> &aabb)
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
	root->aabb_ray_test = merge_aabb(aabb);
	root->aabb_ray_test.intersect(tree_aabb);
	root->aabb = tree_aabb;
	if (aabb.size() < 15 || depth == 40) {
		for (auto &ab: aabb)
			root->primitive.push_back(primitive[ab.id]);
		return root;
	}

#if 1
	int axis_to_split = depth % 3;
	root->split_axis = axis_to_split;
	root->split_coord = 
		(root->aabb.get_coord_min(axis_to_split) +
		 root->aabb.get_coord_max(axis_to_split)) * 0.5;
#else
	real_t min_cost = 1e100;
	for (int axis = 0; axis < 3; axis ++) {
		real_t splt_crd;
		real_t cost = split_cost(axis, aabb, tree_aabb, depth, splt_crd);
		if (cost < min_cost) {
			min_cost = cost;
			root->split_axis = axis;
			root->split_coord = splt_crd;

			assert(tree_aabb.get_coord_min(axis) <= splt_crd);
			assert(tree_aabb.get_coord_max(axis) >= splt_crd);
		}
	}

	if (min_cost > 1e99) {
		for (auto &ab: aabb)
			root->primitive.push_back(primitive[ab.id]);
		return root;
	}
#endif

	std::vector<AABB> left, right;

	for (auto &ab: aabb) {
		if (ab.get_coord_min(root->split_axis) < root->split_coord + EPS)
			left.push_back(ab);
		if (ab.get_coord_max(root->split_axis) > root->split_coord - EPS)
			right.push_back(ab);
	}


	AABB aabb_left = tree_aabb,
		 aabb_right = tree_aabb;

	aabb_left.modify(root->split_axis, 1, root->split_coord);
	aabb_right.modify(root->split_axis, 0, root->split_coord);

	root->ch[0] = do_build_tree(left, aabb_left, depth + 1);
	root->ch[1] = do_build_tree(right, aabb_right, depth + 1);
	return root;
}

real_t KDTree::split_cost(int axis, const std::vector<AABB> &aabb, const AABB
		&tree_aabb, int , real_t &split_coord) {
	// Surface Area Heuristic (SAH)

	if (aabb.size() <= 1)
		return 1e100;

	struct Coord {
		real_t pos;
		int type; // -1 or 1;
		Coord(real_t pos, int type) :
			pos(pos), type(type) {}
	};

	std::vector<Coord> coord;
	for (size_t i = 0; i < aabb.size(); i ++) {
		const AABB &ab = aabb[i];
		coord.push_back(Coord(ab.get_coord_min(axis), 1));
		coord.push_back(Coord(ab.get_coord_max(axis), -1));
	}

	sort(coord.begin(), coord.end(), [](const Coord &a, const Coord &b) -> bool{
			if (fabs(a.pos - b.pos) > EPS) return a.pos < b.pos;
			return a.type < b.type;
			});

	struct CoordPro {
		real_t pos;
		int n_in,
			n_out;
		CoordPro(real_t pos, int n_in, int n_out) :
			pos(pos), n_in(n_in), n_out(n_out) {}
	}; 

	std::vector<CoordPro> coord_pro;
	for (size_t i = 0; i < coord.size(); ) {
		size_t j = i;
		CoordPro cp(coord[i].pos, 0, 0);
		while (j < coord.size() && fabs(coord[j].pos - coord[i].pos) < EPS) {
			if (coord[j].type == 1)
				cp.n_in ++;
			else cp.n_out ++;
			j ++;
		}
		coord_pro.push_back(cp);
		i = j;
	}
	

	int axis_y = (axis + 1) % 3,
		axis_z = (axis + 2) % 3;
	real_t a = tree_aabb.get_length(axis),
		   b = tree_aabb.get_length(axis_y),
		   c = tree_aabb.get_length(axis_z);
	real_t s = a * b + b * c + c * a;

	real_t min_cost = 1e100;

	int nl = 0, nr = aabb.size();
	int nl_min, nr_min;

	real_t coord_low = tree_aabb.get_coord_min(axis),
		   coord_high = tree_aabb.get_coord_max(axis);

	for (size_t i = 1; i < coord_pro.size(); i ++) {
		CoordPro &cp0 = coord_pro[i - 1],
				 &cp1 = coord_pro[i];
		real_t splt_crd = (cp1.pos + cp0.pos) * 0.5;
		nl = nl + cp0.n_in;
		nr = nr - cp0.n_out;

		if (splt_crd < coord_low || splt_crd > coord_high)
			continue;

		real_t al = splt_crd - coord_low,
			   ar = a - al;
		
		real_t sl = al * b + al * c + b * c,
			   sr = ar * b + ar * c + b * c;

		real_t cost = sl / s * nl + sr / s * nr;

		if (cost < min_cost) {
			min_cost = cost;
			split_coord = splt_crd;
			nl_min = nl;
			nr_min = nr;
		}
	}

	if (aabb.size() < min_cost) {
		//cout << c_traversal * aabb.size() << " " << min_cost << endl;
		return 1e100;
	}

	//printf("nl_min: %d, nr_min: %d, cost: %lf\n", nl_min, nr_min, min_cost);
	return min_cost;
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
	real_t t = root->aabb.intersect(ray);
	if (t < EPS)
		return nullptr;
	return do_intersect(root, ray);
}

void KDTree::print_stats() {
	Stats stats;
	do_print_stats(root, 0, stats);

#define PRINT_EXPR(expr) \
	cout << #expr << ": " << (expr) << endl;
#define PRINT_EXPR_PROMPT(prompt, expr) \
	cout << prompt << ": " << (expr) << endl;

	printf("----- kd-tree stats -----\n");
	PRINT_EXPR(stats.n_node);
	PRINT_EXPR(stats.leaf_min_depth); 
	PRINT_EXPR(stats.leaf_max_depth); 
	PRINT_EXPR(stats.n_leaf);
	PRINT_EXPR(stats.n_primitive);
	PRINT_EXPR(stats.leaf_n_prim_min);
	PRINT_EXPR(stats.leaf_n_prim_max);
	PRINT_EXPR_PROMPT("ave prim per leaf:", stats.n_primitive / (double)stats.n_leaf);
	printf("------------------------\n");

#undef PRINT_EXPR
#undef PRINT_EXPR_PROMPT
	fflush(stdout);
}

void KDTree::do_print_stats(Node *root, int depth, Stats &stats) {
	if (root == nullptr)
		return;
	if (root->is_leaf()) {
		stats.n_leaf ++;
		stats.leaf_min_depth = min(stats.leaf_min_depth, depth);
		stats.leaf_max_depth = max(stats.leaf_max_depth, depth);
		stats.n_primitive += root->primitive.size();
		stats.leaf_n_prim_min = min(stats.leaf_n_prim_min, (int)root->primitive.size());
		stats.leaf_n_prim_max = max(stats.leaf_n_prim_max, (int)root->primitive.size());
		return;
	}
	do_print_stats(root->ch[0], depth + 1, stats);
	do_print_stats(root->ch[1], depth + 1, stats);
}

void KDTree::free_node(Node *root) {
	if (root == nullptr)
		return;

	free_node(root->ch[0]);
	free_node(root->ch[1]);

	delete root;
}

KDTree::~KDTree() {
	free_node(root);
}

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

