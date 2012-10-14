#include "PrimeTileManager.h"

PrimeTileManager::PrimeTileManager() {};
PrimeTileManager::~PrimeTileManager() {};

void PrimeTileManager::updateTiles(IrrBoard* board)
{
	//Scan the whole board
	for (int i=0; i < board->tile_i; i++)
	{
		for (int j=0; j < board->tile_j; j++)
		{
			//Update every tile
			//...
		}
	}
}