#include "PrimeTokenManager.h"

PrimeTokenManager::PrimeTokenManager() {};
PrimeTokenManager::~PrimeTokenManager() {};

void PrimeTokenManager::updateTokens(IrrBoard* board)
{
	//Scan the whole board
	for (int i=0; i < board->tile_i; i++)
	{
		for (int j=0; j < board->tile_j; j++)
		{
			//Update every tile's token
			if (board->board[i][j]->token != NULL)
			{
				//...
			}
		}
	}
}