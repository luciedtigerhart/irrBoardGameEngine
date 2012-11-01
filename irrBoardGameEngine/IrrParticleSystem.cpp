#include "IrrParticleSystem.h"

using namespace IrrBoardGameEngine;

IrrParticleSystem::IrrParticleSystem(ISceneManager * s)
{
	smgr = s;
	ps = smgr->addParticleSystemSceneNode(false);
}


IrrParticleSystem::~IrrParticleSystem(void)
{
}

IParticleEmitter * IrrParticleSystem::createEmitter(s32 id)
{
	IParticleEmitter * em = ps->createBoxEmitter();
	
	emitters.insert(pair<s32, IParticleEmitter*>(id,em));

	// this grabs the emitter
	ps->setEmitter(em);

	// so we can drop it here without deleting it
    em->drop();

    scene::IParticleAffector* paf = ps->createFadeOutParticleAffector();

	// same goes for the affector
    ps->addAffector(paf);
    paf->drop();

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
		(*it).second->drop();
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
	IBillboardSceneNode* nm = smgr->addBillboardSceneNode();

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