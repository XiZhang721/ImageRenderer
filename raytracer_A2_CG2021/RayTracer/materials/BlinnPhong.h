/*
 * BlinnPhong.h
 *
 *
 */

#ifndef BLINNPHONG_H_
#define BLINNPHONG_H_

#include "core/Material.h"
#include "math/geometry.h"


namespace rt{

class BlinnPhong: public Material{

public:
    BlinnPhong();
    BlinnPhong(float ks, float kd, float kr, int specularexponent, Vec3f diffusecolor, std::string tPath, int tWidth, int tHeight);

    Vec3f GetDiffuseColor() const {return diffusecolor;};
    float ks;
    float kd;
    float kr;
    int specularexponent;
    Vec3f diffusecolor;
    std::string tPath;
    int tWidth;
    int tHeight;   

    Vec3f* texture;

private:
    


};



} //namespace rt



#endif /* BLINNPHONG_H_ */
