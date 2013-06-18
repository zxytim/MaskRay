/*
 * $File: util.hh
 * $Date: Tue Jun 18 23:51:12 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "image.hh"
#include <cv.h>

#include "renderable.hh"
#include "surface_property.hh"
#include "texture_mapper.hh"
#include "material.hh"

cv::Mat image_to_mat(const Image &image);

Renderable *make_renderable(Geometry *geometry,
		SurfaceProperty *surface_property,
		TextureMapper *texture_mapper = NULL,
		Material *material = NULL);

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

