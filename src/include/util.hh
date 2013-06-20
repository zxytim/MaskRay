/*
 * $File: util.hh
 * $Date: Wed Jun 19 21:34:47 2013 +0800
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

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

