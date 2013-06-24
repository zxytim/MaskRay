/*
 * $File: image.hh
 * $Date: Mon Jun 24 03:38:47 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "color.hh"

class Image
{
	public:
		int width, height;
		Color *data;

		Image(int width, int height) :
			width(width), height(height) {
				data = new Color[size()];
			}

		~Image () {
			delete [] data;
		}
		inline int size() const { return width * height; }
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

