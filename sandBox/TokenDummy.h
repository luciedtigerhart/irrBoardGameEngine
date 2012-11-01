#pragma once
#include "IrrEngine.h"

using namespace IrrBoardGameEngine;

class TokenDummy :
	public IrrTokenBehavior
{
private:
	bool flag_cor, flag_estado;

public:
	void init();
	void update();
	void reset();
	
	void setInt(char const * key, int value);
	int getInt(char const * key);

	void setBool(char const * key, bool value);
	bool getBool(char const * key);

	void setFloat(char const * key, float value);
	float getFloat(char const * key);

	void setVector(char const * key, Vector value);
	Vector getVector(char const * key);
};

