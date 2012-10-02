#include "IrrTile.h"

using namespace IrrBoardGameEngine;

IrrTile::IrrTile(void)
{
	token = new IrrToken();
}


IrrTile::~IrrTile(void)
{
	if(token != NULL) delete token;
}
