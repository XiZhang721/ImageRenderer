/*
 * Plane.cpp
 *
 *
 */
#include "Plane.h"
#include <cmath>

namespace rt{


	/**
	 * Computes whether a ray hit the specific instance of a plane shape and returns the hit data
	 *
	 * @param ray cast ray to check for intersection with shape
	 *
	 * @return hit struct containing intersection information
	 *
	 */
	Hit Plane::intersect(Ray ray){

		Hit h;
		//-----------to be implemented -------------
		// Not inplemented
		h.hasHit = false;
		h.material = material;
		return h;

	}



} //namespace rt


