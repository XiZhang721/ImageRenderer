/*
 * Camera.cpp
 *
 */
#include <iostream>

#include "Camera.h"
#include "cameras/Pinhole.h"
#include "cameras/ThinLens.h"

namespace rt{

	Camera::~Camera(){};



/**
 * Factory function that returns camera subclass based on camera specifications
 *
 * @param cameraSpecs camera specifications json object
 *
 * @return camera subclass instance
 *
 */
Camera* Camera::createCamera(Value& cameraSpecs){

	//check if cameratype is defined

	if (!cameraSpecs.HasMember("type")){
		std::cerr<<"Camera type not specified"<<std::endl;
		exit(-1);
	}

	std::string cameraType=cameraSpecs["type"].GetString();

	Vec3f position{cameraSpecs["position"][0].GetFloat(),cameraSpecs["position"][1].GetFloat(),cameraSpecs["position"][2].GetFloat()};
	Vec3f lookat{cameraSpecs["lookat"][0].GetFloat(),cameraSpecs["lookat"][1].GetFloat(),cameraSpecs["lookat"][2].GetFloat()};
	Vec3f up{cameraSpecs["up"][0].GetFloat(),cameraSpecs["up"][1].GetFloat(),cameraSpecs["up"][2].GetFloat()};
	
	//return camera object based on camera specs
	if (cameraType.compare("pinhole")==0){
		return new Pinhole(cameraSpecs["width"].GetInt(),
				cameraSpecs["height"].GetInt(),
				cameraSpecs["fov"].GetInt(), position, lookat, up);
	}
	// }else if (cameraType.compare("thinlens")==0){
	// 	return new ThinLens();
	// }

	return 0;

}

// void setCameraToWorld(){
// 	Vec3f left = this->up.crossProduct(this->lookat).normalize();
// 	Vec3f normalizedUp = this->up.normalize();
// 	Vec3f normalizedLookat = this->lookat.normalize();
// 	Matrix44f returnMatrix{};

// 	returnMatrix[0][0] = left[0];
// 	returnMatrix[1][0] = left[1];
// 	returnMatrix[2][0] = left[2];
// 	returnMatrix[3][0] = 0;

// 	returnMatrix[0][1] = normalizedUp[0];
// 	returnMatrix[1][1] = normalizedUp[1];
// 	returnMatrix[2][1] = normalizedUp[2];
// 	returnMatrix[3][1] = 0;

// 	returnMatrix[0][2] = normalizedLookat[0];
// 	returnMatrix[1][2] = normalizedLookat[1];
// 	returnMatrix[2][2] = normalizedLookat[2];
// 	returnMatrix[3][2] = 0;

// 	returnMatrix[0][3] = this->position[0];
// 	returnMatrix[1][3] = this->position[1];
// 	returnMatrix[2][3] = this->position[2];
// 	returnMatrix[3][3] = 1;

// 	cameraToWorld = returnMatrix;
// }


} //namespace rt
