#pragma once

#include "irrlicht.h"

using namespace irr;
using namespace scene;

namespace IrrBoardGameEngine {
	class InputReceiver{
	public:
		virtual bool isKeyDown(int keyCode) = 0;
		virtual bool isKeyReleased(int keyCode) = 0;
		virtual bool isKeyPressed(int keyCode) = 0;
		virtual void clear() = 0;
	};

	class IrrInput: public IEventReceiver, public InputReceiver
	{
	public:
		IrrInput(void);
		~IrrInput(void);
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