#include "TokenDummy.h"

void TokenDummy::init(void)
{
	token->node = smgr->addMeshSceneNode(smgr->getMesh("obj/token02.obj"),token->parentNode,-1,vector3df(0,0,0));
	token->node->setParent(token->parentNode);
}

void TokenDummy::update(void)
{
	// Movimentação
	float dT = IrrEngine::getInstance()->getDeltaTime();
}