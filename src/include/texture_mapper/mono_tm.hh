/**
 *@file: mono_tm.hh
 *@date: Tue Jun 18 21:46:16 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "texture_mapper/texture_mapper.hh"


/**
 *@class   MonoTextureMapper MonoTextureMapper.hh "src/include/texture_mapper/MonoTextureMapper.hh"
 *@date:   Tue Jun 18 21:46:16 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

class MonoTextureMapper : public TextureMapper
{
	public:
		MonoTextureMapper(const Intensity &intensity);
		virtual Intensity get_texture(IntersectInfo &intersect_info) override;  ///<return color of the texture.

	protected:
		Intensity intensity;                        ///< texture mapper color.
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

