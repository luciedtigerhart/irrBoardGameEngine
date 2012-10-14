#pragma once
#include "irrlicht.h"
#include "irrKlang.h"

#include <map>
#include <string>

#include "IrrInput.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace irrklang;

namespace IrrBoardGameEngine {
class IrrBehavior
{
	public:
		public:
		IVideoDriver *driver;
		ISceneManager *smgr;
		ISoundEngine *soundEngine;
		IrrInput * input;

		virtual void init() = 0;
		virtual void update() = 0;
	};
}
