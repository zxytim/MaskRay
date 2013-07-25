/**
 *@file: random.cc
 *@date: Thu Jun 27 03:31:29 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "random.hh"

#include <cstdlib>
Random::Random() {
	Xi[0] = rand();
	Xi[1] = rand();
	Xi[2] = rand();
}

/**
 *@brief:   return a real number between 0 and 1.
 */

real_t Random::rand_real() {
	return erand48(Xi);
}

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

