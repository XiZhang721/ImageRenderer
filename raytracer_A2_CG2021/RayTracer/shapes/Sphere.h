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
		std::printf("center x: %f\n",center[0]);
		std::printf("center y: %f\n",center[1]);
		std::printf("center z: %f\n",center[2]);
		std::printf("radius: %f\n",radius);
	};

	virtual ~Sphere(){};

	//
	// Functions that need to be implemented, since Sphere is a subclass of Shape
	//
	Hit intersect(Ray ray);

private:

	Vec3f center;
	float radius;

};



} //namespace rt




#endif /* SPHERE_H_ */
