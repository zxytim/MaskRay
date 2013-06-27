/*
 * $File: random.cc
 * $Date: Thu Jun 27 03:31:29 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "random.hh"

#include <cstdlib>
Random::Random() {
	Xi[0] = rand();
	Xi[1] = rand();
	Xi[2] = rand();
}

real_t Random::rand_real() {
	return erand48(Xi);
}

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

