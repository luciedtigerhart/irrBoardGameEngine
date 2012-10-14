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

		//Tile
		ISceneNode *parentNode;
	};

}

