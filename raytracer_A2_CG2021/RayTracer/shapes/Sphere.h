/*
 * Sphere.h
 *
 *
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "core/Shape.h"
#include <iostream>
#include <fstream>

namespace rt{

class Sphere:public Shape{

public:

	//
	// Constructors
	//
	Sphere();
	Sphere(Vec3f center, float radius, Material *material):center(center), radius(radius){
		this->material = material;
		this->shapeType = "sphere";
		this->max = center + Vec3f{radius,radius, radius};
		this->min = center - Vec3f{radius,radius, radius};
	};

	virtual ~Sphere(){};

	//
	// Functions that need to be implemented, since Sphere is a subclass of Shape
	//
	Hit intersect(Ray ray);
	Vec3f getCenter(){
		return this->center;
	};
private:
	Vec3f center;
	float radius;

};



} //namespace rt




#endif /* SPHERE_H_ */
