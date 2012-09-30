#pragma once

#include "irrlicht.h"
#include "irrKlang.h"

#include "IrrTile.h"
#include "IrrBoard.h"
#include "IrrLoader.h";
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

		//init
		int init();

		//manager
		IrrlichtDevice *device;
		IVideoDriver *driver;
		ISceneManager *smgr;
		ISoundEngine *soundEngine;
		IrrInput *inputsReceiver;
		
		//default
		f32 frameDeltaTime;
		IrrScene *currentScene;

	public:		
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
