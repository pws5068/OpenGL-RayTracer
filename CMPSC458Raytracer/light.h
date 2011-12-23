#ifndef LIGHT
#define LIGHT

#include "util_vectors.h"

//struct that holds a 3D location and an RGB color
struct light
{
	Vec3f position, color;
};

#endif