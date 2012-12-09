#ifndef __IRRKLANG_SCENE_NODE_H_INCLUDED__
#define __IRRKLANG_SCENE_NODE_H_INCLUDED__

#include <irrlicht.h>
#include <irrKlang.h>

using namespace irr;
using namespace irrklang;
using namespace scene;

namespace IrrBoardGameEngine
{
	class IrrAudio : public scene::ISceneNode
	{
	public:

		IrrAudio(irrklang::ISoundEngine* soundEngine, scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id);
		~IrrAudio();

		//
		// Modos para iniciar o som:
		//

		//
		// Quando utilizado o modo 'play once', o som ser� tocado apenas uma vez
		// � possivel configurar que o som surja em 'fadeIn', e o tempo de dura��o do 'fade'
		// 
		void setPlayOnceMode(bool fadeIn = false, float tempo = 0.1f,bool deleteWhenFinished=false);
		
		//
		// Quando utilizado o modo 'looping stream', o som ficar� em loop
		// � possivel configurar que o som surja em 'fadeIn', e o tempo de dura��o do 'fade'
		//
		void setLoopingStreamMode(bool fadeIn = false, float tempo = 1.0f);

		//
		// Quando utilizado o modo 'random'. o som ser� tocado com um intervalo aleatorio
		//
		void setRandomMode(int minTimeMsInterval=1000, int maxTimeMsInterval=5000);

		//
		// Parametros do som
		//

		//
		// Configura o aquivo do som
		//
		void setSoundFileName(const char* soundFilename);

		//
		// Devolve o nome do arquivo de som
		//
		const char* getSoundFileName() const;

		//
		// Configura��es do som 3D, determina a minima distancia e m�xima que o som ser� tocado
		//
		void setMinMaxSoundDistance(f32 minDistance=1.0f, f32 maxDistance=10000000.0f);

		//
		// O som � parado, � possivel determinar um fadeOut para o som, passando o tempo de dura��o
		//
		void stop(bool fadeOut = false, float tempo = 1.0f);

		//
		// Devolve quando o som terminou
		//
		bool isFinished();

		//
		// Configura o volume do som
		//
		void setVolume(ik_f32 volume);

		//
		// Fun��es de rendering
		//
		virtual void OnAnimate(u32 timeMs);
		virtual void OnRegisterSceneNode();
		virtual void render();
		virtual const core::aabbox3d<f32>& getBoundingBox() const;
		virtual ESCENE_NODE_TYPE getType() const;

	protected:

		enum EPlayMode
		{
			EPM_NOTHING = 0,
			EPM_RANDOM,
			EPM_LOOPING,
			EPM_ONCE
		};

		//
		// Variaveis de controle do fade
		//
		bool fade_in;
		bool fade_out;
		float fade_velocidade;
		float fade_intervalo_tempo;
		float fade_inc_tempo;

		float fade_tempo_now;
		float fade_tempo_then;
		float fade_tempo_delta;

		float fade_volume;
		float fade_volume_atual;

		//
		// Variaveis de controle do som
		//
		core::aabbox3d<f32> Box;
		irrklang::ISoundEngine* SoundEngine;
		irrklang::ISound* Sound;
		core::stringc SoundFileName;

		//
		// Controle do som 3D
		//
		f32 MinDistance;
		f32 MaxDistance;

		//
		// Controle enquanto o som est� em execu��o
		//
		EPlayMode PlayMode;
		u32 TimeMsDelayFinished;
		bool DeleteWhenFinished;
		s32 MaxTimeMsInterval;
		s32 MinTimeMsInterval;
		s32 PlayedCount;
	};
}
#endif