#include "rtObject.h"

rtObject::rtObject(scene* s)  
{
	myScene = s;
}

int rtObject::getMatIndex()
{
	return matIndex;
}