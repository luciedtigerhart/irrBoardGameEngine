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
	removeAllEmitter();
	removeAllAffectors();
	if(node != NULL) delete node;
}

IParticleEmitter * IrrParticleSystem::createBoxEmitter(s32 id,const core::aabbox3df& box,
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

	node->setEmitter(em);

	// so we can drop it here without deleting it
    em->drop();

	return em;
}

IParticleEmitter * IrrParticleSystem::createSphereEmitter(s32 id,const core::vector3df& center, f32 radius,
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
	IParticleEmitter * em = node->createSphereEmitter(center,radius,
		direction,minParticlesPerSecond,maxParticlesPerSecond,
		minStartColor,maxStartColor,lifeTimeMin,lifeTimeMax,
		maxAngleDegrees,minStartSize,maxStartSize);
	
	emitters.insert(pair<s32, IParticleEmitter*>(id,em));

	node->setEmitter(em);

	// so we can drop it here without deleting it
    em->drop();

	return em;
}

IParticleEmitter * IrrParticleSystem::createCylinderEmitter(s32 id,const core::vector3df& center, f32 radius,
		const core::vector3df& normal, f32 length,
		bool outlineOnly,
		const core::vector3df& direction,
		u32 minParticlesPerSecond, u32 maxParticlesPerSecond,
		const video::SColor& minStartColor,
		const video::SColor& maxStartColor,
		u32 lifeTimeMin, u32 lifeTimeMax,
		s32 maxAngleDegrees,
		const core::dimension2df& minStartSize,
		const core::dimension2df& maxStartSize)
{
	IParticleEmitter * em = node->createCylinderEmitter(center,radius,
		normal,length,outlineOnly,
		direction,minParticlesPerSecond,maxParticlesPerSecond,minStartColor,
		maxStartColor,lifeTimeMin,lifeTimeMax,maxAngleDegrees,minStartSize,maxStartSize);
	
	emitters.insert(pair<s32, IParticleEmitter*>(id,em));

	node->setEmitter(em);

	// so we can drop it here without deleting it
    em->drop();

	return em;
}

IParticleEmitter * IrrParticleSystem::createRingEmitter(s32 id,const core::vector3df& center, f32 radius, f32 ringThickness,
		const core::vector3df& direction,
		u32 minParticlesPerSecond ,
		u32 maxParticlesPerSecond,
		const video::SColor& minStartColor,
		const video::SColor& maxStartColor,
		u32 lifeTimeMin, u32 lifeTimeMax,
		s32 maxAngleDegrees,
		const core::dimension2df& minStartSize,
		const core::dimension2df& maxStartSize)
{
	IParticleEmitter * em = node->createRingEmitter(center,radius,
		ringThickness,direction,minParticlesPerSecond,
		maxParticlesPerSecond,minStartColor,maxStartColor,lifeTimeMin,
		lifeTimeMax,maxAngleDegrees,minStartSize,maxStartSize);
	
	emitters.insert(pair<s32, IParticleEmitter*>(id,em));

	node->setEmitter(em);

	// so we can drop it here without deleting it
    em->drop();

	return em;
}

IParticleEmitter * IrrParticleSystem::createMeshEmitter(s32 id, const char * src, bool useNormalDirection,
		const core::vector3df& direction,
		f32 normalDirectionModifier, s32 mbNumber,
		bool everyMeshVertex,
		u32 minParticlesPerSecond, u32 maxParticlesPerSecond,
		const video::SColor& minStartColor,
		const video::SColor& maxStartColor,
		u32 lifeTimeMin, u32 lifeTimeMax,
		s32 maxAngleDegrees,
		const core::dimension2df& minStartSize,
		const core::dimension2df& maxStartSize)
{
	IParticleEmitter * em = node->createMeshEmitter(smgr->getMesh(src),useNormalDirection,direction,
		normalDirectionModifier,mbNumber,everyMeshVertex,
		minParticlesPerSecond,maxParticlesPerSecond,minStartColor,maxStartColor,
		lifeTimeMin,lifeTimeMax,maxAngleDegrees,minStartSize,maxStartSize);
	
	emitters.insert(pair<s32, IParticleEmitter*>(id,em));

	node->setEmitter(em);

	// so we can drop it here without deleting it
    em->drop();

	return em;
}

void IrrParticleSystem::setEmitter(s32 id)
{
	IParticleEmitter* em = getEmitter(id);
	if(em != NULL)
	{
		node->setEmitter(em);
		em->drop();
	}
}

void IrrParticleSystem::removeEmitter(s32 id)
{
	//
	// deveria remover
	// mas tem que ver como faz
	//
    std::map<s32, IParticleEmitter*>::iterator it = emitters.find(id);
    if(it != emitters.end())
	{
		(*it).second->drop();
		emitters.erase(it);
	}
}

void IrrParticleSystem::removeAllEmitter()
{
	std::map<s32, IParticleEmitter*>::iterator it = emitters.begin();
    while(it != emitters.end())
	{
		it->second->drop();
		it++;
	}
	emitters.empty();
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

IParticleAffector* IrrParticleSystem::addFadeOutAffector(s32 id, const video::SColor& targetColor, u32 timeNeededToFadeOut)
{
	scene::IParticleAffector* paf = node->createFadeOutParticleAffector(targetColor,timeNeededToFadeOut);

	affectors.insert(pair<s32, IParticleAffector*>(id,paf));

	node->addAffector(paf);
	paf->drop();

	return paf;
}

IParticleAffector* IrrParticleSystem::addGravityAffector(s32 id,const core::vector3df& gravity, u32 timeForceLost)
{
	scene::IParticleAffector* paf = node->createGravityAffector(gravity,timeForceLost);

	affectors.insert(pair<s32, IParticleAffector*>(id,paf));

	node->addAffector(paf);
	paf->drop();

	return paf;
}

IParticleAffector* IrrParticleSystem::addRotationAffector(s32 id, const core::vector3df& speed, const core::vector3df& pivotPoint)
{
	scene::IParticleAffector* paf = node->createRotationAffector(speed,pivotPoint);

	affectors.insert(pair<s32, IParticleAffector*>(id,paf));

	node->addAffector(paf);
	paf->drop();

	return paf;
}

IParticleAffector* IrrParticleSystem::addAttractionAffector(s32 id,  const core::vector3df& point, f32 speed, bool attract, bool affectX, bool affectY, bool affectZ)
{
	scene::IParticleAffector* paf = node->createAttractionAffector(point,speed,attract,affectX,affectY,affectZ);

	affectors.insert(pair<s32, IParticleAffector*>(id,paf));

	node->addAffector(paf);
	paf->drop();

	return paf;
}

IParticleAffector* IrrParticleSystem::setAffector(s32 id)
{
	IParticleAffector* paf = getAffector(id);
	if(paf != NULL)
	{
		node->addAffector(paf);
		paf->drop();
	}
}

IParticleAffector* IrrParticleSystem::getAffector(s32 id)
{
	std::map<s32, IParticleAffector*>::iterator it = affectors.find(id);
    if(it != affectors.end())
	{
		return (*it).second;
	}
	else
	{
		return NULL;
	}
}

void IrrParticleSystem::removeAffector(s32 id)
{
	//
	// deveria remover
	// mas tem que ver como faz
	//
    std::map<s32, IParticleAffector*>::iterator it = affectors.find(id);
    if(it != affectors.end())
	{
		(*it).second->drop();
		affectors.erase(it);
	}
}

void IrrParticleSystem::removeAllAffectors()
{
	std::map<s32, IParticleAffector*>::iterator it = affectors.begin();
    while(it != affectors.end())
	{
		it->second->drop();
		it++;
	}
	affectors.empty();
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

void IrrParticleSystem::setActive(bool flag)
{
	node->setVisible(flag);
}