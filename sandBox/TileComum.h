#pragma once
#include "IrrEngine.h"

using namespace IrrBoardGameEngine;

class TileComum :
	public IrrTileBehavior
{
private:
	int pontos, energia;
	bool flag_cor, flag_estado;

public:
	TileComum(void);
	~TileComum(void);

	void init();
	void update();

	void setInt(char const * key, int value);
	int getInt(char const * key);

	void setBool(char const * key, bool value);
	bool getBool(char const * key);
};

