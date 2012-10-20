#include "TileComum.h"


TileComum::TileComum(void)
{
	//faz alguma coisa
}


TileComum::~TileComum(void)
{
	//destroi alguma coisa
}


void TileComum::init(void)
{	
	//tile->node->setMaterialTexture(0, driver->getTexture("obj/texturas/grama.jpg"));
}

void TileComum::update(void)
{
	// Movimentação
	float dT = IrrEngine::getInstance()->getDeltaTime();

	if(tile->isHighlighted)
	{		
		tile->node->setMaterialFlag(irr::video::EMF_WIREFRAME,true);
	}
	else
	{
		tile->node->setMaterialFlag(irr::video::EMF_WIREFRAME,false);
	}
}