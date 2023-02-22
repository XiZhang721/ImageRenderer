/*
 * Shape.cpp
 *
 */
 
#include "Shape.h"
#include "shapes/Sphere.h"
#include "Material.h"




namespace rt{
    Shape::~Shape(){};

    Shape* Shape::createShape(Value& shapeSpecs){
        if(!shapeSpecs.HasMember("type")){
            std::cerr<<"Shape type not specified"<<std::endl;
		    exit(-1);
        }

        std::string shapeType = shapeSpecs["type"].GetString();

        if(shapeType.compare("sphere") == 0){
            Vec3f center = {shapeSpecs["center"][0].GetFloat(),shapeSpecs["center"][1].GetFloat(),shapeSpecs["center"][2].GetFloat()};
            float radius = shapeSpecs["radius"].GetFloat();
            Material *material = Material::createMaterial((Value&) shapeSpecs["material"]);
            return new Sphere(center,radius, material);
        }
        return nullptr;
    }









} //namespace rt

