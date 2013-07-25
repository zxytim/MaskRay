/**
 *@file: image.hh
 *@date: Tue Jun 25 02:03:19 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "color.hh"
#include <cstring>

/**
 *@class   Image image.hh "src/include/image.hh"
 *@date:   Tue Jun 25 02:03:19 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 *@brief:  image class.
 */

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

