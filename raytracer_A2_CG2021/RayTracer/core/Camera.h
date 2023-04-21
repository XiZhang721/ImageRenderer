/*
 * Camera.h
 *
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "rapidjson/document.h"
#include "math/geometry.h"
#include "RayHitStructs.h"


using namespace rapidjson;

namespace rt{

class Camera{
public:

	//
	// Constructors
	//
	Camera(){};
	Camera(int height, int width, int fov, Vec3f position, Vec3f lookat, Vec3f up, int camera_type, int jittering):height(height), width(width), fov(fov), position(position), lookat(lookat), up(up), camera_type(camera_type), jittering(jittering){};

	//
	// Destructor
	//
	virtual ~Camera();

	virtual Ray createRay(int x, int y, RayType type, int sampleX, int sampleY, int xNum, int yNum) = 0;


	//
	// factory function : returns camera instance dynamically based on camera specifications
	//
	static Camera* createCamera(Value& cameraSpecs);


	//
	// print function (to be implemented by the subclasses )
	//
	virtual void printCamera()=0;


	//
	// other camera functions (to complete)
	//


	//
	// Getters and Setters
	//
	int getHeight() const {
		return height;
	}

	void setHeight(int height) {
		this->height = height;
	}

	int getWidth() const {
		return width;
	}

	void setWidth(int width) {
		this->width = width;
	}

	int getType() const {
		return camera_type;
	}

	int getJittering() const{
		return jittering;
	}



protected:

	//
	//camera members
	//
	int height;
	int width;
	int fov; //field of view
	int jittering;
	Vec3f position;
	Vec3f lookat;
	Vec3f up;
	int camera_type;

};

} //namespace rt



#endif /* CAMERA_H_ */
