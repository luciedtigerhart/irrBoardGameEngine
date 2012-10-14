#pragma once
#include "IrrEngine.h"

using namespace IrrBoardGameEngine;

class TokenNoob :
	public IrrTokenBehavior
{
public:
	void init();
	void update();
};

