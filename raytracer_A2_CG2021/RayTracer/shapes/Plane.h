/*
 * Plane.h
 *
 *
 */

#ifndef PLANE_H_
#define PLANE_H_

#include "core/Shape.h"
#include <iostream>
#include <fstream>
namespace rt{

class Plane:public Shape{

public:

	//
	// Constructors
	//
	Plane();
	Plane(Vec3f v0, Vec3f v1, Vec3f v2, Vec3f v3, Material *material):v0(v0), v1(v1), v2(v2), v3(v3){
		this->material = material;
		this->shapeType = "plane";

		float max_x = std::max(std::max(std::max(v0.x, v1.x),v2.x),v3.x);
		float max_y = std::max(std::max(std::max(v0.y, v1.y),v2.y),v3.y);
		float max_z = std::max(std::max(std::max(v0.z, v1.z),v2.z),v3.z);
		this->max = Vec3f{max_x, max_y, max_z};

		float min_x = std::min(std::min(std::min(v0.x, v1.x),v2.x),v3.x);
		float min_y = std::min(std::min(std::min(v0.y, v1.y),v2.y),v3.y);
		float min_z = std::min(std::min(std::min(v0.z, v1.z),v2.z),v3.z);
		this->min = Vec3f{min_x,min_y,min_z};
	};

	virtual ~Plane(){};


	//
	// Functions that need to be implemented, since Plane is a subclass of Shape
	//
	Hit intersect(Ray ray);




private:
	Vec3f v0;
    Vec3f v1;
    Vec3f v2;
    Vec3f v3;

};



} //namespace rt




#endif /* PLANE_H_ */
