#pragma once
#include "irrlicht.h"
#include "irrKlang.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <list>

#include "IrrInput.h"
#include "IrrBehavior.h"
#include "IrrGameObject.h"
#include "Vector.h"
#include "IrrCamera.h"
#include "IrrMesh.h"
#include "IrrMeshAnimated.h"
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

		//largura em pixel
		int width;

		//comprimento em pixel
		int length;

		//numeros de tiles em x
		int tile_i;

		//numeros de tiles em z
		int tile_j;

		//largura em coordenadas x do tile
		int tile_width;

		//altura em coordenadas y do tile
		int tile_height;

		//comprimento em coordenadas z do tile
		int tile_length;

		//lista de tiles
		vector<vector<IrrTile*>> board;

		//lista de objs
		vector<std::string> * objs;

		//adiciona um comportamento num tile especifico
		void addTileBehavior(IrrTile * tile, IrrTileBehavior * behavior);
		void addTileBehavior(int j, int i, IrrTileBehavior * behavior);

		//devolve o comportamento em vários tiles, cujo o inf do arquivo
		std::list<IrrTile*> * getAllTiles();
		std::list<IrrTile*> * getTiles(int inf);
		std::list<IrrToken*> * createTokens(int start);

		bool createToken(int j, int i, IrrTokenBehavior * behavior);
		void addTokenBehavior(IrrToken *token, IrrTokenBehavior * behavior);

		IrrToken *getToken(int j, int i);
		bool addToken(int j, int i, IrrToken * token);
		bool moveToken(int oj, int oi, int tj, int ti);
		bool deleteToken(int j, int i);

		void changeHighlightToken(int type, int player);
		void changeHighlightTile(int type, int inf);

		void setHighlight(ISceneNode *node);

		void update();
	};

}

