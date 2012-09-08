#pragma once

#include <string.h>
#include "irrlicht.h"
#include "Vector.h"

using namespace irr;
using namespace scene;
using namespace core;

namespace IrrBoardGameEngine {
	class IrrMesh
	{
	public:
		IrrMesh(IMeshSceneNode *);

		void setPosition(Vector&);
		void setScale(Vector&);
		void setRotation(Vector&);

		IMeshSceneNode *node;

		~IrrMesh(void);
	};
}