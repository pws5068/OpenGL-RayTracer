#ifndef RTOBJECT
#define RTOBJECT

#include "util_vectors.h"

class scene;

//object is a virtual class: it is never used, except as a subclass
class rtObject
{
public:
	//virtual class so constructor is unusable
	rtObject(scene* s);

	//returns the distance to the object from the eye
	//or 9999999 if no intersection
	virtual float testIntersection(Vec3f eye, Vec3f dir)=0;

	//returns the normal of the point on the object seen by this eye
	virtual Vec3f getNormal(Vec3f eye, Vec3f dir)=0;

	//returns the position on the texture image from which to get the color
	//first value is x, second is y, third is zero (not needed)
	virtual Vec3f getTextureCoords(Vec3f eye, Vec3f dir)=0;

	//accessor for material index
	int getMatIndex();

protected:
	scene* myScene;
	int matIndex;

};



#endif