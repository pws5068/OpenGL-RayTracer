#include "triangle.h"

//constructor given  center, radius, and material
triangle::triangle(Vec3f p0, Vec3f p1, Vec3f p2, float tx0, float tx1, float tx2, float ty0, float ty1, float ty2, int m, scene* s) : rtObject(s)  
{
	point0 = p0;
	point1 = p1;
	point2 = p2;
	texX0 = tx0;
	texX1 = tx1;
	texX2 = tx2;
	texY0 = ty0;
	texY1 = ty1;
	texY2 = ty2;
	matIndex = m;
	myScene = s;
}

float triangle::testIntersection(Vec3f eye, Vec3f dir)
{
	//see the book/slides for a description of how to use Cramer's rule to solve
	//for the intersection(s) of a line and a plane, implement it here and
	//return the minimum distance (if barycentric coordinates indicate it hit
	//the triangle) otherwise 9999999

	return 9999999;
}

Vec3f triangle::getNormal(Vec3f eye, Vec3f dir)
{
	//construct the barycentric coordinates for the plane
	Vec3f bary1 = point1-point0;
	Vec3f bary2 = point2-point0;

	//cross them to get the normal to the plane
	//note that the normal points in the direction given by right-hand rule
	//(this can be important for refraction to know whether you are entering or leaving a material)
	Vec3f normal;
	Vec3f::Cross3(normal,bary1,bary2);
	normal.Normalize();

	return normal;
}

Vec3f triangle::getTextureCoords(Vec3f eye, Vec3f dir)
{
	//find alpha and beta (parametric distance along barycentric coordinates)
	//use these in combination with the known texture surface location of the vertices
	//to find the texture surface location of the point you are seeing

	Vec3f coords;
	return coords;
}