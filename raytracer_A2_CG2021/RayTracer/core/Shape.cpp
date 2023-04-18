/*
 * Shape.cpp
 *
 */
 
#include "Shape.h"
#include "shapes/Sphere.h"
#include "shapes/Plane.h"
#include "shapes/Triangle.h"
#include "shapes/TriMesh.h"
#include "Material.h"




namespace rt{
    Shape::~Shape(){};

    Shape* Shape::createShape(Value& shapeSpecs){
        if(!shapeSpecs.HasMember("type")){
            std::cerr<<"Shape type not specified"<<std::endl;
		    exit(-1);
        }

        std::string shapeType = shapeSpecs["type"].GetString();
        std::printf("Loading shape: %s\n", shapeType.c_str());
        if(shapeType.compare("sphere") == 0){
            Vec3f center = {shapeSpecs["center"][0].GetFloat(),shapeSpecs["center"][1].GetFloat(),shapeSpecs["center"][2].GetFloat()};
            float radius = shapeSpecs["radius"].GetFloat();
            Material *material = Material::createMaterial((Value&) shapeSpecs["material"]);
            return new Sphere(center,radius, material);
        }else if(shapeType.compare("plane") == 0){
            Vec3f v0 = {shapeSpecs["v0"][0].GetFloat(),shapeSpecs["v0"][1].GetFloat(),shapeSpecs["v0"][2].GetFloat()};
            Vec3f v1 = {shapeSpecs["v1"][0].GetFloat(),shapeSpecs["v1"][1].GetFloat(),shapeSpecs["v1"][2].GetFloat()};
            Vec3f v2 = {shapeSpecs["v2"][0].GetFloat(),shapeSpecs["v2"][1].GetFloat(),shapeSpecs["v2"][2].GetFloat()};
            Vec3f v3 = {shapeSpecs["v3"][0].GetFloat(),shapeSpecs["v3"][1].GetFloat(),shapeSpecs["v3"][2].GetFloat()};
            Material *material = Material::createMaterial((Value&) shapeSpecs["material"]);
            return new Plane(v0,v1,v2,v3,material);
        }else if(shapeType.compare("triangle") == 0){
            Vec3f v0 = {shapeSpecs["v0"][0].GetFloat(),shapeSpecs["v0"][1].GetFloat(),shapeSpecs["v0"][2].GetFloat()};
            Vec3f v1 = {shapeSpecs["v1"][0].GetFloat(),shapeSpecs["v1"][1].GetFloat(),shapeSpecs["v1"][2].GetFloat()};
            Vec3f v2 = {shapeSpecs["v2"][0].GetFloat(),shapeSpecs["v2"][1].GetFloat(),shapeSpecs["v2"][2].GetFloat()};
            Material *material = Material::createMaterial((Value&) shapeSpecs["material"]);
            return new Triangle(v0,v1,v2,material);
        }else if(shapeType.compare("mesh") == 0){
            Vec3f position = {shapeSpecs["position"][0].GetFloat(),shapeSpecs["position"][1].GetFloat(),shapeSpecs["position"][2].GetFloat()};
            float scale = shapeSpecs["scale"].GetFloat();
            std::string path = shapeSpecs["path"].GetString();
            Material *material = Material::createMaterial((Value&) shapeSpecs["material"]);
            return new TriMesh(position,scale,path,material);
        }
        return nullptr;
    }









} //namespace rt

