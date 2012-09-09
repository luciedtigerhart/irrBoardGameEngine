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
		IrrInput();
		virtual bool OnEvent(const SEvent& event);
		bool isKeyDown(int keyCode);
		bool isKeyReleased(int keyCode);
		bool isKeyPressed(int keyCode);
		void clear();
		void update();
	private:
		void setKeyStatus(int* k, int keyCode, bool value);
		bool getKeyStatus(int* k, int keyCode);

		//Armazena o estado das teclas pressionadas
		int keyStatusDown[KEY_KEY_CODES_COUNT / 32];
		int keyStatusPressed[KEY_KEY_CODES_COUNT / 32];
		int keyStatusReleased[KEY_KEY_CODES_COUNT / 32];
	};
}