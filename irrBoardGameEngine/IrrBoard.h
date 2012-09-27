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

		vector<vector<IrrTile*>> board;
	};

}

