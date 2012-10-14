#pragma once

#include "irrlicht.h"
#include "irrKlang.h"

#include "IrrTile.h"
#include "IrrBoard.h"
#include "IrrLoader.h"
#include "IrrScene.h"
#include "IrrInput.h"
#include "IrrGUI.h"

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
		
		//default
		f32 frameDeltaTime;
		IrrScene *currentScene;
		IrrGUI * currentGUI;

	public:		
		static IrrEngine *GetInstance();

		void loop();
		void loop(IrrGUI * gui);
		void loop(IrrScene*,IrrGUI * gui);

		void setCurrentScene(IrrScene *s);
		IrrScene *createScene();
		IrrScene *getScene();

		void setCurrentGUI(IrrGUI * gui);
		IrrGUI *createGUI();
		IrrGUI *getGUI();

		// Controle do INPUT
		IrrInput * input;

		float getDeltaTime();
		
		~IrrEngine(void);

		//manager
		IrrlichtDevice *device;
		IVideoDriver *driver;
		ISceneManager *smgr;
		ISoundEngine *soundEngine;
		IGUIEnvironment * guienv;
	};
}
