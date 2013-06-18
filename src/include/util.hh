/*
 * $File: util.hh
 * $Date: Wed Jun 19 01:40:47 2013 +0800
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

cv::Mat image_to_mat(const Image &image);

Renderable *make_renderable(Geometry *geometry,
		SurfaceProperty *surface_property,
		TextureMapper *texture_mapper = NULL,
		Material *material = NULL);

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

