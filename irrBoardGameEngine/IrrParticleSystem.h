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
		IVideoDriver *driver;

	protected:

		std::map<s32, IParticleEmitter*> emitters;
		std::map<s32, IBillboardSceneNode*> billboards;

	public:
		IParticleSystemSceneNode* node;

		IrrParticleSystem(ISceneManager * s, IVideoDriver * d);
		~IrrParticleSystem(void);

		void setPosition(Vector*);
		void setScale(Vector*);
		void setParent(ISceneNode * node);
		void setMaterialFlag(video::E_MATERIAL_FLAG flag, bool newvalue);
		void setMaterialTexture(u32 textureLayer, const char * src);
		void setMaterialType(video::E_MATERIAL_TYPE newType);

		IBillboardSceneNode* addBillboard(s32 id);
		IBillboardSceneNode* addBillboard(s32 id, ISceneNode * node);
		IBillboardSceneNode * getBillboard(s32 id);

		IParticleEmitter * createEmitter(s32 id,const core::aabbox3df& box = core::aabbox3df(-10,28,-10,10,30,10),
		const core::vector3df& direction = core::vector3df(0.0f,0.03f,0.0f),
		u32 minParticlesPerSecond = 5,
		u32 maxParticlesPerSecond = 10,
		const video::SColor& minStartColor = video::SColor(255,0,0,0),
		const video::SColor& maxStartColor = video::SColor(255,255,255,255),
		u32 lifeTimeMin=2000, u32 lifeTimeMax=4000,
		s32 maxAngleDegrees=0,
		const core::dimension2df& minStartSize = core::dimension2df(5.0f,5.0f),
		const core::dimension2df& maxStartSize = core::dimension2df(5.0f,5.0f));
		IParticleEmitter * getEmitter(s32 id);

		void removeEmitter(s32 id);
	};
}

