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
	RayType raytype;


	//----------Ray variables to be filled------
};


struct Hit{

	Vec3f point; //point where ray hits a shape
	//----------Hit variables to be filled------
	bool hasHit; // if the ray hits an object
	Vec3f normal;
	Material *material;
};

}


#endif /* CORE_RAYHITSTRUCTS_H_ */
