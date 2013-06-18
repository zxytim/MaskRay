/*
 * $File: material.hh
 * $Date: Tue Jun 18 21:15:47 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

class Material
{
	public:
		real_t refractive_index;
		Material(real_t refractive_index) : refractive_index(refractive_index) {}
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

