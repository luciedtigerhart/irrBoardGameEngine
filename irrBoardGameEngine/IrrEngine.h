#pragma once

#include "irrlicht.h"
#include "irrKlang.h"

#include "IrrScene.h"
#include "IrrInput.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

using namespace irrklang;

namespace IrrBoardGameEngine {
	class IrrEngine
	{
	private:
		//singleton
		static IrrEngine *instance;
		IrrEngine(void);

		//manager
		IrrlichtDevice *device;
		IVideoDriver *driver;
		ISceneManager *smgr;
		ISoundEngine *soundEngine;
		InputReceiver *inputsReceiver;
		
		//default
		f32 frameDeltaTime;
		IrrScene *currentScene;

	public:
		//init
		int init();
		static IrrEngine *GetInstance();

		void loop();
		void loop(IrrScene*);

		void setCurrentScene(IrrScene *s);
		IrrScene *createScene();
		IrrScene *getScene();

		float getDeltaTime();

		
		~IrrEngine(void);
	};
}
