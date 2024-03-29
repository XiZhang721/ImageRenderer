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
 * 
 * @param scene the scene to render, including objects and lightsources
 * 
 * @param nbounces the number of bounces to consider for raytracing
 *
 * @return a pixel buffer containing pixel values in linear RGB format
 */
Vec3f* RayTracer::render(Camera* camera, Scene* scene, int nbounces){
	int jitterNumber = camera->getJittering();
	int cameraWidth = camera->getWidth();
	int cameraHeight = camera->getHeight();
	int totalPixel = cameraWidth * cameraHeight;
	Vec3f* pixelbuffer=new Vec3f[cameraWidth * cameraHeight];
	std::printf("CameraType: %d\n", camera->getType());
	int progress = 0;
	int jitterXNum = 0;
	int jitterYNum = 0;
	if(jitterNumber > 0){
		jitterXNum = (int)std::sqrt(jitterNumber);
		jitterYNum = (int)(jitterNumber / jitterXNum);
	}
	std::printf("Total jittering num: %d \nJitter x num: %d\nJitter y num: %d\n",jitterNumber, jitterXNum, jitterYNum);
	// Start rendering
	if(camera->getType() == 0){
		//----------phinhole camera------
		for(int y = 0; y < cameraHeight; y++){
			for(int x = 0; x < cameraWidth; x++){
				if(jitterNumber <= 0){
					// no camera jittering
					Ray ray = camera->createRay(x, y, PRIMARY,0,0,0,0);
					Vec3f hitColor = RayTracer::castRay(ray, scene, 0, nbounces);
					int pixelIndex = y * cameraWidth + x;
					pixelbuffer[pixelIndex] = hitColor;
					
					// progress printing
					if(((float)pixelIndex / (float)totalPixel) * 100.f > (float)progress){
						progress += 1;
						std::printf("Progress: %d%%\n",progress);
					}
				}else{
					// camera jittering
					Vec3f pixelColor = Vec3f(0.f,0.f,0.f);
					for(int sampleY = 0; sampleY < jitterYNum; sampleY ++){
						for(int sampleX = 0; sampleX < jitterXNum; sampleX ++){
							Ray ray = camera->createRay(x,y,PRIMARY, sampleX, sampleY, jitterXNum, jitterYNum);
							Vec3f hitColor = RayTracer::castRay(ray, scene, 0, nbounces);
							pixelColor = pixelColor + hitColor;
						}
					}
					float jitterNum = (float)(jitterYNum * jitterXNum);
					int pixelIndex = y * cameraWidth + x;
					pixelbuffer[pixelIndex] = pixelColor / jitterNum;

					// progress printing
					if(((float)pixelIndex / (float)totalPixel) * 100.f > (float)progress){
						progress += 1;
						std::printf("Progress: %d%%\n",progress);
					}
				}
			}
		}
	}else{
		//----------thin lens camera------
		int sampleNumber = 3;
		for(int y = 0; y < cameraHeight; y++){
			for(int x = 0; x < cameraWidth; x++){
				Vec3f colorSum = Vec3f(0.f,0.f,0.f);
				for(int z = 0; z < sampleNumber; z++){
					if(jitterNumber <= 0){
						// no jittering
						Ray ray = camera->createRay(x, y, PRIMARY,0,0,0,0);
						Vec3f hitColor = RayTracer::castRay(ray, scene, 0, nbounces);
						colorSum = colorSum + hitColor;
					}else{
						// with jittering
						Vec3f jitterSum = Vec3f(0.f,0.f,0.f);
						for(int sampleY = 0; sampleY < jitterYNum; sampleY ++){
							for(int sampleX = 0; sampleX < jitterXNum; sampleX ++){
								Ray ray = camera->createRay(x,y,PRIMARY, sampleX, sampleY, jitterXNum, jitterYNum);
								Vec3f hitColor = RayTracer::castRay(ray, scene, 0, nbounces);
								jitterSum = jitterSum + hitColor;
							}
						}
						float jitterNum = (float)(jitterYNum * jitterXNum);
						colorSum = colorSum + (jitterSum / jitterNum);
					}
				}
				int pixelIndex = y * cameraWidth + x;
				pixelbuffer[pixelIndex] = colorSum / (float) sampleNumber;

				// progress printing
				if(((float)pixelIndex / (float)totalPixel) * 100.f > (float)progress){
					progress += 1;
					std::printf("Progress: %d%%\n",progress);
				}
			}
		}
	}

	return pixelbuffer;

}

/**
 * The cast ray function
 * 
 * @param ray the ray to cast
 * 
 * @param scene the scene
 * 
 * @param depth the current depth of the ray
 * 
 * @param nbounces the total nbounces that the ray can have
 * 
 * @return the color of ray casting result
*/
Vec3f RayTracer::castRay(Ray ray, Scene* scene, int depth,int nbounces){
	if(depth > nbounces){
		return scene->backgroundColor;
	}

	// Return background color if ray not hit
	Hit hit = scene->intersect(ray);
	if(!hit.hasHit){
		return scene->backgroundColor;
	}

	Vec3f Ia = scene->backgroundColor;
	Vec3f Id = Vec3f(0.f,0.f,0.f);
	Vec3f Is = Vec3f(0.f,0.f,0.f);
	Vec3f refraction = Vec3f(0.f,0.f,0.f);

	BlinnPhong *material = (BlinnPhong *) hit.material;
	float ka = material->ka;
	float kt = 1.f - ka;
	Vec3f color{};
	Vec3f reflection = scene->backgroundColor;

	// Ray casting for each light source
	for(LightSource *light : scene->getLightSources()){
		Vec3f light_dir = (hit.point - light->position).normalize();
		float distance = (hit.point - light->position).length();
		Vec3f lightColor = Vec3f(1.f,1.f,1.f);
		float attenuation = 1.f / (distance * distance * 10.f);

		Ray shadowRay;
		shadowRay.origin = light->position;
		shadowRay.direction = light_dir;
		shadowRay.inv_dir = 1.f / light_dir;
		shadowRay.raytype = SHADOW;


		// Check if ray's hit point can be seen by light
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

		// Refraction
		if(kt > 0.f && nbounces > 0){
			Vec3f ray_dir = (hit.point - ray.origin).normalize();
			Vec3f normal = hit.normal;
			float n1 = 1.f;
			float n2 = material->refractionIndex;
			if(ray.isInside){
				std::swap(n1,n2);
			}
			float cosi = -normal.dotProduct(ray_dir);
			float n = n1 / n2;
			float k = 1.f - n * n * (1.f - cosi * cosi);
			if(k >= 0.f){
				// The refraction
				Vec3f refract_dir = (n * -ray_dir + (n * cosi - std::sqrt(k)) * normal).normalize();
				Ray refract_ray;
				refract_ray.direction = refract_dir;
				refract_ray.inv_dir = 1.f / refract_dir;
				refract_ray.origin = hit.point;
				refract_ray.raytype = SECONDARY;
				refract_ray.isInside = !ray.isInside;
				refraction = refraction + castRay(refract_ray, scene, depth + 1, nbounces);
			}else{
				// The internal reflection
				Vec3f reflect_dir = (2.f * normal.dotProduct(ray_dir) * normal - ray_dir).normalize();
				Ray reflect_ray;
				reflect_ray.direction = reflect_dir;
				reflect_ray.inv_dir = 1.f/reflect_dir;
				reflect_ray.origin = hit.point;
				reflect_ray.raytype = SECONDARY;
				reflect_ray.isInside = ray.isInside;
				refraction = refraction + ka * castRay(reflect_ray, scene, depth+1, nbounces);
			}
		}
	}
	
	// Compute the final color and return
	color = (Ia + Id + Is + reflection) * ka + kt * refraction;
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
	}

	return pixelbuffer;

}





} //namespace rt


