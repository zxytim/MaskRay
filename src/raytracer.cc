/*
 * $File: raytracer.cc
 * $Date: Wed Jun 19 00:13:20 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "raytracer.hh"
#include "intensity.hh"
#include "math.hh"

static Color intensity_to_color(const Intensity &intensity)
{
	return Color(intensity.r, intensity.g, intensity. b);
}

shared_ptr<Image> RayTracer::render(Scene &scene, Camera &camera)
{
	this->scene = &scene;
	shared_ptr<Image> image(new Image(camera.resol_x, camera.resol_y));

	int n_ray_emit_per_pixel = 10;
	for (int phase = 0; phase < n_ray_emit_per_pixel; phase ++) {
		Color *image_data = image->data;
		for (int i = 0; i < camera.resol_x; i ++)
			for (int j = 0; j < camera.resol_y; j ++) {
				Ray ray = camera.emit_ray(i, j);
				*image_data += intensity_to_color(trace(ray));
				image_data ++;
			}
	}

	Color *image_data = image->data;
	for (int i = 0; i < camera.resol_x; i ++)
		for (int j = 0; j < camera.resol_y; j ++) {
			*image_data /= n_ray_emit_per_pixel;
			image_data ++;
		}

	return image;
}

Intensity RayTracer::trace(const Ray &ray)
{
	return do_trace(ray, conf.TRACE_DEPTH_MAX);
}


shared_ptr<IntersectInfo> RayTracer::get_closest_intersection(const Ray &ray)
{
	real_t min_dist = 1e100;
	shared_ptr<IntersectInfo> ii = nullptr;

	for (auto renderable: scene->renderable) {
		auto rst = renderable->intersect(ray);
		if (rst == nullptr)
			continue;
		real_t dist = rst->get_dist();
		if (dist < min_dist)
		{
			min_dist = dist;
			ii = rst;
		}
	}

	return ii;
}

Intensity RayTracer::do_trace(const Ray &incident, int depth)
{
	if (incident.energy < conf.STOP_ENERGY_THRESHOLD || depth == 0)
		return Intensity(0, 0, 0);

	auto inter = get_closest_intersection(incident);
	if (inter == nullptr)
		return Intensity(0, 0, 0); // black

	Ray ray = inter->ray_bounce(incident);

	if (ray.dir.dot(incident.dir) > 0.0) // in order to prevent float point accuracy problems:
		ray.o += incident.dir * EPS; // if refracts, move the intersection a little more in
	else ray.o -= incident.dir * EPS; // if reflects, move the intersection a little more out

	Renderable *renderable = inter->renderable;

	// traced intensity * texture
	Intensity ret = do_trace(ray, depth - 1) * renderable->texture_mapper->get_texture(*inter)
		+ renderable->surface_property->get_emission(*inter);

	// FIXME: energy not used
	return ret;

	// TODO:
	//		REFRACT
	//		MATERIAL
	//		MEDIA
	//		BRDFs
}


/**
 * vim: syntax=cpp11 foldmethod=marker
 */

