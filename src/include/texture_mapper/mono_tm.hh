/*
 * $File: mono_tm.hh
 * $Date: Tue Jun 18 21:46:16 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "texture_mapper/texture_mapper.hh"

class MonoTextureMapper : public TextureMapper
{
	public:
		MonoTextureMapper(const Intensity &intensity);
		virtual Intensity get_texture(IntersectInfo &intersect_info) override;

	protected:
		Intensity intensity;
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

