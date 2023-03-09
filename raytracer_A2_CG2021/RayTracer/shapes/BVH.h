/*
 * BVH.h
 *
 *
 */

#ifndef BVH_H_
#define BVH_H_

#include <vector>
#include "core/Shape.h"


namespace rt{

    struct BoundingBox{
        Vec3f min;
        Vec3f max;
    };

    struct BVHNode{
        BoundingBox box;
        BVHNode* left;
        BVHNode* right;
        Shape* shape;
        bool isEmpty;
        bool hasShape;
    };

class BVH: public Shape{

public:

    BVH(std::vector<Shape*> shapes){
        root = BuildBVHTree(shapes);
    };

    virtual ~BVH(){};

    static BVHNode* BuildBVHTree(std::vector<Shape*> shapes);

    Hit intersect(Ray ray){
        return getIntersect(ray, root);
    };
    static Hit getIntersect(Ray ray, BVHNode* node);

    static bool checkBounding(Ray ray, BoundingBox box);

    Vec3f getCenter(){
        return Vec3f{0.f,0.f,0.f};
    }
    std::vector<Shape*> BVHShapes;
    BVHNode* root;

};



} //namespace rt



#endif /* BVH_H_ */
