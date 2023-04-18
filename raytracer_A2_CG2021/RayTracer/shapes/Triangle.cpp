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
        if(abs(det) < 0){
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

        // Barycentric coordinate
        Vec3f p0 = intersection - v0;
        Vec3f p1 = intersection - v1;
        Vec3f p2 = intersection - v2;

        float denominator = e1.crossProduct(e2).length();
        float alpha = p1.crossProduct(p2).length() / denominator;
        float beta = p2.crossProduct(p0).length() / denominator;
        float gamma = 1 - alpha - beta;

        if(this->hasNormal){
            hit.normal = (n0 * alpha + n1 * beta + n2 * gamma).normalize();
        }else{
            hit.normal = e1.crossProduct(e2).normalize();
        }
        
        if(u > 0){
            u = -u;
            v = -v;
        }
        if(this->hasUV){
            Vec2f uv = uv0 * alpha + uv1 * beta + uv2 * gamma;
            hit.u = uv.x;
            hit.v = uv.y;
        }else{
            hit.u = v;
            hit.v = u;            
        }

        return hit;



    }



} //namespace rt
