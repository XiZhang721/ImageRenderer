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
		this->camera_right = lookat.crossProduct(up).normalize();
		this->new_up = this->camera_right.crossProduct(lookat).normalize();
		this->aspect_ratio = (float)width / (float)height;
		this->half_fov_tan = tan(fov * 0.5f * M_PI / 180.f);
		this-> pixel_size = 2.f * half_fov_tan;
		// to fill

	}

	Ray Pinhole::createRay(int x, int y, RayType type){
		Ray ray;
		float u = (float)x / (float)this->width - 0.5f;
		float v = ((float)y / (float)this->height - 0.5f) / this->aspect_ratio;
		Vec3f ray_dir = (this->lookat + u * this->camera_right * pixel_size - v * this->new_up * pixel_size).normalize();
		ray.origin = this->position;
		ray.inv_dir = 1.f / ray_dir;
		ray.direction = ray_dir;
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

