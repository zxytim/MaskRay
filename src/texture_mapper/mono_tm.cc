/**
 *@file: mono_tm.cc
 *@date: Tue Jun 18 22:02:57 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "texture_mapper/mono_tm.hh"

MonoTextureMapper::MonoTextureMapper(const Intensity &intensity) :
	intensity(intensity)
{}
/**
 *@brief:   return color of the texture.
 */
Intensity MonoTextureMapper::get_texture(IntersectInfo &)
{
	return intensity;
}

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

