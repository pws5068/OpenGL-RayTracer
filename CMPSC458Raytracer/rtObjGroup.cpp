#include "rtObjGroup.h"

//default constructor
rtObjGroup::rtObjGroup()  
{}

//add an object to the vector
void rtObjGroup::addObj(rtObject *o)
{
	myObjects.push_back(o);
}

//accessor for objects in the vector
rtObject* rtObjGroup::getObj(int index)
{
	return myObjects.at(index);
}

float rtObjGroup::testIntersections(Vec3f eye, Vec3f dir)
{
	float closest = 9999999;
	float currentDist;
	//test intersection distance with every object in the group
	for (int iter=0; iter<myObjects.size(); iter++)
	{
		currentDist = myObjects.at(iter)->testIntersection(eye, dir);
		//keep track of closest distance and remember index of closest object
		if (currentDist<closest)
		{
			closest = currentDist;
			indexOfClosest = iter;
		}
	}
	return closest;
}

//returns the object that was closest in the last call to testIntersections
rtObject* rtObjGroup::getClosest()
{
	return myObjects.at(indexOfClosest);
}