/*
 * Material.cpp
 *
 */
#include "Material.h"
#include "materials/BlinnPhong.h"
namespace rt{

	/**
 	* Factory function that returns material subclass based on material specifications
 	*
 	* @param materialSpecs material specifications json object
 	*
 	* @return material subclass instance
 	*
 	*/
    Material* Material::createMaterial(Value& materialSpecs){
        float ks = materialSpecs["ks"].GetFloat();
        float kd = materialSpecs["kd"].GetFloat();
        float kr = -1.f;;
        if(materialSpecs.HasMember("kr")){
            kr = materialSpecs["kr"].GetFloat();
        }
        float ka = 1.f;
        if(materialSpecs.HasMember("ka")){
            ka = materialSpecs["ka"].GetFloat();
        }
        float refractionIndex = 1.f;
        if(materialSpecs.HasMember("refractionindex")){
            refractionIndex = materialSpecs["refractionindex"].GetFloat();
        }
        int specularexponent = materialSpecs["specularexponent"].GetInt();
        Vec3f diffusecolor = {materialSpecs["diffusecolor"][0].GetFloat(),
            materialSpecs["diffusecolor"][1].GetFloat(),
            materialSpecs["diffusecolor"][2].GetFloat()};
        std::string tPath;
        int tWidth;
        int tHeight;
        if(materialSpecs.HasMember("tPath")){
            tPath = materialSpecs["tPath"].GetString();
            tWidth = materialSpecs["tWidth"].GetInt();
            tHeight = materialSpecs["tHeight"].GetInt();
        }
        return new BlinnPhong(ks,kd,kr,ka,refractionIndex,specularexponent,diffusecolor,tPath,tWidth,tHeight);
        
    }




} //namespace rt


