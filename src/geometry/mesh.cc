/*
 * $File: mesh.cc
 * $Date: Wed Jun 19 20:07:34 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#if 0

#include "geometry/mesh.hh"

std::shared_ptr<GeometryIntersectInfo> Mesh::intersect(const Ray &ray)
{
	auto ret = new MeshIntersectInfo();

	for (auto f: face) {
		Vector p[3] = {v[f.v[0]], v[f.v[1]], v[f.v[2]]};
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

		real_t dist = f * e2.dot(r);

		if (dist < EPS)
			continue;

		if (dist < ret->dist) {
			Vector normal = (1 - u - v) * vn[f.vn[0]]
				+ u * vn[fa.vn[1]]
				+ v * vn[fa.vn[2]];

			if (normal.dot(ray.dir) > 0)
				normal *= -1;
			if (normal.dot(ray.dir) >= -EPS)
				continue;

			ret->normal = normal;
			ret->dist = dist;
			ret->face = &f;
		}
	}
	if (ret->face == nullptr) {
		delete ret;
		return nullptr;
	}

	ret->mesh = this;
	return shared_ptr<GeometryIntersectInfo>(ret);
}

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

#endif
