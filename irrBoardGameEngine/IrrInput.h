#pragma once

#include <map>
#include <string>
#include "irrlicht.h"
#include "IrrGUI.h"
#include "IrrCamera.h"

using namespace irr;
using namespace scene;
using namespace std;
using namespace video;

namespace IrrBoardGameEngine {
	class IrrGUI;
	class IrrCamera;
	class IrrInput: public IEventReceiver
	{
	public:		
		struct SMouseState
		{
			core::position2di position;
			bool leftButtonDown;
			bool rightButtonDown;
			bool middleButtonDown;
			SMouseState() : leftButtonDown(false), rightButtonDown(false), middleButtonDown(false) { }
		} mouseState;

		IrrInput();
		virtual bool OnEvent(const SEvent& event);
		bool isKeyDown(int keyCode);
		bool isKeyReleased(int keyCode);
		bool isKeyPressed(int keyCode);
		void clear();
		void update();

		void setDriver(IVideoDriver *);
		void setDevice(IrrlichtDevice *);
		void setGUI(IrrGUI *);
		s32 guiElementid;

		void setCamera(IrrCamera *);

		const SMouseState & getMouseState(void) const { return mouseState; }
	private:

		IrrGUI * gui;
		IrrCamera * camera;
		IVideoDriver * driver;
		IrrlichtDevice * device;

		void setKeyStatus(int* k, int keyCode, bool value);
		bool getKeyStatus(int* k, int keyCode);

		//
		// Armazena o estado das teclas pressionadas
		//
		int keyStatusDown[KEY_KEY_CODES_COUNT / 32];
		int keyStatusPressed[KEY_KEY_CODES_COUNT / 32];
		int keyStatusReleased[KEY_KEY_CODES_COUNT / 32];

		float deltaTime;
		int now, then;
	};
}