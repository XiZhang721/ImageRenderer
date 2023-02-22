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

    BlinnPhong(float ks, float kd, float kr, int specularexponent, Vec3f diffusecolor, std::string tPath, int tWidth, int tHeight):
        ks(ks), kd(kd), kr(kr), specularexponent(specularexponent), diffusecolor(diffusecolor), tPath(tPath), tWidth(tWidth), tHeight(tHeight){};

    float ks;
    float kd;
    float kr;
    int specularexponent;
    Vec3f diffusecolor;
    std::string tPath;
    int tWidth;
    int tHeight;   

private:
    


};



} //namespace rt



#endif /* BLINNPHONG_H_ */
