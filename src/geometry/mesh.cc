/*
 * $File: mesh.cc
 * $Date: Wed Jun 19 22:56:09 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "geometry/mesh.hh"

#include "math.hh"

#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;
std::shared_ptr<GeometryIntersectInfo> Mesh::intersect(const Ray &ray)
{
	auto ret = new MeshIntersectInfo();

	for (auto fa: face) {
		Vector p[3] = {v[fa.v[0]], v[fa.v[1]], v[fa.v[2]]};
		const Vector &d = ray.dir,
			  &o = ray.o;

		Vector e1 = p[1] - p[0],
			   e2 = p[2] - p[0];
		
		Vector q = d.cross(e2);
		real_t f = e1.dot(q);
		if (fabs(f) < EPS)
			continue;

		f = 1.0 / f;

		Vector s = o - p[0];
		real_t u = f * s.dot(q);
		if (u < 0)
			continue;

		Vector r = s.cross(e1);
		real_t v = f * d.dot(r);
		if (v < 0 || u + v > 1.0)
			continue;

		real_t dist = -f * e2.dot(r);

		if (dist < EPS)
			continue;

		if (dist < ret->dist) {
			Vector normal = (1 - u - v) * vn[fa.vn[0]]
				+ u * vn[fa.vn[1]]
				+ v * vn[fa.vn[2]];

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

	ret->mesh = this;
	return shared_ptr<GeometryIntersectInfo>(ret);
}

Mesh::Mesh()
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

Mesh *mesh_read_from_file(const std::string &fname)
{
	Mesh *mesh = new Mesh();

	const int LINE_CHAR_MAX = 1000;
	std::ifstream fin(fname);
	char line[LINE_CHAR_MAX];
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
					break;
				case 'p': // vp
					continue;
					break;
				case ' ':// v x y z [w=1]
					ss >> dummy >> x >> y >> z;
					break;
			}
		} else if (line[0] == 'f') {
		}
	}
	
	return mesh;
}

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

