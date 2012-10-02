#pragma once
#include <map>

#include "irrlicht.h"
#include <string>
#include <vector>

#include "Vector.h"
#include "IrrCamera.h"
#include "IrrMesh.h"

//#include "IrrBehavior.h"
//#include "IrrAnimation.h"
//#include "IrrAudio.h"

#include "IrrToken.h"
#include "IrrGameObject.h"

using namespace irr;
using namespace scene;
using namespace core;
using namespace std;

namespace IrrBoardGameEngine {

	class IrrTile :
		public IrrGameObject
	{
	public:
		IrrTile(void);
		~IrrTile(void);

		int posx;//posicao x
		int posy;//posicao y

		int idx;//index da imagem
		int inf;//index da informação/evento/comportamento

		IrrToken * token;
	};

}