/**
 *@file:   texture_mapper/texture_mapper.hh
 *@date:   Mon Jun 24 03:19:50 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once
#include "intersect_info.hh"
#include "intensity.hh"

/**
 *@class   TextureMapper texture_mapper.hh "src/include/texture_mapper/texture_mapper.hh"
 *@date:   Mon Jun 24 03:19:50 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 *@brief:  Texture Mapper may be geometry related.
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

