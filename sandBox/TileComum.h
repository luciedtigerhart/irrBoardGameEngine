#pragma once
#include "IrrEngine.h"

using namespace IrrBoardGameEngine;

class TileComum :
	public IrrTileBehavior
{
public:
	TileComum(void);
	~TileComum(void);

	void init();
	void update();
};

