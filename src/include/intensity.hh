/*
 * $File: intensity.hh
 * $Date: Thu Jun 20 02:16:54 2013 +0800
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
		inline Intensity operator / (real_t _ratio) const {
			real_t ratio = 1.0 / _ratio;
			return Intensity(r * ratio, g * ratio, b * ratio);
		}

		inline Intensity operator + (const Intensity &intensity) const {
			return Intensity(r + intensity.r, g + intensity.g, b + intensity. b);
		}

		inline real_t lengthsqr() const { return r * r + g * g + b * b; }
		inline real_t length() const { return sqrt(r * r + g * g + b * b); }
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

