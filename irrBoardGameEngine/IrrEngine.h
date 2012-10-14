#pragma once

#include "irrlicht.h"
#include "irrKlang.h"
#include "Vector.h"
#include <stack>
#include <string>
#include <vector>

#include "IrrInput.h"
#include "IrrBehavior.h"
#include "IrrGameObject.h"

#include "IrrScene.h"
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
		IrrInput * input;

		//manager
		IrrlichtDevice *device;
		IVideoDriver *driver;
		ISceneManager *smgr;
		ISoundEngine *soundEngine;
		IGUIEnvironment * guienv;

	public:		
		static IrrEngine *getInstance();
		
		void loop();
		void loop(IrrGUI * gui);
		void loop(IrrScene*,IrrGUI * gui);

		void setCurrentScene(IrrScene *s);
		IrrScene *createScene();
		IrrScene *getScene();

		void setCurrentGUI(IrrGUI * gui);
		IrrGUI *createGUI();
		IrrGUI *getGUI();

		IrrInput *getInput();
		IrrlichtDevice *getDevice();
		IVideoDriver *getDriver();
		ISceneManager *getSceneManager();
		ISoundEngine *getSoundEngine();
		IGUIEnvironment * getGUIenv();

		float getDeltaTime();
		
		~IrrEngine(void);
	};
}
