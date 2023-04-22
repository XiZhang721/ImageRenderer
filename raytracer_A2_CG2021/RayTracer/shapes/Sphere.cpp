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
		Vec3f L = center - ray.origin;
		float tca = L.dotProduct(ray.direction);
		if(tca < 0){
			h.hasHit = false;
			return h;
		}

		float d2 = L.dotProduct(L) - tca * tca;
		float d = sqrtf(d2);
		if(d < 0.f || d > radius){
			h.hasHit = false;
			return h;
		}

		// Use the pythaorean theorem to calculate t0 and t1
		float thc = sqrtf(radius * radius - d2);
		float t0 = tca - thc;
		float t1 = tca + thc;

		// Get the t value
		float t;
		if(t0 < 1e-4 && t1 < 1e-4){
			h.hasHit = false;
			return h;
		}else if(t0 < 1e-4){
			t = t1;
		}else if(t1 < 1e-4){
			t = t0;
		}else{
			t = std::min(t0, t1);
		}

		h.hasHit = true;
		h.point = ray.origin + ray.direction * t;
		h.normal = (h.point - center).normalize();
		h.material = material;
		float phi = acos(h.normal[2]);
		float theta = atan2(h.normal[1], h.normal[0]);
		if(theta < 0.f){
			theta += 2.f * M_PI;
		}
		h.u = theta / (2.f * M_PI);
		h.v = phi / M_PI;
		return h;

	}



} //namespace rt


