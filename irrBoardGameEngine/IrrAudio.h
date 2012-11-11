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

		// play modes:

		//! Sets the play mode to 'play once', a sound file is played once, and 
		//! the scene node deletes itself then, if wished.
		void setPlayOnceMode(bool fadeIn = false, float velocidade = 0.1f,bool deleteWhenFinished=false);

		//! Sets the play mode to 'looping stream', plays a looped sound over and over again.
		void setLoopingStreamMode(bool fadeIn = false, float velocidade = 0.1f);

		//! Sets the play mode to 'random'. Plays a sound with a variable, random interval
		//! over and over again.
		//! \param minTimeMsInterval: Minimal wait time in milli seconds before the sound is played again.
		//! \param maxTimeMsInterval: Maximal wait time in milli seconds before the sound is played again.
		void setRandomMode(int minTimeMsInterval=1000, int maxTimeMsInterval=5000);

		// Sound parameters

		//! Sets the sound filename to play
		void setSoundFileName(const char* soundFilename);

		//! Gets the sound filename to play
		const char* getSoundFileName() const;

		//! Sets the minimal and maximal 3D sound distances.
		//! Set to negative values if you want to use the default values of the sound engine.
		void setMinMaxSoundDistance(f32 minDistance=1.0f, f32 maxDistance=10000000.0f);

		//! stops playback, releases sound, sets playmode to 'nothing'
		void stop(bool fadeOut = false, float velocidade = 0.1f);

		//
		bool isFinished();
		void setVolume(ik_f32 volume);

		// rendering functions:
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

		bool fade_in;
		bool fade_out;
		float fade_velocidade;
		float fade_volume;
		float fade_volume_atual;

		core::aabbox3d<f32> Box;
		irrklang::ISoundEngine* SoundEngine;
		irrklang::ISound* Sound;

		core::stringc SoundFileName;
		f32 MinDistance;
		f32 MaxDistance;

		EPlayMode PlayMode;
		u32 TimeMsDelayFinished;
		bool DeleteWhenFinished;
		s32 MaxTimeMsInterval;
		s32 MinTimeMsInterval;
		s32 PlayedCount;
	};
}
#endif