/*
 * Shape.h
 *
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "core/RayHitStructs.h"
#include "core/Material.h"
#include "math/geometry.h"
#include "rapidjson/document.h"
#include "materials/BlinnPhong.h"


using namespace rapidjson;
namespace rt{

class Shape{
public:

	//
	// Constructors
	//
	Shape(){};

	//
	// Destructor (must be overriden in subclass)
	//
	virtual ~Shape();

	static Shape* createShape(Value& shapeSpecs);
	
	//
	// Shape abstract methods (to be implemented by subclasses)
	//
	virtual Hit intersect(Ray)=0;
	virtual Vec3f getCenter()=0;

	bool isMesh() const{
		return shapeType == "mesh";
	}
	Vec3f min;
	Vec3f max;	

protected:
	Material *material;
	std::string shapeType;

};


} //namespace rt


#endif /* SHAPE_H_ */
