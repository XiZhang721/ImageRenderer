/*
 * RayTracer.h
 *
 */
#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include "math/geometry.h"
#include "core/Camera.h"
#include "core/Scene.h"
#include <math.h>

namespace rt{



/*
 * Raytracer class declaration
 */
class RayTracer {
public:

	RayTracer();

	static Vec3f* render(Camera* camera, Scene* scene, int nbounces);
	static Vec3f* tonemap(Vec3f* pixelbuffer, int cameraWidth, int cameraHeight);

	static Vec3f castRay(Ray ray, Scene* scene,int depth, int nbounces);
private:
	static bool checkTwoPoints(Vec3f p1, Vec3f p2){
		bool isXSame = abs(p1.x - p2.x) <= 1e-3f;
		bool isYSame = abs(p1.y - p2.y) <= 1e-3f;
		bool isZSame = abs(p1.z - p2.z) <= 1e-3f;
		return isXSame && isYSame && isZSame;
	}
};




} //namespace rt



#endif /* RAYTRACER_H_ */

