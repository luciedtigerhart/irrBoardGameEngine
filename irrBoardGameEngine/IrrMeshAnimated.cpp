#include "IrrMeshAnimated.h"

using namespace IrrBoardGameEngine;

IrrMeshAnimated::IrrMeshAnimated(IAnimatedMeshSceneNode * c)
{
	this->node = c;
}

IrrMeshAnimated::~IrrMeshAnimated(void)
{

}

void IrrMeshAnimated::setPosition(Vector &p)
{
	this->node->setPosition(vector3df(p.x,p.y,p.z));
}

void IrrMeshAnimated::setScale(Vector &p)
{
	this->node->setScale(vector3df(p.x,p.y,p.z));
}

void IrrMeshAnimated::setRotation(Vector &p)
{
	this->node->setRotation(vector3df(p.x,p.y,p.z));
}
