#include "TokenDummy.h"

void TokenDummy::init(void)
{
	token->node = smgr->addMeshSceneNode(smgr->getMesh("obj/token02.obj"),token->parentNode->node,-1,vector3df(0,0,0));
	token->node->setParent(token->parentNode->node);

	ITriangleSelector* selector = smgr->createTriangleSelectorFromBoundingBox(token->node);
	token->node->setTriangleSelector(selector);
	selector->drop();
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