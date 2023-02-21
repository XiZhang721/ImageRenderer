/*
 * PointLight.cpp
 *
 *
 */
#include "PointLight.h"




namespace rt{

    PointLight::PointLight(Vec3f position, Vec3f is, Vec3f id): LightSource(position, is, id){
        name = "pointlight";
    }



} //namespace rt
