/*
 * Scene.cpp
 *
 */
#include "Scene.h"
#include "RayHitStructs.h"
#include "shapes/Sphere.h"
#include "shapes/Plane.h"
#include "Material.h"
#include "materials/BlinnPhong.h"



namespace rt{

/**
 * Parses json scene object to generate scene to render
 *
 * @param scenespecs the json scene specificatioon
 */
void Scene::createScene(Value& scenespecs){

	//----------parse json object to populate scene-----------
	if(scenespecs.HasMember("backgroundcolor")){
		const Value& backgroundFromJson = scenespecs["backgroundcolor"];
		backgroundColor = Vec3f(backgroundFromJson[0].GetFloat(), backgroundFromJson[1].GetFloat(), backgroundFromJson[2].GetFloat());
	}

	if(scenespecs.HasMember("lightsources")){
		const Value& lightsFromJson = scenespecs["lightsources"];
		for (int i = 0; i < lightsFromJson.Size(); i++){
			lightSources.push_back(LightSource::createLightSource((Value&) lightsFromJson[i]));
		}
	}
	if(scenespecs.HasMember("shapes")){
		const Value& shapesFromJson = scenespecs["shapes"];
		for (int i = 0; i < shapesFromJson.Size(); i++){
			Shape *currShape = Shape::createShape((Value&) shapesFromJson[i]);
			if(!currShape->isMesh()){
				shapes.push_back(currShape);
			}else{
				shapes.push_back(currShape);
			}
		}
	}
	std::printf("Scene creation finished\n");
	this->bvh  = new BVH(shapes);
}

Hit Scene::intersect(Ray ray){

	// Use the standard ray hit
	// Hit hit;
	// hit.hasHit = false;
	// double rayDistance = INFINITY;
	// for (Shape *shape : shapes){
	// 	Hit h = shape -> intersect(ray);
	// 	if(h.hasHit){
	// 		float distance = (h.point - ray.origin).length();
	// 		if(distance <= 1e-3){
	// 			continue;
	// 		}
	// 		if(distance < rayDistance){
	// 			rayDistance = distance;
	// 			hit.point = h.point;
	// 			hit.material = h.material;
	// 			hit.normal = h.normal;
	// 			hit.hasHit = true;
	// 			hit.u = h.u;
	// 			hit.v = h.v;
	// 		}
	// 	}
	// }
	// return hit;

	//Using BVH for ray hit
	return this->bvh->intersect(ray);
}



} //namespace rt
