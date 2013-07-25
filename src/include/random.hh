/**
 *@file: random.hh
 *@date: Thu Jun 27 03:30:35 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "type.hh"

/**
 *@class   Random random.hh "src/include/random.hh"
 *@date:   Thu Jun 27 03:30:35 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 *@brief:  get random number.
 */
class Random
{
	public:
		Random();


		real_t rand_real();///< return a real number in [0.0, 1.0] with uniform distribution

	protected:
		unsigned short Xi[3];
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

