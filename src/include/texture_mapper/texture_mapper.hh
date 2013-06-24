/*
 * $File: texture_mapper.hh
 * $Date: Mon Jun 24 03:19:50 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once
#include "intersect_info.hh"
#include "intensity.hh"

/*
 * Texture Mapper may be geometry related
 */
class TextureMapper
{
	public:
		virtual Intensity get_texture(IntersectInfo &intersect_info) = 0;
		virtual ~TextureMapper() {}
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

