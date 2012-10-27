#pragma once
#include "IrrEngine.h"

using namespace IrrBoardGameEngine;

class TokenNoob :
	public IrrTokenBehavior
{
private:
	bool flag_cor, flag_estado;

public:
	void init();
	void update();
	
	void setInt(char const * key, int value);
	int getInt(char const * key);

	void setBool(char const * key, bool value);
	bool getBool(char const * key);
};

