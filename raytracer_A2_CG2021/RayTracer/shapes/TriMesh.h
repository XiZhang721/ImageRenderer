/*
 * TriMesh.h
 *
 *
 */

#ifndef TRIMESH_H_
#define TRIMESH_H_

#include "core/Shape.h"
#include "parsers/happly.h"
#include "BVH.h"
#include "Triangle.h"
#include <vector>

namespace rt{

class TriMesh: public Shape{
public:
    TriMesh();
    TriMesh(Vec3f position, float scale, std::string path, Material *material);

    void createMesh(std::string path);
    virtual ~TriMesh(){};
	//
	// Functions that need to be implemented, since Sphere is a subclass of Shape
	//
	Hit intersect(Ray ray);
	Vec3f getCenter(){
		return this->center;
	};

private:
    Vec3f position;
    Vec3f center;
    float scale;
    std::vector<Shape *> triangles;
    BVH* bvh;

};



} //namespace rt




#endif /* TRIMESH_H_ */
