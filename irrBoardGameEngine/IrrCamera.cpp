#include "IrrCamera.h"

using namespace IrrBoardGameEngine;

IrrCamera::IrrCamera(ICameraSceneNode *n){
	this->node = n;
}


IrrCamera::~IrrCamera(void)
{
}

void IrrCamera::lookAt(Vector &v)
{
	this->node->setTarget(vector3df(v.x,v.y,v.z));
}
