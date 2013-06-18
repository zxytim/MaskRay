/*
 * $File: raytracer.hh
 * $Date: Tue Jun 18 21:54:15 2013 +0800
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
		shared_ptr<Image> render(Scene &scene, Camera &camera);

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

		shared_ptr<IntersectInfo> get_closest_intersection(const Ray &ray);
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

