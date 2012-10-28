#include "TokenNoob.h"

void TokenNoob::init(void)
{
	token->node = smgr->addMeshSceneNode(smgr->getMesh("obj/token01.obj"),token->parentNode->node,-1,vector3df(0,0,0));
	token->node->setParent(token->parentNode->node);

	ITriangleSelector* selector = smgr->createTriangleSelectorFromBoundingBox(token->node);
	token->node->setTriangleSelector(selector);
	selector->drop();

	flag_cor = false;
}

void TokenNoob::update(void)
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

		if(flag_cor == true)	
		{
			token->node->setMaterialFlag(irr::video::EMF_WIREFRAME,true);
		}
	}
}

void TokenNoob::setInt(char const * key, int value)
{
	//
}

int TokenNoob::getInt(char const * key)
{
	return 0;
}

void TokenNoob::setBool(char const * key, bool value)
{
	if (key == "flag_cor")
	{
		flag_cor = value;
	}
	else if (key == "flag_estado")
	{
		flag_estado = value;
	}
}

bool TokenNoob::getBool(char const * key)
{
	if (key == "flag_cor")
	{
		return flag_cor;
	}
	else if (key == "flag_estado")
	{
		return flag_estado;
	}
	else return false;
}