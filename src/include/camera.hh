/*
 * $File: camera.hh
 * $Date: Tue Jun 18 23:00:16 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "vector.hh"
#include "ray.hh"

class Camera
{
	public:
		Vector eye,
			   front,
			   up;

		real_t screen_dist;
		real_t screen_width, screen_height;

		int resol_x, resol_y;

		Camera() {}

		Camera(const Vector &eye, const Vector &front, const Vector &up,
				real_t screen_dist, real_t screen_width, real_t screen_height,
				int resol_x, int resol_y) :
			eye(eye), front(front), up(up), 
			screen_dist(screen_dist), screen_width(screen_width), screen_height(screen_height),
			resol_x(resol_x), resol_y(resol_y) {
				normalize();
			}

		Ray emit_ray(int x, int y);
		void normalize();
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

