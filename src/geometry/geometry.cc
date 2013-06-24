/*
 * $File: geometry.cc
 * $Date: Mon Jun 24 08:30:27 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "geometry/geometry.hh"
#include <cassert>

GeometryIntersectInfo * Geometry::intersect(const Ray &)
{
	throw "not implemented";
}

void Geometry::get_shape(real_t *, real_t *, real_t *) {
	throw "not implemented";
}

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

