/*
 * $File: raytracer.hh
 * $Date: Wed Jun 19 02:43:51 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "scene.hh"
#include "camera.hh"
#include "renderable.hh"
#include "image.hh"
#include "raytracer_conf.hh"

class RayTracer
{
	public:
		Image * render(Scene &scene, Camera &camera);

	protected:

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
		void iterate(Camera &camera);
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

