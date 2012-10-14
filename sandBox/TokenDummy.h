#pragma once
#include "IrrEngine.h"

using namespace IrrBoardGameEngine;

class TokenDummy :
	public IrrTokenBehavior
{
public:
	void init();
	void update();
};

