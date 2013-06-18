/*
 * $File: texture_mapper.hh
 * $Date: Tue Jun 18 21:45:36 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once
#include "intersect_info.hh"
#include "intensity.hh"

class TextureMapper
{
	public:
		virtual Intensity get_texture(IntersectInfo &intersect_info) = 0;
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

