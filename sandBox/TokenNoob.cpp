#include "TokenNoob.h"

void TokenNoob::init(void)
{
	token->node = smgr->addMeshSceneNode(smgr->getMesh("obj/token01.obj"),token->parentNode,-1,vector3df(0,0,0));
	token->node->setParent(token->parentNode);
}

void TokenNoob::update(void)
{
	// Movimentação
	float dT = IrrEngine::getInstance()->getDeltaTime();
}
