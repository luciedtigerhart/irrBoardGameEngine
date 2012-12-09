#pragma once
#include <map>

#include "irrlicht.h"
#include <string>
#include <vector>

#include "Vector.h"
#include "IrrCamera.h"
#include "IrrMesh.h"
#include "IrrMeshAnimated.h"
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

		//quando o mouse estiver sobre
		bool isMouseHover;

		//quando o hightligh está ativo
		bool isHighlighted;

		//tipo do highlight
		int highlight;

		//Tile		
		IrrTile *parentNode;
	};

}

