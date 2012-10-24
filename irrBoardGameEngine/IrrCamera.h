#pragma once
#include "irrlicht.h"
#include "IrrInput.h"
#include <string.h>
#include "Vector.h"

using namespace irr;
using namespace scene;
using namespace core;

namespace IrrBoardGameEngine {
	class IrrCamera
	{
	private:
		IrrInput * ip;
	public:
		IrrCamera(ICameraSceneNode *);
		void lookAt(Vector&);

		ICameraSceneNode *node;
		~IrrCamera(void);

		void update();
	};
}