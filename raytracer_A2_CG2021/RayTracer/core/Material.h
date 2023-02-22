/*
 * Material.h
 *
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_
#include "rapidjson/document.h"


using namespace rapidjson;
namespace rt{

class Material{
public:
    Material(){};

    static Material* createMaterial(Value& materialSpecs);

    virtual ~Material(){};

private:
};


} //namespace rt



#endif /* MATERIAL_H_ */
