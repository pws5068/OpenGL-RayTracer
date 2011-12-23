#ifndef SPHERE
#define SPHERE

#include "rtObject.h"
#include "scene.h"

class sphere : public rtObject
{
public:
	//constructor given  center, radius, and material
	sphere(Vec3f c, float r, int m, scene* s);

	//see descriptions in rtObject
	float testIntersection(Vec3f eye, Vec3f dir);
	Vec3f getNormal(Vec3f eye, Vec3f dir);
	Vec3f getTextureCoords(Vec3f eye, Vec3f dir);

private:
	Vec3f center;
	float radius;
};

#endif