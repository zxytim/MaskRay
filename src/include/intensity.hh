/*
 * $File: intensity.hh
 * $Date: Tue Jun 18 22:28:12 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "type.hh"

class Intensity
{
	public:
		intensity_t r, g, b;

		Intensity() {}
		Intensity(const real_t &r, const real_t &g, const real_t &b) :
			r(r), g(g), b(b) {}

		inline Intensity operator * (const Intensity &intensity) const {
			return Intensity(r * intensity.r, g * intensity.g, b * intensity.b);
		}

		inline Intensity operator * (const real_t &ratio) const {
			return Intensity(r * ratio, g * ratio, b * ratio);
		}

		inline Intensity operator + (const Intensity &intensity) const {
			return Intensity(r + intensity.r, g + intensity.g, b + intensity. b);
		}
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

