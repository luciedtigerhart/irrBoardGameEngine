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

		// We'll create a struct to record info on the mouse state
		struct SMouseState
		{
			core::position2di position;
			bool leftButtonDown;
			bool rightButtonDown;
			SMouseState() : leftButtonDown(false), rightButtonDown(false) { }
		} mouseState;

		IrrInput();
		virtual bool OnEvent(const SEvent& event);
		bool isKeyDown(int keyCode);
		bool isKeyReleased(int keyCode);
		bool isKeyPressed(int keyCode);
		void clear();
		void update();

		void setDriver(IVideoDriver *);
		void setGUI(IrrGUI *);
		void setCamera(IrrCamera *);
		/*
		//registra uma comando de teclado
		void registry(char *, int);

		bool getButton(char *);
		bool getButtonDown(char *);
		bool getButtonPressed(char *);
		bool getButtonReleased(char *);

		multimap<std::string,int> *keys;
		*/
		const SMouseState & getMouseState(void) const { return mouseState; }
	private:

		IrrGUI * gui;
		IrrCamera * camera;
		IVideoDriver * driver;

		void setKeyStatus(int* k, int keyCode, bool value);
		bool getKeyStatus(int* k, int keyCode);

		//Armazena o estado das teclas pressionadas
		int keyStatusDown[KEY_KEY_CODES_COUNT / 32];
		int keyStatusPressed[KEY_KEY_CODES_COUNT / 32];
		int keyStatusReleased[KEY_KEY_CODES_COUNT / 32];
	};
}