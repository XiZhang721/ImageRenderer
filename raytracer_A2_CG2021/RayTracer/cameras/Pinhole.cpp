/*
 * Pinhole.cpp
 *
 *
 */
#include <iostream>

#include "Pinhole.h"


namespace rt{

	//
	// Pinhole constructor (example)
	//
	Pinhole::Pinhole(int width, int height, int fov, Vec3f position, Vec3f lookat, Vec3f up):Camera(width, height, fov, position, lookat, up){
		this->aspectRatio = width/height;

		// to fill

	}

	Ray Pinhole::createRay(int x, int y, RayType type){
		Ray ray;
		float scale = tan(this->fov * ((M_PI / 180.f)/2));
		float newX = (2 * (x + 0.5)/ (float)this->width - 1)*scale;
		float newY = (1-2*(y+0.5)/(float)this->height) * scale * 1 / this->aspectRatio;
		Vec3f cameraSpace = Vec3f(newX, newY, -0.5);
		ray.origin = this->position;
		ray.direction = (cameraSpace - this->position).normalize();
		ray.raytype = type;
		return ray;
	}


	/**
	 * Prints camera data
	 * this function implements the abstract function of the base Camera class
	 */
	void Pinhole::printCamera(){
		printf("I am a pinhole camera! \n");
		printf("width: %dpx, height: %dpx, fov:%d \n", width, height, fov);
	}



} //namespace rt

