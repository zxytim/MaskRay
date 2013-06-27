/*
 * $File: util.hh
 * $Date: Thu Jun 27 12:48:54 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "image.hh"
#include <cv.h>
#include <highgui.h>

#include "renderable.hh"
#include "surface_property.hh"
#include "texture_mapper.hh"
#include "material.hh"
#include "random.hh"
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <string>

cv::Mat image_to_mat(const Image &image);

Renderable *make_renderable(std::string name, 
		Geometry *geometry,
		SurfaceProperty *surface_property,
		TextureMapper *texture_mapper = NULL,
		Material *material = NULL);

Renderable *make_renderable_noname(
		Geometry *geometry,
		SurfaceProperty *surface_property,
		TextureMapper *texture_mapper = NULL,
		Material *material = NULL);

long long get_time();

void write_image(Image *image, const std::string &fname);

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

