#include "IrrBoard.h"

using namespace IrrBoardGameEngine;

IrrBoard::IrrBoard(void)
{
	objs = new vector<std::string>();
	tokens = new vector<std::string>();
	tokens->push_back("null");
}


IrrBoard::~IrrBoard(void)
{
	delete objs;
	delete tokens;

	for(int y = 0; y < tile_y; y++)
	{
		for(int x = 0; x < tile_x; x++)
		{
			delete board[x][y];
		}
	}
}
