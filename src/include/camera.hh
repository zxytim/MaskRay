/**
 *@file:   camera.hh
 *@date:   Mon Jul 22 14:01:57 CST 2013
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 *         Shicao Li <shicao.li[at]gmail[dot]com>
 *@brief:  This is a thinLens camera.
 */

#pragma once

#include "vector.hh"
#include "ray.hh"
#include "random.hh"
#include <cstdio>

/**
 *@class    Camera camera.hh "src/include/camera.hh"
 *@author   Shicao Li <shicao.li[at]gmail[dot]com>
 *@brief    Thinlens camera.
 */

class Camera
{
	public:
		Vector eye,                             ///< location of the camera
			   front,                           ///< where the camera look at
			   up;                              ///< up direction

		real_t screen_dist ;                    ///< screen_dist is the distance beteewn the eye ans the screen
        real_t focal_dist ;                     ///< focal_dist is the distance between the eye and the focal plane
        real_t lens_radius ;                    ///< lens_radius is the radius of the lens on the camera
		real_t screen_width ;                   ///< width of the screen
		real_t screen_height ;                  ///< hight of th screen

		int resol_x;                            ///< The pixel number of width.
		int resol_y;                            ///< The pixel number of hight.

		Camera() {}
        /**
         *@brief:   constructed function
         */
		Camera(const Vector &eye, const Vector &front, const Vector &up,
				real_t screen_dist, real_t screen_width, real_t screen_height,
				real_t focal_dist , real_t lens_radius ,
				int resol_x, int resol_y) :
			eye(eye), front(front), up(up),
			screen_dist(screen_dist), screen_width(screen_width), screen_height(screen_height),
			focal_dist( focal_dist ), lens_radius( lens_radius ) ,
			resol_x(resol_x), resol_y(resol_y) {
				normalize();
			}

		Ray emit_ray(int x, int y);             ///< emit a ray from eye to pixel (x, y)
		void normalize();                       ///< normalize up and front vector.

	protected:

		Random random;                          ///< get random x and y ( 0 < x < 1 && 0 < y < 1 ). no lock
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */


