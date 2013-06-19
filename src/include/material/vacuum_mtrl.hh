/*
 * $File: vacuum_mtrl.hh
 * $Date: Wed Jun 19 14:52:46 2013 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "material.hh"

class VacuumMaterial : public Material
{
	public:
		VacuumMaterial() : Material(1.0) {}
};

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

