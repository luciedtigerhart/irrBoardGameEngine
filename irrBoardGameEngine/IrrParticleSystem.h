#pragma once
#include "irrlicht.h"
#include "IrrInput.h"

#include <map>
#include <string>
#include "Vector.h"

using namespace irr;
using namespace scene;
using namespace core;
using namespace scene;

namespace IrrBoardGameEngine {
	class IrrParticleSystem
	{
	private:
		IParticleSystemSceneNode* ps;

		std::map<s32, IParticleEmitter*> particles;
	public:
		IrrParticleSystem(void);
		~IrrParticleSystem(void);
	};
}

