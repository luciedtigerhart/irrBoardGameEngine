#pragma once

#include <string.h>
#include "irrlicht.h"
#include "Vector.h"

using namespace irr;
using namespace scene;
using namespace core;

namespace IrrBoardGameEngine {
	class IrrMeshAnimated
	{
	public:
		IrrMeshAnimated(IAnimatedMeshSceneNode *);

		void setPosition(Vector&);
		void setScale(Vector&);
		void setRotation(Vector&);

		IAnimatedMeshSceneNode *node;

		~IrrMeshAnimated(void);
	};
}
