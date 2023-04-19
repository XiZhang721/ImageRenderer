/*
 * BlinnPhong.cpp
 *
 *
 */

#include "BlinnPhong.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


namespace rt{

    BlinnPhong::BlinnPhong(float ks, float kd, float kr, float ka, float refractionIndex, int specularexponent, Vec3f diffusecolor, std::string tPath, int tWidth, int tHeight)
    {
        this->ks = ks;
        this->kd = kd;
        this->kr = kr;
        this->ka = ka;
        this->refractionIndex = refractionIndex;
        this->specularexponent = specularexponent;
        this->diffusecolor = diffusecolor;
        this->tPath = tPath;
        this->tWidth = tWidth;
        this->tHeight = tHeight;

        if(tPath.length()>0){
            int x,y,channels;
            const char* path = tPath.c_str();
            stbi_uc* image = stbi_load(path, &x, &y, &channels, 3);
            if(image == NULL){
                return;
            }
            texture = new Vec3f[tWidth * tHeight];
            for(int i = 0; i< tHeight; i++){
                for(int j = 0; j < tWidth; j++){
                    int index = i * tWidth * 3 + j * 3;
                    float r = (float) image[index] / 255.f;
                    float g = (float) image[index+1] / 255.f;
                    float b = (float) image[index+2] / 255.f;
                    texture[i * tWidth + j] = {r,g,b};
                }
            }
            stbi_image_free(image);
        }
    }

} // namespace rt
