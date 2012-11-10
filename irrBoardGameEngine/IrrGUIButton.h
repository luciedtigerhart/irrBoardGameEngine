#pragma once

#include <map>
#include <string>
#include <iostream>

#include "irrlicht.h"
#include "irrKlang.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace irrklang;
using namespace gui;

namespace IrrBoardGameEngine {
	class IrrGUIButton
	{
	private:
		IGUIEnvironment *guienv;
		IVideoDriver *driver;

		IGUIImage* img_normal;
		IGUIImage* img_hover;
		IGUIImage* img_pressed;
		IGUIImage* img_pressed_hover;
		IGUIImage* img_disabled;

		s32 id;
		int x;
		int y;

		bool pressed;
		bool hover;
		bool visible;
		bool toggle;
		bool disabled;

		IGUIElement* parent_node;

	public:
		IrrGUIButton(IGUIEnvironment *, IVideoDriver *, s32 ID, int posx, int posy, IGUIElement* parent=0, bool Toggle = false);

		void addImage(char* file);
		void addImageHover(char* file);
		void addImagePressed(char* file);
		void addImagePressedHover(char* file);
		void addImageDisabled(char* file);

		void setHover(bool value);
		bool isHover();

		void setPressed(bool value);
		bool isPressed();

		void setVisible(bool value);

		void setDisabled(bool value);
		bool isDisabled();

		void update();

		~IrrGUIButton(void);
	};
}