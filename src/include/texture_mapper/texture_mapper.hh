/*
 * $File: texture_mapper.hh
 * $Date: Wed Jun 19 11:44:47 2013 +0800
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
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

