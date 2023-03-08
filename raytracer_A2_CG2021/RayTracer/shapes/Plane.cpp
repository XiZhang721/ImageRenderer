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
		Vec3f e1 = v1 - v0;
		Vec3f e2 = v3 - v0;
		Vec3f normal = e2.crossProduct(e1).normalize();

		float t = ((v0 - ray.origin).dotProduct(normal)) / (ray.direction.dotProduct(normal));
		Vec3f intersection = ray.origin + ray.direction * t;

		Vec3f edge1 = intersection - v0;
		Vec3f edge2 = intersection - v1;
		Vec3f edge3 = intersection - v2;
		Vec3f edge4 = intersection - v3;

		float dot1 = edge1.dotProduct(e1.crossProduct(normal));
		float dot2 = edge2.dotProduct(e2.crossProduct(normal));
		float dot3 = edge3.dotProduct((v3 - v2).crossProduct(normal));
		float dot4 = edge4.dotProduct((v0 - v3).crossProduct(normal));

		if(dot1 >= 0.f && dot2 >= 0.f && dot3 >= 0.f && dot4 >= 0.f){
			h.point = intersection;
			h.normal = normal;
			h.material = material;
			h.hasHit = true;
			Vec3f q = (intersection - v0);
			float uCoord = q.dotProduct(e1)/ e1.length();
			float vCoord = q.dotProduct(e2)/ e2.length();
			h.u = uCoord / e1.length();
			h.v = vCoord / e2.length();
			return h;
		}else{
			h.hasHit = false;
			return h;
		}
	}



} //namespace rt


