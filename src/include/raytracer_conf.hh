/*
 * $File: raytracer_conf.hh
 * $Date: Thu Jun 27 12:55:18 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "type.hh"
#include <string>

class RayTracerConf
{
	public:
		real_t STOP_ENERGY_THRESHOLD;
		int TRACE_DEPTH_MAX;

		int N_THREDED_WORKER; // -1 means auto
		int N_ITER;
		int N_ITER_WRITE_IMAGE;
		int N_ITER_SHOW_IMAGE;

		std::string IMAGE_NAME;
		std::string IMAGE_FORMAT;

		RayTracerConf() :
			STOP_ENERGY_THRESHOLD(0.01),
			TRACE_DEPTH_MAX(15),
			N_THREDED_WORKER(-1),
			N_ITER(12000000),
			N_ITER_WRITE_IMAGE(1),
			N_ITER_SHOW_IMAGE(10),
			IMAGE_NAME("/tmp/output-mid"),
			IMAGE_FORMAT("png")
		{}

		void print() {
			printf("----- Ray Tracer Config -----\n");
			printf("TRACE_DEPTH_MAX:  %5d\n", TRACE_DEPTH_MAX);
			printf("N_THREDED_WORKER: %5d\n", N_THREDED_WORKER);
			printf("N_ITER:           %5d\n", N_ITER);
			printf("N_ITER_WRITE_IMAGE: %5d\n", N_ITER_WRITE_IMAGE);
			printf("IMAGE_OUTPUT:  %s\n", (IMAGE_NAME + "." + IMAGE_FORMAT).c_str());
			printf("-----------------------------\n");
			fflush(stdout);
		}
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

