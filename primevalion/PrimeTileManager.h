#ifndef _PRIMETILEMANAGER_H
#define _PRIMETILEMANAGER_H

#include <iostream>
#include "PrimePlayState.h"

using namespace IrrBoardGameEngine;

class PrimeTileManager
{
private:
public:
	PrimeTileManager();
	~PrimeTileManager();

	void updateTiles(IrrBoard* board);
};

#endif