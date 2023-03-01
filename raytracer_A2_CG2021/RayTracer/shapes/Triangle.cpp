/*
 * Triangle.cpp
 *
 *
 */
#include "Triangle.h"
#include <math.h>


namespace rt{

    Hit Triangle::intersect(Ray ray){
        Hit hit;
        Vec3f e1 = v1 - v0;
        Vec3f e2 = v2 - v0;
        Vec3f pvec = ray.direction.crossProduct(e2);
        float det = e1.dotProduct(pvec);
        if(abs(det) < 1e-3){
            hit.hasHit = false;
            return hit;
        }
        float inv_det = 1/det;
        Vec3f tvec = ray.origin - v0;
        float u = tvec.dotProduct(pvec) * inv_det;

        if(u < 0 || u > 1){
            hit.hasHit = false;
            return hit;
        }
        Vec3f qvec = tvec.crossProduct(e1);
        float v = ray.direction.dotProduct(qvec) * inv_det;

        if(v < 0 || u + v > 1){
            hit.hasHit = false;
            return hit;
        }

        float t = e2.dotProduct(qvec) * inv_det;
        if(t < 0){
            hit.hasHit = false;
            return hit;
        }
        Vec3f intersection = ray.origin + ray.direction * t;
        hit.hasHit = true;
        hit.point = intersection;
        hit.material = material;
        hit.normal = e1.crossProduct(e2).normalize();
        return hit;



    }



} //namespace rt
