#include "IrrMesh.h"

using namespace IrrBoardGameEngine;

IrrMesh::IrrMesh(IMeshSceneNode *c){
	this->node = c;
}


IrrMesh::~IrrMesh(void)
{
}

void IrrMesh::setPosition(Vector &p)
{
	this->node->setPosition(vector3df(p.x,p.y,p.z));
}

void IrrMesh::setScale(Vector &p)
{
	this->node->setScale(vector3df(p.x,p.y,p.z));
}

void IrrMesh::setRotation(Vector &p)
{
	this->node->setRotation(vector3df(p.x,p.y,p.z));
}