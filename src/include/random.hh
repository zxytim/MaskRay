/*
 * $File: random.hh
 * $Date: Thu Jun 27 03:30:35 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "type.hh"

class Random
{
	public:
		Random();

		// return a real number in [0.0, 1.0] with uniform distribution
		real_t rand_real();

	protected:
		unsigned short Xi[3];
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

