/**
 *@file:   camera.cc
 *@date:   Mon Jul 22 14:25:56 CST 2013
 *@author: Shicao Li <shicao.li[at]gmail[dot]com>
 *@brief:  achieve some function.
 */

#include "camera.hh"
#include "math.hh"
#include <cstdio>

/**
 *@brief:   Product a ray from eye to the (x,y) pixel on the screen.
 *@param[in]  x  The pixel's x coordinate on the screen(width).
 *@param[in]  y  The pixel's y coordinate on the screen(hight).
 *@return:   Function return a ray from eye to the (x,y) pixel on the screen.
 *
 *  We get a sampler point on the eye called lens_sampler at first, the eye's randius is lens_randius.
 *  Then we get a sampler point on (x,y) pixel called screen_pos.
 *  Then we find the point on focal plane that correspond with screen_pos , we call it focal_pos.
 *  Finally we product a ray from lens_sampler to focal_pos and normalize it .
 */


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


