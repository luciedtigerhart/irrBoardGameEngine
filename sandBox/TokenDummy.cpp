#include "TokenDummy.h"

void TokenDummy::init(void)
{
	/*
	token->node = smgr->addMeshSceneNode(smgr->getMesh("obj/token02.obj"),token->parentNode->node,-1,vector3df(0,0,0));
	token->node->setParent(token->parentNode->node);
	*/

	IAnimatedMesh * ms = smgr->getMesh("obj/dwarf.x");

	IAnimatedMeshSceneNode * animNode = smgr->addAnimatedMeshSceneNode(ms,token->parentNode->node,-1,vector3df(0,0,0));
	token->node = animNode;
	token->node->setParent(token->parentNode->node);

	token->node->setScale(vector3df(0.05,0.05,0.05));

	//
	// SOMBRA
	//
	animNode->addShadowVolumeSceneNode(ms);

	ITriangleSelector* selector = smgr->createTriangleSelectorFromBoundingBox(token->node);
	token->node->setTriangleSelector(selector);
	selector->drop();
}

void TokenDummy::reset(void)
{
}

void TokenDummy::update(void)
{
	// Movimentação
	float dT = IrrEngine::getInstance()->getDeltaTime();

	if(token->isMouseHover)
	{		
		token->node->setMaterialFlag(irr::video::EMF_WIREFRAME,true);
	}
	else
	{
		token->node->setMaterialFlag(irr::video::EMF_WIREFRAME,false);
	}
}

void TokenDummy::setInt(char const * key, int value)
{
	//
}

int TokenDummy::getInt(char const * key)
{
	return 0;
}

void TokenDummy::setBool(char const * key, bool value)
{

}

bool TokenDummy::getBool(char const * key)
{
	return false;
}

void TokenDummy::setFloat(char const * key, float value)
{
	
}

float TokenDummy::getFloat(char const * key)
{
	return 0;
}

void TokenDummy::setVector(char const * key, Vector value)
{

}

Vector TokenDummy::getVector(char const * key)
{
	return Vector();
}