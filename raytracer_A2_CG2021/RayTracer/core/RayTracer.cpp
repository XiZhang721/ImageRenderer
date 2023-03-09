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
#include <fstream>


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
			Vec3f hitColor = RayTracer::castRay(ray, scene, 0, nbounces);
			pixelbuffer[y * cameraWidth + x] = hitColor;
			//std::printf("Progress: %d\n",y* cameraWidth + column);
		}
	}




	return pixelbuffer;

}

Vec3f RayTracer::castRay(Ray ray, Scene* scene, int depth,int nbounces){
	if(depth > nbounces){
		return scene->backgroundColor;
	}
	Hit hit = scene->intersect(ray);
	if(!hit.hasHit){
		return scene->backgroundColor;
	}

	Vec3f Ia = scene->backgroundColor;
	Vec3f Id = Vec3f(0.f,0.f,0.f);
	Vec3f Is = Vec3f(0.f,0.f,0.f);

	BlinnPhong *material = (BlinnPhong *) hit.material;
	Vec3f color{};
	Vec3f reflection = scene->backgroundColor;
	for(LightSource *light : scene->getLightSources()){
		Vec3f light_dir = (hit.point-light->position).normalize();
		float distance = (hit.point - light->position).length();
		Vec3f lightColor = Vec3f(1.f,1.f,1.f);
		float attenuation = 1.f / (distance * distance * 10.f);
		Ray shadowRay;
		shadowRay.origin = light->position;
		shadowRay.direction = light_dir;
		shadowRay.inv_dir = 1.f / light_dir;
		shadowRay.raytype = SHADOW;
		Hit shadowHit = scene->intersect(shadowRay);
		if(shadowHit.hasHit && !checkTwoPoints(shadowHit.point, hit.point)){
			continue;
		}
		Vec3f normal = -shadowHit.normal.normalize();

		// Diffuse
		float diffuse_intensity = std::max(0.f,light_dir.dotProduct(normal));
		if(material->tPath.size() > 0){
			int x = hit.u * material->tWidth;
			int y = hit.v * material->tHeight;
			x = x % material->tWidth;
			y = y % material->tHeight;
			if(x < 0) x += material->tWidth;
			if(y < 0) y += material-> tHeight;
			int index = x + y * material-> tWidth;
			Id = Id + material->kd * light->id * diffuse_intensity * attenuation * material->texture[index];
		}else{
			Id = Id + material->kd * light->id * diffuse_intensity * attenuation * material->diffusecolor;
		}
					
		// Specular
		Vec3f view_dir = (ray.origin - hit.point).normalize();
		Vec3f reflect_dir = (light_dir -(2.f * light_dir.dotProduct(normal) * normal)).normalize();
		float specular_factor = std::pow(std::max(0.f, reflect_dir.dotProduct(view_dir)), material->specularexponent);
		Is = Is + material->ks * specular_factor * light->is * Vec3f(1.f,1.f,1.f) * (attenuation / 10.f);

		// Reflection
		if(material->kr > 0.f && nbounces > 0){
			Vec3f normal = hit.normal;
			Vec3f ray_dir = (hit.point - ray.origin).normalize();
			Vec3f reflect_dir = (ray_dir - (2.f * ray_dir.dotProduct(normal) * normal)).normalize();
			Ray reflect_ray;
			reflect_ray.direction = reflect_dir;
			reflect_ray.inv_dir = 1.f/reflect_dir;
			reflect_ray.origin = hit.point;
			reflect_ray.raytype = SECONDARY;
			Hit reflect_hit = scene->intersect(reflect_ray);
			if(reflect_hit.hasHit){
				Vec3f reflect_color = castRay(reflect_ray,scene,depth+1,nbounces);
				reflection = reflection +reflect_color * material->kr;
			}
		}
	}

	color = Ia + Id + Is + reflection;
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


