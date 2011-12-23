#ifndef MATERIAL
#define MATERIAL

#include <pic.h>
#include "util_vectors.h"

struct material
{
	//the image loaded using libpicio
	Pic* texture;
	//four RGB colors for different material properties
	Vec3f diffuseCol, specularCol, transparentCol, reflectiveCol;

	//the shininess (see illumination model)
	//and refraction index (look up refraction of light through materials)
	float shininess, refractionIndex;
};

#endif