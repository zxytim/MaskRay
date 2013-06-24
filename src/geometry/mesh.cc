/*
 * $File: mesh.cc
 * $Date: Tue Jun 25 01:06:11 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "geometry/mesh.hh"

#include "math.hh"

#include <cctype>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

GeometryIntersectInfo * Mesh::intersect(const Ray &ray) {
	if (conf.use_kdtree) {
#if 0
		static int cnt = 0;
		cnt ++;
		if (cnt == 5168) 
			int asdf = 0;
		GeometryIntersectInfo *ptr0 = brute_force_intersect(ray);
		GeometryIntersectInfo *ptr1 = kdtree_intersect(ray);
		assert(((ptr0 == nullptr) ^ (ptr1 == nullptr)) == 0);
		if (ptr0)
			assert(fabs(ptr0->get_dist() - ptr1->get_dist()) < EPS);
		return ptr0;
#endif
		return kdtree_intersect(ray);
	}
	return brute_force_intersect(ray);
}

GeometryIntersectInfo * Mesh::brute_force_intersect(const Ray &ray)
{
	auto ret = new MeshIntersectInfo();
	ret->dist = 1e100;
	ret->face = nullptr;

	for (auto &fa: face) {
		Vector &vert0 = v[fa.v[0]],
			   &vert1 = v[fa.v[1]],
			   &vert2 = v[fa.v[2]];

		Vector edge1 = vert1 - vert0,
			   edge2 = vert2 - vert0;

		Vector pvec = ray.dir.cross(edge2);
		real_t det = edge1.dot(pvec);
		if (det > -EPS && det < EPS)
			continue;

		real_t inv_det = 1.0 / det;

		Vector tvec = ray.o - vert0;
		real_t u = tvec.dot(pvec) * inv_det;
		if (u < 0.0 || u > 1.0)
			continue;

		Vector qvec = tvec.cross(edge1);
		real_t v = ray.dir.dot(qvec) * inv_det;
		if (v < 0.0 || u + v > 1.0)
			continue;
		
		real_t dist = edge2.dot(qvec) * inv_det;

		if (dist > EPS && dist < ret->dist) {
#if 0
			Vector normal = (1 - u - v) * vn[fa.vn[0]]
				+ u * vn[fa.vn[1]]
				+ v * vn[fa.vn[2]];
#else
			Vector normal = (vert1 - vert0).cross(vert2 - vert0);
#endif

			if (normal.dot(ray.dir) > 0)
				normal *= -1;
			if (normal.dot(ray.dir) >= -EPS)
				continue;

			ret->normal = normal;
			ret->dist = dist;
			ret->face = &fa;
		}
	}
	if (ret->face == nullptr) {
		delete ret;
		return nullptr;
	}

	ret->normal.to_normalized();
	ret->mesh = this;
	return ret;
}

void Mesh::finish() {
	if (conf.use_kdtree) {
		printf("building kdtree\n");
		build_kdtree();
	}
}

void Mesh::build_kdtree() {
	std::vector<Geometry *> primitive;
	for (size_t i = 0; i < face.size(); i ++) {
		auto ptr = new KDTreeFace();
		ptr->mesh = this;
		ptr->id = i;
		primitive.push_back(ptr);
	}

	if (kdtree)
		delete kdtree;

	kdtree = new KDTree();
	kdtree->build_tree(primitive);
}

GeometryIntersectInfo *Mesh::kdtree_intersect(const Ray &ray) {
	return kdtree->intersect(ray);
}

Mesh::Mesh(const MeshConf &conf) :
	conf(conf),
	kdtree(nullptr)
{
}

Mesh &Mesh::translate(const Vector &delta)
{
	for (auto &i: v) i += delta;
	for (auto &i: vn) i += delta;
	return *this;
}

Mesh &Mesh::translate(real_t dx, real_t dy, real_t dz)
{
	return translate(Vector(dx, dy, dz));
}

static void rotate_2D(real_t x, real_t y, real_t angle, real_t &xo, real_t &yo) {
	real_t sin_angle = sin(angle),
		   cos_angle = cos(angle);
	xo = cos_angle * x - sin_angle * y;
	yo = sin_angle * x + cos_angle * y;
}

Mesh &Mesh::rotate(int axis, real_t angle) {
	for (auto &i: v) {
		if (axis == 0) // x
			rotate_2D(i.y, i.z, angle, i.y, i.z);
		else if (axis == 1) // y
			rotate_2D(i.z, i.x, angle, i.z, i.x);
		else // z
			rotate_2D(i.x, i.y, angle, i.x, i.y);
	}
	return *this;
}

Mesh &Mesh::rotate_deg(int axis, real_t angle) {
	return rotate(axis, angle / 180.0 * M_PI);
}

Mesh &Mesh::scale(real_t ratio)
{
	for (auto &i: v) i *= ratio;
	for (auto &i: vn) i *= ratio;
	return *this;
}

Mesh &Mesh::to_origin()
{
	if (v.size() == 0)
		return *this;
	Vector s;
	s = Vector(0, 0, 0);
	for (auto &i: v) s += i;
	s /= v.size();
	for (auto &i: v) i -= s;
	return *this;
}

Mesh &Mesh::normalize()
{
	if (v.size() == 0)
		return *this;
	to_origin();
	real_t s = -1;
	for (auto &i: v) s = max(abs(i.x), max(abs(i.y), abs(i.z)));
	for (auto &i: v) i /= s;
	return *this;
}

GeometryIntersectInfo * Mesh::KDTreeFace::intersect(const Ray &ray) {
	return mesh->face_intersect(id, ray);
}

void Mesh::KDTreeFace::get_shape(real_t *x, real_t *y, real_t *z) {
	Mesh::Face &fa = mesh->face[id];
	Vector &v0 = mesh->v[fa.v[0]],
		   &v1 = mesh->v[fa.v[1]],
		   &v2 = mesh->v[fa.v[2]];
	if (fa.v[0] == 57)
		int asdf = 0;

	x[0] = min(v0.x, min(v1.x, v2.x));
	x[1] = max(v0.x, max(v1.x, v2.x));
	y[0] = min(v0.y, min(v1.y, v2.y));
	y[1] = max(v0.y, max(v1.y, v2.y));
	z[0] = min(v0.z, min(v1.z, v2.z));
	z[1] = max(v0.z, max(v1.z, v2.z));
}

GeometryIntersectInfo *Mesh::face_intersect(int id, const Ray &ray) {
	Face &fa = face[id];
	Vector &vert0 = v[fa.v[0]],
		   &vert1 = v[fa.v[1]],
		   &vert2 = v[fa.v[2]];

	Vector edge1 = vert1 - vert0,
		   edge2 = vert2 - vert0;

	Vector pvec = ray.dir.cross(edge2);
	real_t det = edge1.dot(pvec);
	if (det > -EPS && det < EPS)
		return nullptr;

	real_t inv_det = 1.0 / det;

	Vector tvec = ray.o - vert0;
	real_t u = tvec.dot(pvec) * inv_det;
	if (u < 0.0 || u > 1.0)
		return nullptr;

	Vector qvec = tvec.cross(edge1);
	real_t v = ray.dir.dot(qvec) * inv_det;
	if (v < 0.0 || u + v > 1.0)
		return nullptr;

	real_t dist = edge2.dot(qvec) * inv_det;

	if (dist < EPS)
		return nullptr;

#if 0
	Vector normal = (1 - u - v) * vn[fa.vn[0]]
		+ u * vn[fa.vn[1]]
		+ v * vn[fa.vn[2]];
#else
	Vector normal = (vert1 - vert0).cross(vert2 - vert0);
#endif

	if (normal.dot(ray.dir) > 0)
		normal *= -1;
	if (normal.dot(ray.dir) >= -EPS)
		return nullptr;

	MeshIntersectInfo *ret = new MeshIntersectInfo();
	ret->normal = normal.normalize();
	ret->dist = dist;
	ret->face = &fa;
	ret->mesh = this;
	return ret;
}

Mesh *mesh_read_from_file(const std::string &fname)
{
	Mesh *mesh = new Mesh();

	const int LINE_CHAR_MAX = 1000;
	std::ifstream fin(fname);
	char line[LINE_CHAR_MAX];
	int id = 0;
	while (fin.getline(line, LINE_CHAR_MAX)) {
		// comment
		if (line[0] == '#')
			continue;

		std::stringstream ss;
		ss << line;
		std::string dummy;

		real_t x, y, z;
		real_t u, v;

		if (line[0] == 'v') {
			switch (line[1]) {
				case 't': // vt u v [w=0]
					ss >> u >> v;
					break;
				case 'n': // vn x y z, may not be unit
					ss >> x >> y >> z;
					mesh->vn.push_back(Vector(x, y, z));
					break;
				case 'p': // vp
					break;
				case ' ':// v x y z [w=1]
					ss >> dummy >> x >> y >> z;
					mesh->v.push_back(Vector(x, y, z));
					break;
			}
		} else if (line[0] == 'f') {
			// FIXME: only deal with triangles
			ss >> dummy;
			int v[3], vt[3], vn[3];
			memset(v, -1, sizeof(v));
			memset(vt, -1, sizeof(vt));
			memset(vn, -1, sizeof(vn));
			for (int i = 0; i < 3; i ++) {
				string s;
				ss >> s;
				auto func = [](string s, int &v, int &vt, int &vn) -> void{
					size_t i = 0;
					v = 0;
					while (i < s.length() && isdigit(s[i])) v = v * 10 + s[i ++] - '0';
					if (i < s.length() && s[i] == '/')  {
						if (i + 1 < s.length() && s[i + 1] == '/') { // no vt
							vt = -1;
							i = i + 2;
							vn = 0;
							while (i < s.length() && isdigit(s[i])) vn = vn * 10 + s[i ++] - '0';
						}
						else { // has vt
							vt = 0;
							i = i + 1;
							while (i < s.length() && isdigit(s[i])) vt = vt * 10 + s[i ++] - '0';

							if (i < s.length() && s[i] == '/') { // has vn
								vn = 0;
								while (i < s.length() && isdigit(s[i])) vn = vn * 10 + s[i ++] - '0';
							}
						}
					}
				};
				func(s, v[i], vt[i], vn[i]);
				v[i] -= 1, vt[i] -= 1, vn[i] -= 1;
			}
			auto f = Mesh::Face(v, vt, vn);
			f.id = id ++;
			mesh->face.push_back(f);
		}
	}
	
	return mesh;
}


/**
 * vim: syntax=cpp11 foldmethod=marker
 */

