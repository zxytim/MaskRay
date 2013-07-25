/**
 *@file: color.hh
 *@date: Wed Jun 19 01:50:34 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "type.hh"
typedef double color_t;

/**
 *@class    Color color.hh "src/include/color.hh"
 *@date:    Wed Jun 19 01:50:34 2013 +0800
 *@author:  Xinyu Zhou <zxytim[at]gmail[dot]com>
 *@brief:   RGB color.
 */

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

		Color operator / (real_t _ratio) const {
			register real_t ratio = 1.0 / _ratio;
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

