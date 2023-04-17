/*
 * ThinLens.h
 *
 */

#ifndef THINLENS_H_
#define THINLENS_H_

#include "core/Camera.h"
#include "core/RayHitStructs.h"

namespace rt{

class ThinLens:public Camera{
public:

	//
	// Constructors
	//
	ThinLens();
	ThinLens(int width, int height, int fov, Vec3f position, Vec3f lookat, Vec3f up, float aperturesize, float focusdistance);

	Ray createRay(int x, int y, RayType type);
	//
	//Destructor
	//
	~ThinLens(){};

	//
	// print function (implementing abstract function of base class)
	//
	void printCamera();

private:
	Vec3f camera_right;
	Vec3f new_up;
	float aperture_size;
	float focus_distance;
	float aspect_ratio;
	float half_fov_tan;
	float pixel_size;
};



} //namespace rt




#endif /* THINLENS_H_ */
