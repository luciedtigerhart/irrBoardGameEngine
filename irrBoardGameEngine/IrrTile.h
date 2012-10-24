#pragma once
#include <map>

#include "irrlicht.h"
#include <string>
#include <vector>

#include "Vector.h"
#include "IrrCamera.h"
#include "IrrMesh.h"
#include "IrrGameObject.h"
#include "IrrToken.h"

using namespace irr;
using namespace scene;
using namespace video;
using namespace core;
using namespace std;

namespace IrrBoardGameEngine {
	class IrrBoard;

	class IrrTile :
		public IrrGameObject
	{
	public:
		IrrTile(void);
		~IrrTile(void);

		//posicao i na matriz
		int posi;

		//posicao j na matriz
		int posj;

		//index da imagem
		int idx;

		//index da informação/evento/comportamento
		int inf;

		//define o grupo que inicia
		int start;

		//quando o mouse estiver sobre
		bool isMouseHover;

		//Whether this tile must be highlighted
		bool isHighlighted;

		//Type of highlight (movement, pushing, attack, etc.)
		int highlight;

		//Peça
		IrrToken *token;

		//board
		//ISceneNode *parentNode;
		IrrBoard *parentNode;

		void update();
	};

}