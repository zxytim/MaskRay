/*
 * $File: color.hh
 * $Date: Wed Jun 19 00:12:21 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

typedef double color_t;

class Color
{
	public:
		color_t r, g, b;
		Color() {}
		Color(color_t r, color_t g, color_t b) :
			r(r), g(g), b(b) {}

		Color operator + (const Color &col) const {
			return Color(r + col.r, g + col.g, b + col.b);
		}
		Color& operator += (const Color &col) {
			r += col.r;
			g += col.g;
			b += col.b;
			return *this;
		}

		Color operator / (real_t ratio) const {
			return Color(r * ratio, g * ratio, b * ratio);
		}
		Color& operator /= (real_t ratio) {
			r /= ratio;
			g /= ratio;
			b /= ratio;
			return *this;
		}
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

