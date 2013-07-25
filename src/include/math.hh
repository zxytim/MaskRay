/**
 *@file:   math.hh
 *@date:   Thu Jun 27 03:32:19 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 *@brief:  some math function.
 */

#pragma once

#include <cmath>
#include <cstdlib>

#include "type.hh"

const real_t EPS = 1e-6;

inline bool ge0(const real_t &a) {
	return a > -EPS;
}

inline bool le0(const real_t &a) {
	return a < EPS;
}

inline bool lt0(const real_t &a) {
	return a < -EPS;
}

inline bool gt0(const real_t &a) {
	return a > EPS;
}

inline bool eq0(const real_t &a) {
	return -EPS < a && a < EPS;
}

inline bool le(const real_t &a, const real_t &b) {
	return a < b + EPS;
}

inline bool ge(const real_t &a, const real_t &b) {
	return a > b - EPS;
}

inline bool gt(const real_t &a, const real_t &b) {
	return a > b + EPS;
}

inline bool lt(const real_t &a, const real_t &b) {
	return a < b - EPS;
}

inline bool eq(const real_t &a, const real_t &b) {
	register real_t d = a - b;
	return -EPS < d && d < EPS;
}

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

