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
		std::map<s32, IParticleAffector*> affectors;
		std::map<s32, IBillboardSceneNode*> billboards;

	public:
		IParticleSystemSceneNode* node;

		IrrParticleSystem(ISceneManager * s, IVideoDriver * d);
		~IrrParticleSystem(void);

		void setPosition(Vector*);
		void setScale(Vector*);
		void setParent(ISceneNode * node);
		//ativa a particle system
		void setActive(bool flag);
		void setMaterialFlag(video::E_MATERIAL_FLAG flag, bool newvalue);
		void setMaterialTexture(u32 textureLayer, const char * src);
		void setMaterialType(video::E_MATERIAL_TYPE newType);

		//
		// Affector
		//
		IParticleAffector* addFadeOutAffector(s32 id, const video::SColor& targetColor = video::SColor(0,0,0,0), u32 timeNeededToFadeOut = 1000);
		IParticleAffector* addGravityAffector(s32 id, const core::vector3df& gravity = core::vector3df(0.0f,-0.03f,0.0f), u32 timeForceLost = 1000);
		IParticleAffector* addRotationAffector(s32 id, const core::vector3df& speed = core::vector3df(5.0f,5.0f,5.0f), const core::vector3df& pivotPoint = core::vector3df(0.0f,0.0f,0.0f));
		IParticleAffector* addAttractionAffector(s32 id, const core::vector3df& point, f32 speed = 1.0f, bool attract = true, bool affectX = true, bool affectY = true, bool affectZ = true);

		IParticleAffector* setAffector(s32 id);
		IParticleAffector* getAffector(s32 id);
		void removeAffector(s32 id);
		void removeAllAffectors();


		//
		// Billboard
		//
		IBillboardSceneNode* addBillboard(s32 id);
		IBillboardSceneNode* addBillboard(s32 id, ISceneNode * node);
		IBillboardSceneNode * getBillboard(s32 id);


		//
		// EMITTER
		//
		IParticleEmitter * createBoxEmitter(s32 id,const core::aabbox3df& box = core::aabbox3df(-10,28,-10,10,30,10),
											const core::vector3df& direction = core::vector3df(0.0f,0.03f,0.0f),
											u32 minParticlesPerSecond = 5,
											u32 maxParticlesPerSecond = 10,
											const video::SColor& minStartColor = video::SColor(255,0,0,0),
											const video::SColor& maxStartColor = video::SColor(255,255,255,255),
											u32 lifeTimeMin=10000, u32 lifeTimeMax=10000,
											s32 maxAngleDegrees=0,
											const core::dimension2df& minStartSize = core::dimension2df(5.0f,5.0f),
											const core::dimension2df& maxStartSize = core::dimension2df(5.0f,5.0f));

		IParticleEmitter * createSphereEmitter(s32 id,const core::vector3df& center, f32 radius,
											const core::vector3df& direction = core::vector3df(0.0f,0.03f,0.0f),
											u32 minParticlesPerSecond = 5,
											u32 maxParticlesPerSecond = 10,
											const video::SColor& minStartColor = video::SColor(255,0,0,0),
											const video::SColor& maxStartColor = video::SColor(255,255,255,255),
											u32 lifeTimeMin=10000, u32 lifeTimeMax=10000,
											s32 maxAngleDegrees=0,
											const core::dimension2df& minStartSize = core::dimension2df(5.0f,5.0f),
											const core::dimension2df& maxStartSize = core::dimension2df(5.0f,5.0f));

		IParticleEmitter * createCylinderEmitter(s32 id,const core::vector3df& center, f32 radius,
											const core::vector3df& normal, f32 length,
											bool outlineOnly = false,
											const core::vector3df& direction = core::vector3df(0.0f,0.03f,0.0f),
											u32 minParticlesPerSecond = 5, u32 maxParticlesPerSecond = 10,
											const video::SColor& minStartColor = video::SColor(255,0,0,0),
											const video::SColor& maxStartColor = video::SColor(255,255,255,255),
											u32 lifeTimeMin = 10000, u32 lifeTimeMax = 10000,
											s32 maxAngleDegrees = 0,
											const core::dimension2df& minStartSize = core::dimension2df(5.0f,5.0f),
											const core::dimension2df& maxStartSize = core::dimension2df(5.0f,5.0f));

		IParticleEmitter * createRingEmitter(s32 id,const core::vector3df& center, f32 radius, f32 ringThickness,
											const core::vector3df& direction = core::vector3df(0.0f,0.03f,0.0f),
											u32 minParticlesPerSecond = 5,
											u32 maxParticlesPerSecond = 10,
											const video::SColor& minStartColor = video::SColor(255,0,0,0),
											const video::SColor& maxStartColor = video::SColor(255,255,255,255),
											u32 lifeTimeMin=10000, u32 lifeTimeMax=10000,
											s32 maxAngleDegrees=0,
											const core::dimension2df& minStartSize = core::dimension2df(5.0f,5.0f),
											const core::dimension2df& maxStartSize = core::dimension2df(5.0f,5.0f));

		IParticleEmitter * createMeshEmitter(s32 id,const char * src, bool useNormalDirection = true,
											const core::vector3df& direction = core::vector3df(0.0f,0.03f,0.0f),
											f32 normalDirectionModifier = 100.0f, s32 mbNumber = -1,
											bool everyMeshVertex = false,
											u32 minParticlesPerSecond = 5, u32 maxParticlesPerSecond = 10,
											const video::SColor& minStartColor = video::SColor(255,0,0,0),
											const video::SColor& maxStartColor = video::SColor(255,255,255,255),
											u32 lifeTimeMin = 10000, u32 lifeTimeMax = 10000,
											s32 maxAngleDegrees = 0,
											const core::dimension2df& minStartSize = core::dimension2df(5.0f,5.0f),
											const core::dimension2df& maxStartSize = core::dimension2df(5.0f,5.0f));

		IParticleEmitter * getEmitter(s32 id);
		void setEmitter(s32 id);
		void removeEmitter(s32 id);
		void removeAllEmitter();
	};
}