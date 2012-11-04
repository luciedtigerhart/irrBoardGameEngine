#include "IrrToken.h"

using namespace IrrBoardGameEngine;

IrrToken::IrrToken(void)
{
	idx = 0;
	player = 0;
}

IrrToken::~IrrToken(void)
{
	node->removeAll();
}
