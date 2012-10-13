#pragma once

#include <map>
#include <string>
#include "irrlicht.h"

using namespace irr;
using namespace scene;
using namespace std;

namespace IrrBoardGameEngine {
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

		//registra uma comando de teclado
		void registry(char *, int);

		bool getButton(char *);
		bool getButtonDown(char *);
		bool getButtonPressed(char *);
		bool getButtonReleased(char *);

	private:
		multimap<std::string,int> *keys;

		void setKeyStatus(int* k, int keyCode, bool value);
		bool getKeyStatus(int* k, int keyCode);

		//Armazena o estado das teclas pressionadas
		int keyStatusDown[KEY_KEY_CODES_COUNT / 32];
		int keyStatusPressed[KEY_KEY_CODES_COUNT / 32];
		int keyStatusReleased[KEY_KEY_CODES_COUNT / 32];

		const SMouseState & getMouseState(void) const { return mouseState; }
	};
}