/*
 * ThinLens.cpp
 *
 *
 */
#include <iostream>


#include "ThinLens.h"
#include <random>



namespace rt{

	//
	// ThinLens constructor (example)
	//
	ThinLens::ThinLens(int width, int height, int fov,Vec3f position, Vec3f lookat, Vec3f up, float aperturesize, float focusdistance):Camera(width, height, fov, position, lookat, up, 1){
		this->aperture_size = aperturesize;
		this->focus_distance = focusdistance;
		this->camera_right = lookat.crossProduct(up).normalize();
		this->new_up = this->camera_right.crossProduct(lookat).normalize();
		this->aspect_ratio = (float)width / (float)height;
		this->half_fov_tan = tan(fov * 0.5f * M_PI / 180.f);
		this->pixel_size = 2.f * half_fov_tan;
	}

    Ray ThinLens::createRay(int x, int y, RayType type)
    {
        Ray ray;
		float u = (float)x / (float)this->width - 0.5f;
		float v = ((float)y / (float)this->height - 0.5f) / this->aspect_ratio;

		// std::random_device rd;
		// std::mt19937 gen(rd());
		// std::uniform_real_distribution<> dist(-1.0, 1.0);
		// float r1, r2;
		// do{
		// 	r1 = dist(gen);
		// 	r2 = dist(gen);
		// }while (r1 * r1 + r2 * r2 > 1.f);
		//Vec3f lens_point = this->aperture_size * (r1 * this->camera_right + r2 * this->new_up) * 0.5f;
		float r1 = static_cast<float>(std::rand())/ static_cast<float>(RAND_MAX);
		float r2 = static_cast<float>(std::rand())/ static_cast<float>(RAND_MAX);
		float angle = 2.f * M_PI * r1;
		float radius = sqrtf(r2) * this->aperture_size * 0.5f;
		float offsetX = radius * cosf(angle);
		float offsetY = radius * sinf(angle);
		Vec3f lens_point = this->position + offsetX * this->camera_right + offsetY * this->new_up;

		Vec3f ray_dir = (this->lookat + u * this->camera_right * pixel_size - v * this->new_up * pixel_size).normalize();
		Vec3f focus_point = this->position  + ray_dir * this->focus_distance;

		ray_dir = (focus_point - lens_point).normalize();
		ray.origin = lens_point;
		ray.inv_dir = 1.f / ray_dir;
		ray.direction = ray_dir;
		ray.raytype = type;
		return ray;
    }

    /**
	 * Prints camera data
	 * this function implements the abstract function of the base Camera class
	 */
	void ThinLens::printCamera(){
		printf("I am a thin lens camera! \n");
		printf("width: %dpx, height: %dpx, fov:%d \n", width, height, fov);
	}

} //namespace rt
