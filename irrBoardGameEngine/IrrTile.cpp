#include "IrrTile.h"

using namespace IrrBoardGameEngine;

IrrTile::IrrTile(void)
{
	token = NULL;
	start = 0;
}


IrrTile::~IrrTile(void)
{
	if(token != NULL) delete token;
}
