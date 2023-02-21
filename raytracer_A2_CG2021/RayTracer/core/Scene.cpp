/*
 * Scene.cpp
 *
 */
#include "Scene.h"




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
	// if(scenespecs.HasMember("shapes")){
	// 	const Value& shapesFromJson = scenespecs["shapes"];
	// 	for (int i = 0; i < shapesFromJson.Size(); i++){
	// 		shapes.push_back(Shape::createShape)
	// 	}
	// }

}



} //namespace rt
