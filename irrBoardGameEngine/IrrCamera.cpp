#include "IrrCamera.h"
#include "IrrEngine.h"

using namespace IrrBoardGameEngine;

IrrCamera::IrrCamera(ICameraSceneNode *n){
	this->node = n;

	ip = IrrEngine::getInstance()->getInput();
}


IrrCamera::~IrrCamera(void)
{
}

void IrrCamera::lookAt(Vector &v)
{
	this->node->setTarget(vector3df(v.x,v.y,v.z));
}

void IrrCamera::update()
{	
	if(ip->getMouseState().leftButtonDown)
	{
		//this->node->setRotation(vector3df(90.0,0,0.0));
	}
}