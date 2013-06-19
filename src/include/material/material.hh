/*
 * $File: material.hh
 * $Date: Wed Jun 19 14:38:19 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "type.hh"

class Material
{
	public:
		real_t refractive_index;
		Material(real_t refractive_index) : refractive_index(refractive_index) {}
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

