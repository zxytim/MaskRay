/**
 *@file:   material/material.hh
 *@date:   Wed Jun 19 14:38:19 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "type.hh"

/**
 *@class    Material material.hh "src/include/material/material.hh"
 *@date:    Wed Jun 19 14:38:19 2013 +0800
 *@author:  Xinyu Zhou <zxytim[at]gmail[dot]com>
 *@brief:   material of the object.
 */

class Material
{
	public:
		real_t refractive_index;                                                    ///< refractive index.
		Material(real_t refractive_index) : refractive_index(refractive_index) {}
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

