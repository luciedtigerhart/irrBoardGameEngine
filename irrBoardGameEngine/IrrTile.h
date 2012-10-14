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

		//Peça
		IrrToken * token;
	};

}