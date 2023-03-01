/*
 * Triangle.h
 *
 *
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "core/Shape.h"

namespace rt{

class Triangle: public Shape{
public:

	//
	// Constructors
	//
	Triangle();
	Triangle(Vec3f v0, Vec3f v1, Vec3f v2, Material *material):v0(v0), v1(v1), v2(v2){
		this->material = material;
	};

	virtual ~Triangle(){};


	//
	// Functions that need to be implemented, since Plane is a subclass of Shape
	//
	Hit intersect(Ray ray);

private:

	Vec3f v0;
    Vec3f v1;
    Vec3f v2;

};



} //namespace rt




#endif /* TRIANGLE_H_ */
