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


		// to fill

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

