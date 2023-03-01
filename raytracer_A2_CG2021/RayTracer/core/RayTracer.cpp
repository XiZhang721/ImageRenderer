/*
 * RayTracer.cpp
 *
 */
#include <iostream>
#include "RayTracer.h"
#include "RayHitStructs.h"
#include "materials/BlinnPhong.h"
#include "shapes/Sphere.h"
#include "Material.h"
#include <math.h>


namespace rt{


/**
 * Performs ray tracing to render a photorealistic scene
 *
 * @param camera the camera viewing the scene
 * @param scene the scene to render, including objects and lightsources
 * @param nbounces the number of bounces to consider for raytracing
 *
 * @return a pixel buffer containing pixel values in linear RGB format
 */
Vec3f* RayTracer::render(Camera* camera, Scene* scene, int nbounces){
	int cameraWidth = camera->getWidth();
	int cameraHeight = camera->getHeight();
	Vec3f* pixelbuffer=new Vec3f[cameraWidth * cameraHeight];


	//----------main rendering function to be filled------
	for(int y = 0; y < cameraHeight; y++){
		for(int x = 0; x < cameraWidth; x++){
			Ray ray = camera->createRay(x, y, PRIMARY);
			Vec3f hitColor = RayTracer::castRay(ray, scene, nbounces);
			pixelbuffer[y * cameraWidth + x] = hitColor;
			//std::printf("Progress: %d\n",y* cameraWidth + column);
		}
	}




	return pixelbuffer;

}

Vec3f RayTracer::castRay(Ray ray, Scene* scene, int nbounces){
	if(nbounces <= 0){
		return scene->backgroundColor;
	}
	Hit hit = scene->intersect(ray);
	if(!hit.hasHit){
		return scene->backgroundColor;
	}

	BlinnPhong *material = (BlinnPhong *) hit.material;
	Vec3f color = material->GetDiffuseColor();
	float Ia = 0.f;
	for(LightSource *light : scene->getLightSources()){
		Vec3f lightDir = (hit.point-light->position).normalize();
		lightDir = lightDir.normalize();		

		Ray shadowRay;
		shadowRay.origin = light->position;
		shadowRay.direction = lightDir;
		shadowRay.raytype = SHADOW;
		Hit shadowHit = scene->intersect(shadowRay);
		if(shadowHit.hasHit && checkTwoPoints(shadowHit.point, hit.point)){
			continue;
		}else{
			color = scene->backgroundColor;
		}
		
		
	}
	return color;
}

/**
 * Tonemaps the rendered image (conversion of linear RGB values [0-1] to low dynamic range [0-255]
 *
 * @param pixelbuffer the array of size width*height containing linear RGB pixel values
 *
 * @return the tonemapped image
 */
Vec3f* RayTracer::tonemap(Vec3f* pixelbuffer, int cameraWidth, int cameraHeight){

	//---------tonemapping function to be filled--------

	int pixelCount = cameraWidth * cameraHeight;
	for(int i = 0; i < pixelCount; i++){
		Vec3f pixel = pixelbuffer[i];
		pixel *=255.f;
		for(int j = 0; j < 3; j++){
			pixel[j] = (float)std::max((int)pixel[j],0);
			pixel[j] = (float)std::min((int)pixel[j],255);
		}
		pixelbuffer[i] = pixel;
		//std::printf("Progress: %d\n",i);
	}

	return pixelbuffer;

}





} //namespace rt


