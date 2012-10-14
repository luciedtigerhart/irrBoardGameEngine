#pragma once
#include "irrlicht.h"
#include "irrKlang.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>

#include "IrrInput.h"
#include "IrrBehavior.h"
#include "IrrGameObject.h"
#include "Vector.h"
#include "IrrCamera.h"
#include "IrrMesh.h"
#include "IrrTile.h"
#include "IrrTokenBehavior.h"
#include "IrrTileBehavior.h"

using namespace irr;
using namespace scene;
using namespace core;
using namespace std;
using namespace irrklang;

namespace IrrBoardGameEngine {

	class IrrBoard :
		public IrrGameObject
	{
	public:
		IrrBoard(void);
		~IrrBoard(void);

		int width; //largura em pixel
		int length; //comprimento em pixel

		int tile_i; //numeros de tiles em x
		int tile_j; //numeros de tiles em z

		int tile_width; //largura em coordenadas x do tile
		int tile_height; //altura em coordenadas y do tile
		int tile_length; //comprimento em coordenadas z do tile

		vector<vector<IrrTile*>> board; //lista de tiles
		vector<std::string> * objs; //lista de objs

		void addTileBehavior(int i, int j, IrrTileBehavior * behavior);

		void startTokens(int idx, IrrTokenBehavior * behavior);
		bool createToken(int i, int j, IrrTokenBehavior * behavior);

		IrrToken *getToken(int i, int j);
		bool addToken(int i, int j, IrrToken * token);
		bool moveToken(int oi, int oj, int ti, int tj);
		bool deleteToken(int i, int j);
	};

}

