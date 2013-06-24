/*
 * $File: raytracer_conf.hh
 * $Date: Mon Jun 24 05:10:54 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "type.hh"

class RayTracerConf
{
	public:
		real_t STOP_ENERGY_THRESHOLD,
			   TRACE_DEPTH_MAX;

		RayTracerConf() :
			STOP_ENERGY_THRESHOLD(0.01),
			TRACE_DEPTH_MAX(15)
		{}
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

