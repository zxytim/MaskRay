/*
 * $File: util.cc
 * $Date: Mon Jun 24 03:17:26 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "util.hh"
#include <algorithm>
#include <sstream>

using namespace cv;

Mat image_to_mat(const Image &image)
{
	Mat mat(image.height, image.width, CV_8UC3, Scalar::all(0));
	Color *data = image.data;

	for (int i = 0; i < mat.rows; i ++) {
		uchar *p = mat.ptr<uchar>(i);
		for (int j = 0; j < mat.cols; j ++) {
			p[0] = std::min(255.0, data[(image.width - 1 - j) * image.height + (image.height - i)].b * 255);
			p[1] = std::min(255.0, data[(image.width - 1 - j) * image.height + (image.height - i)].g * 255);
			p[2] = std::min(255.0, data[(image.width - 1 - j) * image.height + (image.height - i)].r * 255);

#if 0
			p[0] = std::min(255.0, pow(data[(image.width - 1 - j) * image.height + (image.height - i)].b, 1 / 2.2) * 255 + 0.5);
			p[1] = std::min(255.0, pow(data[(image.width - 1 - j) * image.height + (image.height - i)].g, 1 / 2.2) * 255 + 0.5);
			p[2] = std::min(255.0, pow(data[(image.width - 1 - j) * image.height + (image.height - i)].r, 1 / 2.2) * 255 + 0.5);
#endif
			p += 3;
		}
	}

	return mat;
}

Renderable *make_renderable(std::string name, 
		Geometry *geometry,
		SurfaceProperty *surface_property,
		TextureMapper *texture_mapper,
		Material *material)
{
	TextureMapper * tm(texture_mapper);
	if (texture_mapper == NULL)
		tm = (new MonoTextureMapper(Intensity(0.5, 0.5, 0.5)));
	Material * mtrl(material);
	if (material == NULL)
		mtrl = (new Material(1.0));

	return new Renderable(
			name,
			geometry,
			surface_property,
			tm, mtrl);
}

Renderable *make_renderable_noname(
		Geometry *geometry,
		SurfaceProperty *surface_property,
		TextureMapper *texture_mapper,
		Material *material)
{
	// FIXME: not thread safe
	static int count = 0;
	std::string name;

	std::stringstream ss;
	ss << count ++;
	ss >> name;
	return make_renderable(name, geometry, surface_property, texture_mapper, material);
}

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

