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
		static IrrEngine *instance;
		IrrEngine(void);

		//
		// Inicializa o motor
		//
		int init(video::E_DRIVER_TYPE deviceType = video::EDT_SOFTWARE,const core::dimension2d<u32>& windowSize = (core::dimension2d<u32>(640,480)),u32 bits = 16,bool fullscreen = false,bool stencilbuffer = false,bool vsync = false,const wchar_t* text = L"IrrBGE");

		//
		// Controla tempo do frame
		//
		f32 frameDeltaTime;

		//
		// Variaveis de controle da cena, GUI atuais
		//
		IrrScene *currentScene;
		IrrGUI * currentGUI;

		//
		// Controla o input. teclado e mouse
		//
		IrrInput * input;

		//
		// gerenciamento do video e som
		//
		IrrlichtDevice *device;
		IVideoDriver *driver;		
		ISoundEngine *soundEngine;

	public:		
		static IrrEngine *getInstance(video::E_DRIVER_TYPE deviceType = video::EDT_SOFTWARE,const core::dimension2d<u32>& windowSize = (core::dimension2d<u32>(640,480)),u32 bits = 16,bool fullscreen = false,bool stencilbuffer = false,bool vsync = false,const wchar_t* text = L"IrrBGE");
		
		//
		// Loop normal
		//
		void loop(void(*f)());

		//
		// Para poder criar um loop personalizado
		//
		bool run();
		void update();
		void draw();

		//
		// Controla a cena
		//
		void setCurrentScene(IrrScene *s);
		IrrScene *createScene();
		IrrScene *getScene();

		//
		// Controla a GUI
		//
		void setCurrentGUI(IrrGUI * gui);
		IrrGUI *createGUI();
		IrrGUI *getGUI();

		//
		// Retorna os recusos que o motor possui
		//
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
