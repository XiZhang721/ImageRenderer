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
		Vec3f D = ray.direction;
		float tca = L.dotProduct(D);
		if(tca < 0){
			h.hasHit = false;
			return h;
		}
		float d2 = L.dotProduct(L) - tca * tca;
		float d = sqrtf(d);
		if(d < 0.f){
			h.hasHit = false;
			return h;
		}

		float thc2 = radius * radius - d2;
		// We need to ensure thc2 is not negative so we could apply sqrt to it
		if(thc2 < 0){
			h.hasHit = false;
			return h;
		}

		// Use the pythaorean theorem to calculate t0 and t1
		float thc = sqrtf(thc);
		float t0 = tca - thc;
		float t1 = tca + thc;

		// Get the closer t value as t0
		if(t0 > t1){
			std::swap(t0,t1);
		}

		// Check if the ray hits
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


