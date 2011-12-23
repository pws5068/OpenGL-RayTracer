#ifndef SCENE
#define SCENE

#include <pic.h>
#include "util_vectors.h"
#include "rtObjGroup.h"
#include "light.h"
#include "rtObject.h"
#include "sphere.h"
#include "triangle.h"
#include "material.h"

class sphere;
class triangle;

// For parsing purposes
#define MAX_PARSER_TOKEN_LENGTH 100

class scene
{
public:
	//constructor from a scene text file
	scene(const char* filename);

	//accessors for the camera properties
	Vec3f getEye();
	Vec3f getLookAt();
	Vec3f getUp();
	float getFovy();

	//returns the rgb color seen from this eye in this direction
	Vec3f rayTrace(Vec3f eye, Vec3f dir, int recurseDepth);

	//destructor
	~scene();

private:
	//some functions and variables used in parsing
	void parse(const char* filename);
	void eatWhitespace(void);
    int getToken(char token[MAX_PARSER_TOKEN_LENGTH]);
    Vec3f readVec3f();
    float readFloat();
    int readInt();
	void parseBackground();
	void parseCamera();
	rtObjGroup* parseGroup();
	sphere* parseSphere();
	void parseMaterials();
	void parseMaterialIndex();
	triangle* parseTriangle();
	void parseLights();
	FILE *file;
	int parse_char; //current character read from file
    int curline;    //current line in the file

	//!!!VERY USEFUL!!!
	//performs an element-wise multiplication of two vec3fs
	Vec3f multiplyColorVectors(Vec3f a, Vec3f b);

	//the group of objects that are part of the scene
	//you may want to utilize multiple groups for view volume segmentation
	rtObjGroup* myObjGroup;
	vector<material> myMaterials;
	vector<light> myLights;

	Vec3f bgColor; //background color
    Vec3f ambLight; //ambient light
    Vec3f eye; //camera location
    Vec3f lookAt; //camera looking at (x, y, z)
    Vec3f up; //camera up vector
    float fovy; //camera vertical angle of view

};

#endif