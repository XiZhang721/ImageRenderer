/*
 * Pinhole.h
 *
 *
 */

#ifndef PINHOLE_H_
#define PINHOLE_H_

#include "core/Camera.h"
#include "core/RayHitStructs.h"

namespace rt{

class Pinhole:public Camera{
public:

	//
	// Constructors
	//
	Pinhole();
	Pinhole(int width, int height, int fov, Vec3f position, Vec3f lookat, Vec3f up);

	Ray createRay(int x, int y, RayType type);
	//
	//Destructor
	//
	~Pinhole(){};
	
	//
	// print function (implementing abstract function of base class)
	//
	void printCamera();

private:
	Vec3f camera_right;
	Vec3f new_up;
	float aspect_ratio;
	float half_fov_tan;
	float pixel_size;
};



} //namespace rt




#endif /* PINHOLE_H_ */
