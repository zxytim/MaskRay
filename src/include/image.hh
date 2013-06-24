/*
 * $File: image.hh
 * $Date: Tue Jun 25 02:03:19 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "color.hh"
#include <cstring>

class Image
{
	public:
		int width, height;
		Color *data;

		Image(int width, int height) :
			width(width), height(height) {
				data = new Color[size()];
				memset(data, 0, sizeof(data[0]) * size());
			}

		~Image () {
			delete [] data;
		}
		inline int size() const { return width * height; }
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

