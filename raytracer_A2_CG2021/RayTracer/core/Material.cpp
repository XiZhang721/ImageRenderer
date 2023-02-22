/*
 * Material.cpp
 *
 */
#include "Material.h"
#include "materials/BlinnPhong.h"
namespace rt{

    Material* Material::createMaterial(Value& materialSpecs){
        float ks = materialSpecs["ks"].GetFloat();
        float kd = materialSpecs["kd"].GetFloat();
        float kr;
        if(materialSpecs.HasMember("kr")){
            kr = materialSpecs["kr"].GetFloat();
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
        return new BlinnPhong(ks,kd,kr,specularexponent,diffusecolor,tPath,tWidth,tHeight);
        
    }




} //namespace rt


