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

		//cria um token e adiciona um comportamento para o mesmo
		bool createToken(int j, int i, IrrTokenBehavior * behavior);
		void addTokenBehavior(IrrToken *token, IrrTokenBehavior * behavior);

		//devolve um token determinado de uma regiao do tabuleiro
		IrrToken *getToken(int j, int i);

		//adiciona um token já existente para uma regiao do tabuleiro
		bool addToken(int j, int i, IrrToken * token);

		//move um token de lugar
		bool moveToken(int oj, int oi, int tj, int ti);

		//apaga um token
		bool deleteToken(int j, int i);

		//muda o estado 'highlight' de um token
		void changeHighlightToken(int type, int player);

		//muda o estado 'highlight' de um tile
		void changeHighlightTile(int type, int inf);

		//configura um nodo 'highlight'
		void setHighlight(ISceneNode *node);

		//função de atualização dos dados
		void update();
	};

}

