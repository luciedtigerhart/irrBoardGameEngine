#pragma once
#include <map>

#include "irrlicht.h"
#include <string>
#include <vector>

#include "Vector.h"
#include "IrrCamera.h"
#include "IrrMesh.h"
#include "IrrGameObject.h"

using namespace irr;
using namespace scene;
using namespace core;
using namespace std;

namespace IrrBoardGameEngine {
	class IrrTile;

	class IrrToken :
		public IrrGameObject
	{
	public:
		IrrToken(void);
		~IrrToken(void);

		//index do token
		int idx;

		//jogador
		int player;

		//Whether this tile must be highlighted
		bool isHighlighted;

		//Type of highlight (movement, pushing, attack, etc.)
		int highlight;

		//Tile
		//ISceneNode *parentNode;
		IrrTile *parentNode;
	};

}

