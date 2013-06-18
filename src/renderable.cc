/*
 * $File: renderable.cc
 * $Date: Tue Jun 18 23:53:28 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "renderable.hh"

#include "material.hh"
#include "texture_mapper.hh"

Renderable::Renderable(shared_ptr<Geometry> geometry,
		shared_ptr<SurfaceProperty> surface_property,
		shared_ptr<TextureMapper> texture_mapper,
		shared_ptr<Material> material):
	geometry(geometry),
	surface_property(surface_property),
	texture_mapper(texture_mapper),
	material(material)
{
}

shared_ptr<IntersectInfo> Renderable::intersect(const Ray &ray)
{
	// TODO: Bounding Box

	auto geoii = geometry->intersect(ray);
	if (!geoii)
		return nullptr;
	shared_ptr<IntersectInfo> ret(new IntersectInfo());
	ret->intersect_info = geoii;
	ret->renderable = this;

	return ret;
}

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

