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
	Pinhole::Pinhole(int width, int height, int fov, Vec3f position, Vec3f lookat, Vec3f up, int jittering):Camera(width, height, fov, position, lookat, up, 0, jittering){
		this->camera_right = lookat.crossProduct(up).normalize();
		this->new_up = this->camera_right.crossProduct(lookat).normalize();
		this->aspect_ratio = (float)width / (float)height;
		this->half_fov_tan = tan(fov * 0.5f * M_PI / 180.f);
		this->pixel_size = 2.f * half_fov_tan;

	}

	Ray Pinhole::createRay(int x, int y, RayType type, int sampleX, int sampleY, int xNum, int yNum){
		Ray ray;
		float u, v;
		if(xNum <= 0){
			// no jittering
			u = (float)x / (float)this->width - 0.5f;
			v = ((float)y / (float)this->height - 0.5f) / this->aspect_ratio;
		}else{
			// with jittering
			float jitterX = static_cast<float>(std::rand())/ static_cast<float>(RAND_MAX);
			float jitterY = static_cast<float>(std::rand())/ static_cast<float>(RAND_MAX);
			float subPixelWidth = 1.f / (float) xNum;
			float subPixelHeight = 1.f / (float) yNum;
			u = ((float)x + (sampleX + jitterX) * subPixelWidth) / (float)this->width - 0.5f;
			v = (((float)y + (sampleY + jitterY) * subPixelHeight) / (float)this->height - 0.5f) / this->aspect_ratio;
		}
		
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

