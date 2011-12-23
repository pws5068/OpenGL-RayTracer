#ifndef TRIANGLE
#define TRIANGLE

#include "rtObject.h"
#include "scene.h"

class triangle : public rtObject
{
public:
	//constructor given points in 3d space and corresponding
	//locations on the texture surface
	triangle(Vec3f p0, Vec3f p1, Vec3f p2, float tx0, float tx1, float tx2, float ty0, float ty1, float ty2, int m, scene* s);

	//see descriptions in rtObject
	float testIntersection(Vec3f eye, Vec3f dir);
	Vec3f getNormal(Vec3f eye, Vec3f dir);
	Vec3f getTextureCoords(Vec3f eye, Vec3f dir);

private:
	//the points in 3d space that define the triangle
	Vec3f point0, point1, point2;
	//the x-y locations on the texture image corresponding to each vertex
	float texX0, texX1, texX2, texY0, texY1, texY2;
};

#endif