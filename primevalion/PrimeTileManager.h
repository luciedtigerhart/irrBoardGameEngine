#ifndef _PRIMETILEMANAGER_H
#define _PRIMETILEMANAGER_H

#include <iostream>
#include "PrimePlayState.h"

using namespace std;

class PrimeTileManager
{
private:
public:
	PrimeTileManager();
	~PrimeTileManager();

	void updateTiles(IrrBoard* board);
};

#endif