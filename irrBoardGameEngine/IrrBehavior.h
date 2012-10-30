#pragma once
#include "irrlicht.h"
#include "irrKlang.h"

#include <map>
#include <string>

#include "IrrInput.h"
#include "Vector.h"

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

		virtual void setInt(char const * key, int value) = 0;
		virtual int getInt(char const * key) = 0;

		virtual void setFloat(char const * key, float value) = 0;
		virtual float getFloat(char const * key) = 0;

		virtual void setBool(char const * key, bool value) = 0;
		virtual bool getBool(char const * key) = 0;

		virtual void setVector(char const * key, Vector value) = 0;
		virtual Vector getVector(char const * key) = 0;
	};
}
