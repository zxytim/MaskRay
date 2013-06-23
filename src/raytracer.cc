/*
 * $File: raytracer.cc
 * $Date: Mon Jun 24 01:41:34 2013 +0800
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
#include <algorithm>

using namespace std;

static Color intensity_to_color(const Intensity &intensity)
{
	return Color(intensity.r, intensity.g, intensity. b);
}

Image* image_accum;
Image* image_show;
int phase;

bool still_iterate;
int N_ITER_MAX = 100000;

real_t clamp(real_t x) { return x < 0 ? x : x > 1 ? 1 : x; }
Intensity clamp(const Intensity &i) {
	return Intensity(clamp(i.r), clamp(i.g), clamp(i.b));
}

Color clamp(const Color &i) {
	return Color(clamp(i.r), clamp(i.g), clamp(i.b));
}
void RayTracer::iterate(Camera &camera)
{
	static std::mutex lock;
	shared_ptr<Image> image(new Image(camera.resol_x, camera.resol_y));
	while (still_iterate) {
		Color *image_data = image->data;
		for (int i = 0; i < camera.resol_x; i ++)
			//#pragma omp parallel for 
			for (int j = 0; j < camera.resol_y; j ++) {
				Ray ray = camera.emit_ray(i, j);
				Color color = intensity_to_color(trace(ray));
				*image_data = color; //Color(clamp(color.r), clamp(color.g), clamp(color.b));
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
		if ((phase & 3) || phase == N_ITER_MAX)
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
			cv::imshow("process", mat);
			cv::imwrite("output-mid.png", mat);
			cv::waitKey(1);
			if (phase == N_ITER_MAX)
				still_iterate = false;
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
	still_iterate = true;
	auto threads = new std::thread[nworker];
	for (int i = 0; i < nworker; i ++)
		threads[i] = std::thread([&]{iterate(camera);});

	for (int i = 0; i < nworker; i ++)
		threads[i].join();

	delete [] threads;
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

	auto inter = get_closest_intersection(incident);
	if (inter == nullptr)
		return Intensity(0, 0, 0); // black

	Renderable *renderable = inter->renderable;

	Intensity texture = renderable->texture_mapper->get_texture(*inter);
	Intensity emission = renderable->surface_property->get_emission(*inter);

	if (incident.energy < conf.STOP_ENERGY_THRESHOLD || depth == 0)
		return emission;

#if 0
	// Russian Roulette
	real_t prob = max(texture.r, max(texture.g, texture.b));
	if (depth > 5 || !prob) {
		if (rand_real() < prob) 
			texture = texture / prob;
		else
			return emission;
	}
#endif

	Ray ray = inter->ray_bounce(incident);
	ray.o += ray.dir * EPS;


	Intensity ret(0, 0, 0);

	ret = do_trace(ray, depth - 1) * texture;
	ret = ret + emission;

	// FIXME: energy not used
	return ret;

	// TODO:
	//		MATERIAL
	//		MEDIA
	//		BRDFs
}


/**
 * vim: syntax=cpp11 foldmethod=marker
 */

