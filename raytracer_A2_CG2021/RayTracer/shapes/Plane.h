/*
 * Plane.h
 *
 *
 */

#ifndef PLANE_H_
#define PLANE_H_

#include "core/Shape.h"
#include "shapes/Triangle.h"

namespace rt{

class Plane:public Shape{

public:

	//
	// Constructors
	//
	Plane();
	Plane(Vec3f v0, Vec3f v1, Vec3f v2, Vec3f v3, Material *material):v0(v0), v1(v2), v2(v2), v3(v3),material(material){};

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
    Triangle t1;
    Triangle t2;
    Material material;

};



} //namespace rt




#endif /* PLANE_H_ */
