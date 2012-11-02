#include "IrrParticleSystem.h"

using namespace IrrBoardGameEngine;

IrrParticleSystem::IrrParticleSystem(ISceneManager * s, IVideoDriver * d)
{
	smgr = s;
	driver = d;
	node = smgr->addParticleSystemSceneNode(false);
}


IrrParticleSystem::~IrrParticleSystem(void)
{
}

IParticleEmitter * IrrParticleSystem::createEmitter(s32 id,const core::aabbox3df& box,
		const core::vector3df& direction,
		u32 minParticlesPerSecond,
		u32 maxParticlesPerSecond,
		const video::SColor& minStartColor,
		const video::SColor& maxStartColor,
		u32 lifeTimeMin, u32 lifeTimeMax,
		s32 maxAngleDegrees,
		const core::dimension2df& minStartSize,
		const core::dimension2df& maxStartSize)
{
	IParticleEmitter * em = node->createBoxEmitter(box,direction,
		minParticlesPerSecond,maxParticlesPerSecond,minStartColor,
		maxStartColor,lifeTimeMin,lifeTimeMax,maxAngleDegrees,
		minStartSize,maxStartSize);
	
	emitters.insert(pair<s32, IParticleEmitter*>(id,em));

	// this grabs the emitter
	node->setEmitter(em);

	// so we can drop it here without deleting it
    //em->drop();

    scene::IParticleAffector* paf = node->createFadeOutParticleAffector();

	// same goes for the affector
    node->addAffector(paf);
    //paf->drop();

	return em;
}

void IrrParticleSystem::removeEmitter(s32 id)
{
	//
	// deveria remover
	// mas tem que ver como faz
	//
    std::map<s32, IParticleEmitter*>::iterator it = emitters.find(id);
    if(it != emitters.end())
		(*it).second->grab();
}

IParticleEmitter * IrrParticleSystem::getEmitter(s32 id)
{
	std::map<s32, IParticleEmitter*>::iterator it = emitters.find(id);
    if(it != emitters.end())
	{
		return (*it).second;
	}
	else
	{
		return NULL;
	}
}

IBillboardSceneNode* IrrParticleSystem::addBillboard(s32 id)
{
	addBillboard(id, node);
}

IBillboardSceneNode* IrrParticleSystem::addBillboard(s32 id, ISceneNode * node)
{
	IBillboardSceneNode* nm = smgr->addBillboardSceneNode(node);

	billboards.insert(pair<s32, IBillboardSceneNode*>(id,nm));

	return nm;
}

IBillboardSceneNode * IrrParticleSystem::getBillboard(s32 id)
{
	std::map<s32, IBillboardSceneNode*>::iterator it = billboards.find(id);
    if(it != billboards.end())
	{
		return (*it).second;
	}
	else
	{
		return NULL;
	}
}

void IrrParticleSystem::setParent(ISceneNode * node)
{
	node->setParent(node);
}

void IrrParticleSystem::setMaterialFlag(video::E_MATERIAL_FLAG flag, bool newvalue)
{
	node->setMaterialFlag(flag, newvalue);
}

void IrrParticleSystem::setMaterialTexture(u32 textureLayer, const char * src)
{
	node->setMaterialTexture(textureLayer,  driver->getTexture(src));
}

void IrrParticleSystem::setMaterialType(video::E_MATERIAL_TYPE newType)
{
	node->setMaterialType(newType);
}

void IrrParticleSystem::setPosition(Vector*p)
{
	node->setPosition(vector3df(p->x,p->y,p->z));
}
void IrrParticleSystem::setScale(Vector*p)
{
	node->setScale(vector3df(p->x,p->y,p->z));
}