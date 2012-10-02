#pragma once
#include "irrlicht.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>

#include "Vector.h"
#include "IrrCamera.h"
#include "IrrMesh.h"

//#include "IrrBehavior.h"
//#include "IrrAnimation.h"
//#include "IrrAudio.h"

#include "IrrGameObject.h"
#include "IrrTile.h"

using namespace irr;
using namespace scene;
using namespace core;
using namespace std;

namespace IrrBoardGameEngine {

	class IrrBoard :
		public IrrGameObject
	{
	public:
		IrrBoard(void);
		~IrrBoard(void);

		int width; //largura em pixel
		int height; //comprimento em pixel
		int tile_x; //numeros de tiles em x
		int tile_y; //numeros de tiles em y
		int tile_width; //largura em pixel do tile
		int tile_height; //comprimento em pixel do tile
		vector<vector<IrrTile*>> board; //lista de tiles
		vector<std::string> * objs; //lista de objs
		vector<std::string> * tokens; //lista de objs
	};

}

