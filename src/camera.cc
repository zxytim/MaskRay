/*
 * $File: camera.cc
 * $Date: Wed Jun 19 16:19:54 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "camera.hh"
#include "math.hh"

Ray Camera::emit_ray(int x, int y)
{
	normalize();

	real_t cell_x_unit = screen_width / resol_x,
		   cell_y_unit = screen_height / resol_y;

	real_t screen_center_x = screen_width / 2,
		   screen_center_y = screen_height / 2;

	real_t o_x = cell_x_unit * x - screen_center_x + rand_real() * cell_x_unit,
		   o_y = cell_y_unit * y - screen_center_y + rand_real() * cell_y_unit;

	Vector screen_center = eye + front * screen_dist;
	Vector left = up.cross(front);

	Vector screen_pos = screen_center + left * o_x + up * o_y;

	Vector dir = (screen_pos - eye).normalize();
	//printf("(%lf, %lf, %lf)\n", dir.x, dir.y, dir.z);
	return Ray(eye, dir);
}

void Camera::normalize()
{
	front = front.normalize();
	up = up.normalize();
}

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

