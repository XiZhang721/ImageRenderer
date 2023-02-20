/*
 * LightSource.cpp
 *
 */
#include "LightSource.h"
#include "lights/PointLight.h"

namespace rt{
    LightSource* LightSource::createLightSource(Value& lightSpecs){
        if(!lightSpecs.HasMember("type")){
            std::cerr<<"Light source type not specified"<<std::endl;
		    exit(-1);
        }

        std::string lightType=lightSpecs["type"].GetString();

        if(lightType.compare("pointlight") == 0){
            Vec3f pos{lightSpecs["position"][0].GetFloat(),lightSpecs["position"][1].GetFloat(),lightSpecs["position"][2].GetFloat()};
            Vec3f is{lightSpecs["is"][0].GetFloat(),lightSpecs["is"][1].GetFloat(),lightSpecs["is"][2].GetFloat()};
            Vec3f id{lightSpecs["id"][0].GetFloat(),lightSpecs["id"][1].GetFloat(),lightSpecs["id"][2].GetFloat()};
            return new PointLight(pos,is,id);
        }

        return 0;
    }
    




} //namespace rt

