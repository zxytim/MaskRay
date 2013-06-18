/*
 * $File: mono_tm.cc
 * $Date: Tue Jun 18 22:02:57 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "texture_mapper/mono_tm.hh"

MonoTextureMapper::MonoTextureMapper(const Intensity &intensity) :
	intensity(intensity)
{}

Intensity MonoTextureMapper::get_texture(IntersectInfo &)
{
	return intensity;
}

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

