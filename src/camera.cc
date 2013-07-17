/*
 * $File: camera.cc
 * $Date: Thu Jun 27 03:33:04 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#include "camera.hh"
#include "math.hh"
#include <cstdio>

Ray Camera::emit_ray(int x, int y)
{
	normalize();

	real_t cell_x_unit = screen_width / resol_x,
		   cell_y_unit = screen_height / resol_y;

	real_t screen_center_x = screen_width / 2,
		   screen_center_y = screen_height / 2;

	real_t o_x = cell_x_unit * x - screen_center_x + random.rand_real() * cell_x_unit,
		   o_y = cell_y_unit * y - screen_center_y + random.rand_real() * cell_y_unit;

	Vector screen_center = eye + front * screen_dist ;
	Vector left = up.cross(front);

	Vector screen_pos = screen_center + left * o_x + up * o_y;


	o_x = 2 * ( random.rand_real() - 0.5 ) * lens_radius ,
    o_y = 2 * ( random.rand_real() - 0.5 ) * lens_radius ;
    //printf( "o_x: %lf o_y: %lf lens_radius: %lf \n" , o_x , o_y , lens_radius ) ;
	Vector lens_sampler = eye + left * o_x + up * o_y ;                                 // lens_sampler is a sampler point on the lens
	Vector focal_pos = eye + ( screen_pos - eye ) * ( focal_dist / screen_dist ) ;      // focal_pos is the point on focal plane

	//Vector dir = (screen_pos - eye).normalize();

	Vector dir = ( focal_pos - lens_sampler ).normalize() ;

	//printf("o(%lf, %lf, %lf)\n", lens_sampler.x, lens_sampler.y, lens_sampler.z);
	//printf("d(%lf, %lf, %lf)\n", dir.x, dir.y, dir.z);
	//return Ray(screen_pos, dir);

	//return Ray(eye, dir);
	return Ray( lens_sampler , dir ) ;
}

void Camera::normalize()
{
	front = front.normalize();
	up = up.normalize();
}

/**
 * vim: syntax=cpp11 foldmethod=marker
 */


