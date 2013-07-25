/**
 *@file: raytracer.hh
 *@date: Thu Jun 27 03:33:28 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "scene.hh"
#include "camera.hh"
#include "renderable.hh"
#include "image.hh"
#include "raytracer_conf.hh"

#include <vector>

/**
 *@class   RayTracer raytracer.hh "src/include/raytracer.hh"
 *@date:   Thu Jun 27 03:33:28 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 *@brief:  This class will render the scene by ray tracing .
 */

class RayTracer
{
	public:
		Image * render(Scene &scene, Camera &camera);       ///< render the scene.

	//protected:

		/*
		 * Intermediate variable
		 */
		Scene *scene;                                               ///< the scene.

		RayTracerConf conf;                                         ///< some control information of ray tracer.

		/**
		 * Single trace thread
		 */
		Intensity trace(const Ray &ray);                            ///< call do_trace.
		Intensity do_trace(const Ray &ray, int depth);              ///< trace the ray.

		IntersectInfo * get_closest_intersection(const Ray &ray);   ///< get collision point.

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

