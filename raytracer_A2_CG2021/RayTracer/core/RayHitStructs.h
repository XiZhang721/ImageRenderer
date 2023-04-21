/*
 * RayHitStructs.h
 */

#ifndef CORE_RAYHITSTRUCTS_H_
#define CORE_RAYHITSTRUCTS_H_

#include "math/geometry.h"
#include "Material.h"

namespace rt{

/*
 * Ray structure definition
 */
enum RayType {PRIMARY, SECONDARY, SHADOW};

struct Ray{
public:
	Vec3f origin;
	Vec3f direction;
	Vec3f inv_dir; // the inversed direction
	RayType raytype;
	bool isInside = false;
};


struct Hit{
	Vec3f point; //point where ray hits a shape
	bool hasHit; // if the ray hits an object
	Vec3f normal;
	Material *material;
	float u;
	float v;
};

}


#endif /* CORE_RAYHITSTRUCTS_H_ */
