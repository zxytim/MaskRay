/*
 * $File: raytracer.hh
 * $Date: Thu Jun 27 03:33:28 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "scene.hh"
#include "camera.hh"
#include "renderable.hh"
#include "image.hh"
#include "raytracer_conf.hh"

#include <vector>

class RayTracer
{
	public:
		Image * render(Scene &scene, Camera &camera);

	//protected:

		/*
		 * Intermediate variable
		 */
		Scene *scene;

		RayTracerConf conf;

		/**
		 * Single trace thread
		 */
		Intensity trace(const Ray &ray);
		Intensity do_trace(const Ray &ray, int depth);

		IntersectInfo * get_closest_intersection(const Ray &ray);

		class ThreadTaskScheduler {
			public:
				bool working;
				// accumulatively add intensity to image
				ThreadTaskScheduler(Camera &camera, Image *image, int n_ray_cast = 50);

				int fetch_task(std::vector<Ray> &task); // return task_id
				void report_task(const std::vector<Intensity> &intensity, int tid);

				static const int NO_TASK = -1;

			protected:
				Camera &camera;
				Image *image;
				int n_ray_cast;
				int cur_task;
		};

		// a single iterate of image, intensity is added accumulatively
		void iterate(Camera &camera, Image *image);
		void worker(ThreadTaskScheduler *tts);


		bool naive_worker_working;
		int naive_worker_cur_pos;
		void naive_worker(Camera &camera, Image *image);

		Random random;
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

