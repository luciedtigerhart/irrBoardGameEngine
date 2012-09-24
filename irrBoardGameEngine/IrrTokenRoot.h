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

#include "IrrGameObject.h"

using namespace irr;
using namespace scene;
using namespace core;
using namespace std;

namespace IrrBoardGameEngine {

	class IrrTokenRoot :
		public IrrGameObject
	{
	public:
		IrrTokenRoot(void);
		~IrrTokenRoot(void);
	};

}