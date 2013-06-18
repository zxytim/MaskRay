/*
 * $File: util.cc
 * $Date: Wed Jun 19 00:05:48 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "util.hh"

using namespace cv;

Mat image_to_mat(const Image &image)
{
	Mat mat(image.height, image.width, CV_8UC3, Scalar::all(0));
	Color *data = image.data;

	for (int i = 0; i < mat.rows; i ++) {
		uchar *p = mat.ptr<uchar>(i);
		for (int j = 0; j < mat.cols; j ++) {
			p[0] = data[j * image.height + i].b * 255;
			p[1] = data[j * image.height + i].g * 255;
			p[2] = data[j * image.height + i].r * 255;
			p += 3;
		}
	}

	return mat;
}

Renderable *make_renderable(Geometry *geometry,
		SurfaceProperty *surface_property,
		TextureMapper *texture_mapper,
		Material *material)
{
	shared_ptr<TextureMapper> tm(texture_mapper);
	if (texture_mapper == NULL)
		tm = shared_ptr<TextureMapper>(new MonoTextureMapper(Intensity(0.5, 0.5, 0.5)));
	shared_ptr<Material> mtrl(material);
	if (material == NULL)
		mtrl = shared_ptr<Material>(new Material(1.0));

	return new Renderable(
			shared_ptr<Geometry>(geometry),
			shared_ptr<SurfaceProperty>(surface_property),
			tm, mtrl);
}

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

