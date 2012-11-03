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
		//int init(video::E_DRIVER_TYPE deviceType,const core::dimension2d<u32>& windowSize,u32 bits,bool fullscreen,bool stencilbuffer,bool vsync);
		int init(video::E_DRIVER_TYPE deviceType = video::EDT_SOFTWARE,const core::dimension2d<u32>& windowSize = (core::dimension2d<u32>(640,480)),u32 bits = 16,bool fullscreen = false,bool stencilbuffer = false,bool vsync = false,const wchar_t* text = L"IrrBGE");

		//default
		f32 frameDeltaTime;
		IrrScene *currentScene;
		IrrGUI * currentGUI;
		IrrInput * input;

		//manager
		IrrlichtDevice *device;
		IVideoDriver *driver;
		//ISceneManager *smgr;
		ISoundEngine *soundEngine;
		//IGUIEnvironment * guienv;


	public:		
		//static IrrEngine *getInstance(video::E_DRIVER_TYPE deviceType,const core::dimension2d<u32>& windowSize,u32 bits,bool fullscreen,bool stencilbuffer,bool vsync);		
		static IrrEngine *getInstance(video::E_DRIVER_TYPE deviceType = video::EDT_SOFTWARE,const core::dimension2d<u32>& windowSize = (core::dimension2d<u32>(640,480)),u32 bits = 16,bool fullscreen = false,bool stencilbuffer = false,bool vsync = false,const wchar_t* text = L"IrrBGE");
		
		void loop(void(*f)());
		void loop(void(*f)(),IrrGUI * gui);
		void loop(void(*f)(),IrrScene*,IrrGUI * gui);

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
