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
		this->shapeType = "triangle";

		float max_x = std::max(std::max(v0.x, v1.x),v2.x);
		float max_y = std::max(std::max(v0.y, v1.y),v2.y);
		float max_z = std::max(std::max(v0.z, v1.z),v2.z);
		this->max = Vec3f{max_x, max_y, max_z};

		float min_x = std::min(std::min(v0.x, v1.x),v2.x);
		float min_y = std::min(std::min(v0.y, v1.y),v2.y);
		float min_z = std::min(std::min(v0.z, v1.z),v2.z);
		this->min = Vec3f{min_x,min_y,min_z};
		this->center = (this->max + this->min) / 2.f;
	};

	Triangle(Vec3f v0, Vec3f v1, Vec3f v2, Vec3f n0, Vec3f n1, Vec3f n2, Material *material)
	:v0(v0), v1(v1), v2(v2), n0(n0), n1(n1), n2(n2){
		this->material = material;
		this->shapeType = "face";
		this->hasNormal = true;

		float max_x = std::max(std::max(v0.x, v1.x),v2.x);
		float max_y = std::max(std::max(v0.y, v1.y),v2.y);
		float max_z = std::max(std::max(v0.z, v1.z),v2.z);
		this->max = Vec3f{max_x, max_y, max_z};

		float min_x = std::min(std::min(v0.x, v1.x),v2.x);
		float min_y = std::min(std::min(v0.y, v1.y),v2.y);
		float min_z = std::min(std::min(v0.z, v1.z),v2.z);
		this->min = Vec3f{min_x,min_y,min_z};
		this->center = (this->max + this->min) / 2.f;
	};

	Triangle(Vec3f v0, Vec3f v1, Vec3f v2, Vec2f uv0, Vec2f uv1, Vec2f uv2, Material *material)
	:v0(v0), v1(v1), v2(v2), uv0(uv0), uv1(uv1), uv2(uv2){
		this->material = material;
		this->shapeType = "face";
		this->hasUV = true;

		float max_x = std::max(std::max(v0.x, v1.x),v2.x);
		float max_y = std::max(std::max(v0.y, v1.y),v2.y);
		float max_z = std::max(std::max(v0.z, v1.z),v2.z);
		this->max = Vec3f{max_x, max_y, max_z};

		float min_x = std::min(std::min(v0.x, v1.x),v2.x);
		float min_y = std::min(std::min(v0.y, v1.y),v2.y);
		float min_z = std::min(std::min(v0.z, v1.z),v2.z);
		this->min = Vec3f{min_x,min_y,min_z};
		this->center = (this->max + this->min) / 2.f;
	};

	Triangle(Vec3f v0, Vec3f v1, Vec3f v2, Vec3f n0, Vec3f n1, Vec3f n2, Vec2f uv0, Vec2f uv1, Vec2f uv2, Material *material)
	:v0(v0), v1(v1), v2(v2), n0(n0), n1(n1), n2(n2), uv0(uv0), uv1(uv1), uv2(uv2){
		this->material = material;
		this->shapeType = "face";
		this->hasNormal = true;
		this->hasUV = true;

		float max_x = std::max(std::max(v0.x, v1.x),v2.x);
		float max_y = std::max(std::max(v0.y, v1.y),v2.y);
		float max_z = std::max(std::max(v0.z, v1.z),v2.z);
		this->max = Vec3f{max_x, max_y, max_z};

		float min_x = std::min(std::min(v0.x, v1.x),v2.x);
		float min_y = std::min(std::min(v0.y, v1.y),v2.y);
		float min_z = std::min(std::min(v0.z, v1.z),v2.z);
		this->min = Vec3f{min_x,min_y,min_z};
		this->center = (this->max + this->min) / 2.f;
	};



	virtual ~Triangle(){};


	//
	// Functions that need to be implemented, since Plane is a subclass of Shape
	//
	Hit intersect(Ray ray);
	Vec3f getCenter(){
		return this->center;
	};

private:
	Vec3f v0;
    Vec3f v1;
    Vec3f v2;
	Vec3f center;

	bool hasNormal = false;
	Vec3f n0;
	Vec3f n1;
	Vec3f n2;

	bool hasUV = false;
	Vec2f uv0;
	Vec2f uv1;
	Vec2f uv2;

};



} //namespace rt




#endif /* TRIANGLE_H_ */
