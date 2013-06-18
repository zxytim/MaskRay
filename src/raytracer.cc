/*
 * $File: raytracer.cc
 * $Date: Wed Jun 19 03:13:35 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "raytracer.hh"
#include "intensity.hh"
#include <queue>
#include <thread>
#include <mutex>
#include "math.hh"
#include "util.hh"
#include <cv.h>
#include <highgui.h>

static Color intensity_to_color(const Intensity &intensity)
{
	return Color(intensity.r, intensity.g, intensity. b);
}

Image* image_accum;
Image* image_show;
std::mutex lock;
int phase;

void RayTracer::iterate(Camera &camera)
{
	shared_ptr<Image> image(new Image(camera.resol_x, camera.resol_y));
	while (true) {
		Color *image_data = image->data;
		for (int i = 0; i < camera.resol_x; i ++)
			//#pragma omp parallel for 
			for (int j = 0; j < camera.resol_y; j ++) {
				Ray ray = camera.emit_ray(i, j);
				*image_data = intensity_to_color(trace(ray));
				image_data ++;
			}

		lock.lock();

		phase += 1;
		printf("phase %3d ...\r", phase);
		fflush(stdout);

		Color *acc = image_accum->data;
		Color *ptr = image->data;
		for (int i = 0; i < camera.resol_x; i ++)
			for (int j = 0; j < camera.resol_y; j ++)
				*(acc ++) += *(ptr ++);
		if (phase & 3)
		{
			acc = image_accum->data;
			Color *image_show_data = image_show->data;
			for (int i = 0; i < camera.resol_x; i ++)
				for (int j = 0; j < camera.resol_y; j ++) {
					*image_show_data = *acc/ phase;
					image_show_data ++;
					acc ++;
				}
			cv::Mat mat = image_to_mat(*image_show);
			//cv::imshow("process", mat);
			cv::imwrite("output-mid.png", mat);
			//cv::waitKey(1);
		}
		lock.unlock();
	}

}

shared_ptr<Image> RayTracer::render(Scene &scene, Camera &camera)
{
	this->scene = &scene;
	image_show = (new Image(camera.resol_x, camera.resol_y));
	image_accum = (new Image(camera.resol_x, camera.resol_y));
	cv::namedWindow("process", CV_WINDOW_AUTOSIZE);

	int nworker = 4;
#if 1
	auto threads = new std::thread[nworker];
	for (int i = 0; i < nworker; i ++)
		threads[i] = std::thread([&]{iterate(camera);});
	
#endif
	iterate(camera);
	return nullptr;
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

