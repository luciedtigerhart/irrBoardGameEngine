#include "TokenNoob.h"

void TokenNoob::init(void)
{
	token->node = smgr->addMeshSceneNode(smgr->getMesh("obj/token01.obj"),token->parentNode->node,-1,vector3df(0,0,0));
	token->node->setParent(token->parentNode->node);

	ITriangleSelector* selector = smgr->createTriangleSelectorFromBoundingBox(token->node);
	token->node->setTriangleSelector(selector);
	selector->drop();
}

void TokenNoob::update(void)
{
	// Movimenta��o
	float dT = IrrEngine::getInstance()->getDeltaTime();

	if(token->isHighlighted)
	{		
		token->node->setMaterialFlag(irr::video::EMF_WIREFRAME,true);
	}
	else
	{
		token->node->setMaterialFlag(irr::video::EMF_WIREFRAME,false);
	}
}