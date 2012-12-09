#include "IrrAudio.h"
#include <iostream>

using namespace IrrBoardGameEngine;

//
// Configurações para o nodo da cena!
// com o seu id e o tipo!
//
const int IRRKLANG_SCENE_NODE_ID = MAKE_IRR_ID('i','k','n','g');
const char* IrrAudioTypeName = "IrrAudio";

IrrAudio::IrrAudio(irrklang::ISoundEngine* soundEngine, scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id) : scene::ISceneNode(parent, mgr, id), SoundEngine(soundEngine)
{
	setAutomaticCulling(scene::EAC_OFF);

	//
	// Configurações padrões
	//
	MinDistance = 20.0f;
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
	fade_intervalo_tempo = 50.0f;
	fade_volume = 0.0f;
	fade_tempo_then = 0.0f;

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

	//
	// Se houver verdadeiro
	// é realizada a contagem de tempo para o 'fade' funcionar
	//
	if(fade_out || fade_in)
	{
		fade_tempo_now = (float)timeMs;
		if(fade_tempo_then == 0)
		{
			fade_tempo_delta = 0;
		}
		else
		{
			fade_tempo_delta = fade_tempo_now - fade_tempo_then;
		}
		fade_tempo_then = fade_tempo_now;

		fade_inc_tempo += 1.0f * fade_tempo_delta;
	}

	core::vector3df pos = getAbsolutePosition();
	
	//
	// Se o som estiver sendo executado
	//
	if (Sound)
	{
		Sound->setPosition(pos);

		//
		// Controla o fluxo do 'fade'
		// 
		if(fade_out)
		{
			fade_volume = Sound->getVolume();

			if(fade_inc_tempo > fade_intervalo_tempo)
			{
				fade_volume -= fade_velocidade;
				fade_inc_tempo = 0;
			}

			if(fade_volume <= 0)
			{
				Sound->setVolume(0);
				stop();
			}
			else
			{
				Sound->setVolume(fade_volume);
			}
		}

		if(fade_in && fade_volume < fade_volume_atual)
		{
			if(fade_volume == 0)
			{
				fade_volume_atual = Sound->getVolume();
				fade_volume += fade_velocidade;
			}

			if(fade_inc_tempo > fade_intervalo_tempo)
			{
				fade_volume += fade_velocidade;	
				fade_inc_tempo = 0;
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

				//
				// Calcula o proximo tempo
				//

				s32 delta = MaxTimeMsInterval - MinTimeMsInterval;

				if (delta < 2)
					delta = 2;

				TimeMsDelayFinished = timeMs + (rand()%delta) + MinTimeMsInterval;
			}
			else if (!Sound && (!TimeMsDelayFinished || timeMs > TimeMsDelayFinished))
			{
				//
				// Toca um novo som
				//
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
					//
					// Caso não conseguir carregar o som ele é descartado.
					//
					stop();
				}
			}			
			break;
		case EPM_ONCE:			
			if (PlayedCount)
			{
				//
				// Caso o som chegou no fim				
				//
				if (Sound && Sound->isFinished())
				{
					stop();

					if (DeleteWhenFinished)
						SceneManager->addToDeletionQueue(this);
				}
			}
			else
			{
				//
				// Inicia o som
				//
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
					//
					// Caso não conseguir carregar o som ele é descartado.
					//
					stop();
				}
			}
			break;
	}
}


void IrrAudio::render()
{
	//
	// Desenha na tela, caso configurado um billboard
	//
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
		
		//
		// Desenha na tela
		//
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

ESCENE_NODE_TYPE IrrAudio::getType() const
{
	return (ESCENE_NODE_TYPE)IRRKLANG_SCENE_NODE_ID;
}

void IrrAudio::stop(bool fadeOut, float tempo)
{
	PlayMode = EPM_NOTHING;
	PlayedCount = 0;

	if (Sound)
	{
		fade_in = false;
		fade_out = fadeOut;

		if(!fade_out)
		{
			Sound->stop();
			Sound->drop();
			Sound = 0;
		}
		else
		{
			fade_inc_tempo = 0.0f;
			fade_tempo_then = 0.0f;
			fade_velocidade = (1 / ((tempo * 1000) / fade_intervalo_tempo));
		}
	}
}

bool IrrAudio::isFinished()
{
	return Sound == 0 ? true : false;
}

void IrrAudio::setVolume(ik_f32 volume)
{
	Sound->setVolume(volume);
}

void IrrAudio::setPlayOnceMode(bool fadeIn, float tempo, bool deleteWhenFinished)
{
	stop();
	PlayMode = EPM_ONCE;
	PlayedCount = 0;
	
	fade_out = false;
	fade_in = fadeIn;
	DeleteWhenFinished = deleteWhenFinished;
	if(fade_in)
	{
		fade_volume = 0.0f;
		fade_inc_tempo = 0.0f;
		fade_tempo_then = 0.0f;
		fade_velocidade = (1 / ((tempo * 1000) / fade_intervalo_tempo));
	}
}

void IrrAudio::setLoopingStreamMode(bool fadeIn, float tempo)
{
	stop();
	PlayMode = EPM_LOOPING;

	fade_out = false;
	fade_in = fadeIn;	
	if(fade_in)
	{
		fade_volume = 0.0f;
		fade_inc_tempo = 0.0f;
		fade_tempo_then = 0.0f;
		fade_velocidade = (1 / ((tempo * 1000) / fade_intervalo_tempo));
	}
}

void IrrAudio::setRandomMode(int minTimeMs, int maxTimeMs)
{
	stop();
	PlayMode = EPM_RANDOM;
	MinTimeMsInterval = minTimeMs;
	MaxTimeMsInterval = maxTimeMs;
}

void IrrAudio::setSoundFileName(const char* soundFilename)
{
	if (soundFilename)
		SoundFileName = soundFilename;
	else
		SoundFileName = "";
}

const char* IrrAudio::getSoundFileName() const
{
	return SoundFileName.c_str();
}

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