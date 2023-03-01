/*
 * Sphere.cpp
 *
 *
 */
#include "Sphere.h"
#include <cmath>

namespace rt{


	/**
	 * Computes whether a ray hit the specific instance of a sphere shape and returns the hit data
	 *
	 * @param ray cast ray to check for intersection with shape
	 *
	 * @return hit struct containing intersection information
	 *
	 */
	Hit Sphere::intersect(Ray ray){

		Hit h;
		//-----------to be implemented -------------
		
		Vec3f L = center - ray.origin;
		float tca = L.dotProduct(ray.direction);
		if(tca < 0){
			h.hasHit = false;
			return h;
		}
		float d2 = L.dotProduct(L) - tca * tca;
		if(d2 > radius * radius){
			h.hasHit = false;
			return h;
		}
		float thc = sqrtf(radius * radius - d2);
		float t0 = tca - thc;
		float t1 = tca + thc;
		if(t0 > t1){
			std::swap(t0,t1);
		}
		if(t0 < 1e-4){
			t0 = t1;
			if(t0 < 1e-4){
				h.hasHit = false;
				return h;
			}
		}
		h.hasHit = true;
		h.point = ray.origin + ray.direction * t0;
		h.normal = (h.point - center).normalize();
		h.material = material;
		return h;

	}



} //namespace rt


