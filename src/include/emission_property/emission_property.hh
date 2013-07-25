/**
 *@file: emission_property.hh
 *@date: Mon Jun 24 03:18:14 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "intensity.hh"
#include "intersect_info.hh"

/**
 *@class    EmissionProperty emission_property.hh "src/include/emission_property.hh"
 *@date:    Mon Jun 24 03:18:14 2013 +0800
 *@author:  Xinyu Zhou <zxytim[at]gmail[dot]com>
 *@brief:   EmissionProperty may be used by SurfaceProperty.
 */
class EmissionProperty
{
	public:
		// no emission by default
		virtual Intensity get_emission(IntersectInfo &) {
			return Intensity(0, 0, 0);
		}

		virtual ~EmissionProperty() {}
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

