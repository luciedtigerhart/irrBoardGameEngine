#include "IrrTile.h"

using namespace IrrBoardGameEngine;

IrrTile::IrrTile(void)
{
	token = NULL;
	start = 0;
}


IrrTile::~IrrTile(void)
{
	if(token != NULL)
	{
		delete token;
		node->removeAll();
	}
}


void IrrTile::update()
{
	__super::update();
	if(token != NULL) token->update();
}