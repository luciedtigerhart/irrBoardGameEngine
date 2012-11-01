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
		ISceneManager *smgr;

	protected:
		IParticleSystemSceneNode* ps;

		std::map<s32, IParticleEmitter*> emitters;
		std::map<s32, IBillboardSceneNode*> billboards;

	public:
		IrrParticleSystem(ISceneManager * s);
		~IrrParticleSystem(void);

		IBillboardSceneNode* addBillboard(s32 id);
		IBillboardSceneNode * getBillboard(s32 id);

		IParticleEmitter * createEmitter(s32 id);
		IParticleEmitter * getEmitter(s32 id);
		void removeEmitter(s32 id);
	};
}

