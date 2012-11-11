#include "IrrAudio.h"
#include <iostream>

using namespace IrrBoardGameEngine;

// id for our scene node, 'ikng', short for 'irrklang'.
// If this line doesn't work, you are probably using irrlicht 1.3 or earlier.
// Then remove the MAKE_IRR_ID thing and replace it with a random number.
const int IRRKLANG_SCENE_NODE_ID = MAKE_IRR_ID('i','k','n','g');

// type name for our scene node
const char* IrrAudioTypeName = "IrrAudio";

IrrAudio::IrrAudio(irrklang::ISoundEngine* soundEngine, scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id) : scene::ISceneNode(parent, mgr, id), SoundEngine(soundEngine)
{
	setAutomaticCulling(scene::EAC_OFF);

	MinDistance = 20.0f; // a usual good value for irrlicht engine applications
	MaxDistance = -1.0f;
	PlayMode = EPM_RANDOM;
	TimeMsDelayFinished = 0;
	DeleteWhenFinished = false;
	MaxTimeMsInterval = 5000;
	MinTimeMsInterval = 1000;
	Sound = 0;
	PlayedCount = 0;

	fade_volume_atual = 1.0f;
	fade_in = false;
	fade_out = false;
	fade_velocidade = 0.1f;
	fade_volume = 0.0f;

	if (SoundEngine) SoundEngine->grab();
}


IrrAudio::~IrrAudio()
{
	stop();

	if (SoundEngine) SoundEngine->drop();
}


void IrrAudio::OnRegisterSceneNode()
{
	if (IsVisible && DebugDataVisible!=0) SceneManager->registerNodeForRendering(this, irr::scene::ESNRP_TRANSPARENT);

	ISceneNode::OnRegisterSceneNode();
}


void IrrAudio::OnAnimate(u32 timeMs)
{
	ISceneNode::OnAnimate(timeMs);

	// play the sound

	core::vector3df pos = getAbsolutePosition();

	if (Sound)
	{
		Sound->setPosition(pos);

		if(fade_out)
		{
			fade_volume = Sound->getVolume();

			if(timeMs % 1000 == 0)
			{
				fade_volume -= fade_velocidade;
			}

			Sound->setVolume(fade_volume);

			if(fade_volume <= 0)
			{
				stop();
			}
		}

		if(fade_in && fade_volume < fade_volume_atual)
		{
			if(fade_volume == 0)
			{
				fade_volume_atual = Sound->getVolume();
				fade_volume += fade_velocidade;
			}

			if(timeMs % 1000 == 0)
			{
				fade_volume += fade_velocidade;				
			}

			Sound->setVolume(fade_volume);			
		}
		else
		{
			fade_in = false;
		}
	}

	switch(PlayMode)
	{
		case EPM_NOTHING:
			return;
		case EPM_RANDOM:			
			if (Sound && Sound->isFinished())
			{
				Sound->drop();
				Sound = 0;

				// calculate next play time

				s32 delta = MaxTimeMsInterval - MinTimeMsInterval;

				if (delta < 2)
					delta = 2;

				TimeMsDelayFinished = timeMs + (rand()%delta) + MinTimeMsInterval;
			}
			else if (!Sound && (!TimeMsDelayFinished || timeMs > TimeMsDelayFinished))
			{
				// play new sound		

				if (SoundFileName.size())
					Sound = SoundEngine->play3D(SoundFileName.c_str(), pos, false, true, true);

				if (Sound)
				{
					if (MinDistance > 0 )
						Sound->setMinDistance(MinDistance);
					if (MaxDistance > 0 )
						Sound->setMaxDistance(MaxDistance);

					Sound->setIsPaused(false);
				}
			}			
			break;
		case EPM_LOOPING:		
			if (!Sound)
			{
				if (SoundFileName.size())
					Sound = SoundEngine->play3D(SoundFileName.c_str(), pos, true, true, true);

				if (Sound)
				{
					if (MinDistance > 0 )
						Sound->setMinDistance(MinDistance);
					if (MaxDistance > 0 )
						Sound->setMaxDistance(MaxDistance);

					Sound->setIsPaused(false);
				}
				else
				{
					// sound could not be loaded
					stop();
				}
			}			
			break;
		case EPM_ONCE:			
			if (PlayedCount)
			{
				// stop

				if (Sound && Sound->isFinished())
				{
					stop();

					if (DeleteWhenFinished)
						SceneManager->addToDeletionQueue(this);
				}
			}
			else
			{
				// start

				if (SoundFileName.size())
					Sound = SoundEngine->play3D(SoundFileName.c_str(), pos, false, true, true);

				if (Sound)
				{
					if (MinDistance > 0 )
						Sound->setMinDistance(MinDistance);
					if (MaxDistance > 0 )
						Sound->setMaxDistance(MaxDistance);

					Sound->setIsPaused(false);
					++PlayedCount;
				}
				else
				{
					// sound could not be loaded
					stop();
				}
			}
			break;
	}
}


void IrrAudio::render()
{
	// draw scene node as billboard when debug data is visible

	if (!DebugDataVisible)
		return;

	video::IVideoDriver* driver = SceneManager->getVideoDriver();
	driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
      
	scene::ICameraSceneNode* camera = SceneManager->getActiveCamera();
	if (camera)
	{
		video::S3DVertex vertices[4];
		u16 indices[6];

		indices[0] = 0;
		indices[1] = 2;
		indices[2] = 1;
		indices[3] = 0;
		indices[4] = 3;
		indices[5] = 2;

		vertices[0].TCoords.set(0.0f, 1.0f);
		vertices[1].TCoords.set(0.0f, 0.0f);
		vertices[2].TCoords.set(1.0f, 0.0f);
		vertices[3].TCoords.set(1.0f, 1.0f);

		vertices[0].Color.set(128,255,255,255);
		vertices[1].Color.set(128,255,255,255);
		vertices[2].Color.set(128,255,255,255);
		vertices[3].Color.set(128,255,255,255);

		core::vector3df pos = getAbsolutePosition();
		core::vector3df campos = camera->getAbsolutePosition();
		core::vector3df target = camera->getTarget();
		core::vector3df up = camera->getUpVector();
		core::vector3df view = target - campos;
		view.normalize();

		core::vector3df horizontal = up.crossProduct(view);
		horizontal.normalize();

		core::vector3df vertical = horizontal.crossProduct(view);
		vertical.normalize();

		const f32 Size = 5.0f;
		horizontal *= Size / 2.0f;
		vertical *= Size / 2.0f;	

		vertices[0].Pos = pos + horizontal + vertical;
		vertices[1].Pos = pos + horizontal - vertical;
		vertices[2].Pos = pos - horizontal - vertical;
		vertices[3].Pos = pos - horizontal + vertical;

		view *= -1.0f;

		for (s32 i=0; i<4; ++i)
			vertices[i].Normal = view;

		// draw billboard

		video::SMaterial material;
		material.Lighting = false;
		material.MaterialType = video::EMT_TRANSPARENT_ALPHA_CHANNEL;
		material.MaterialTypeParam = 255;
		material.TextureLayer[0].Texture = driver->getTexture("textures/editor_defaults/default_sound.png");

		core::matrix4 mat;
		driver->setTransform(video::ETS_WORLD, mat);
		driver->setMaterial(material);

		driver->drawIndexedTriangleList(vertices, 4, indices, 2);
	}
}


const core::aabbox3d<f32>& IrrAudio::getBoundingBox() const
{
	return Box;
}

const c8* const IrrKlangPlayModeNames[] =
{
	"nothing", "random", "looping",	"play_once", 0
};


//! Returns type of the scene node
ESCENE_NODE_TYPE IrrAudio::getType() const
{
	return (ESCENE_NODE_TYPE)IRRKLANG_SCENE_NODE_ID;
}


void IrrAudio::stop(bool fadeOut, float velocidade)
{
	PlayMode = EPM_NOTHING;
	PlayedCount = 0;

	if (Sound)
	{
		fade_in = false;
		fade_out = fadeOut;
		fade_velocidade = velocidade;

		if(!fade_out)
		{
			Sound->stop();
			Sound->drop();
			Sound = 0;
		}
	}
}

bool IrrAudio::isFinished()
{
	return Sound->isFinished();
}

void IrrAudio::setVolume(ik_f32 volume)
{
	Sound->setVolume(volume);
}

//! Sets the play mode to 'play once', a sound file is played once, and 
//! the scene node deletes itself then, if wished.
void IrrAudio::setPlayOnceMode(bool fadeIn, float velocidade,bool deleteWhenFinished)
{
	stop();
	PlayMode = EPM_ONCE;
	PlayedCount = 0;

	fade_in = fadeIn;
	fade_velocidade = velocidade;
	DeleteWhenFinished = deleteWhenFinished;
	if(fade_in)
	{
		//fade_volume_atual = Sound->getVolume();
		fade_volume = 0.0f;
		//Sound->setVolume(fade_volume);
	}
}


//! Sets the play mode to 'looping stream', plays a looped sound over and over again.
void IrrAudio::setLoopingStreamMode(bool fadeIn, float velocidade)
{
	stop();
	PlayMode = EPM_LOOPING;
	fade_in = fadeIn;
	fade_velocidade = velocidade;
	if(fade_in)
	{
		//fade_volume_atual = Sound->getVolume();
		fade_volume = 0.0f;
		//Sound->setVolume(fade_volume);
	}
}


//! Sets the play mode to 'random'. Plays a sound with a variable, random interval
//! over and over again.
//! \param minTimeMs: Minimal wait time in milli seconds before the sound is played again.
//! \param maxTimeMs: Maximal wait time in milli seconds before the sound is played again.
void IrrAudio::setRandomMode(int minTimeMs, int maxTimeMs)
{
	stop();
	PlayMode = EPM_RANDOM;
	MinTimeMsInterval = minTimeMs;
	MaxTimeMsInterval = maxTimeMs;
}


//! Sets the sound filename to play
void IrrAudio::setSoundFileName(const char* soundFilename)
{
	if (soundFilename)
		SoundFileName = soundFilename;
	else
		SoundFileName = "";
}


//! Gets the sound filename to play
const char* IrrAudio::getSoundFileName() const
{
	return SoundFileName.c_str();
}


//! Sets the minimal and maximal 3D sound distances
void IrrAudio::setMinMaxSoundDistance(f32 minDistance, f32 maxDistance)
{
	MinDistance = minDistance;
	MaxDistance = maxDistance;

	if (Sound)
	{
		if (MinDistance > 0)
			Sound->setMinDistance(MinDistance);

		if (MaxDistance > 0)
			Sound->setMaxDistance(MaxDistance);
	}
}