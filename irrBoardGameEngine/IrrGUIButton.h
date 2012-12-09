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

		//
		// Imagens usada para o desenho do botão
		//
		IGUIImage* img_normal;
		IGUIImage* img_hover;
		IGUIImage* img_pressed;
		IGUIImage* img_pressed_hover;
		IGUIImage* img_disabled;

		s32 id;
		int x;
		int y;

		//
		// Controla o estado do botão
		//
		bool pressed;
		bool hover;
		bool visible;
		bool toggle;
		bool disabled;

		IGUIElement* parent_node;

	public:
		IrrGUIButton(IGUIEnvironment *, IVideoDriver *, s32 ID, int posx, int posy, IGUIElement* parent=0, bool Toggle = false);

		//
		// Carrega as imagens
		//
		void addImage(char* file);
		void addImageHover(char* file);
		void addImagePressed(char* file);
		void addImagePressedHover(char* file);
		void addImageDisabled(char* file);

		//
		// Configura o estado do botão
		//
		void setHover(bool value);
		bool isHover();

		void setPressed(bool value);
		bool isPressed();

		void setVisible(bool value);

		void setDisabled(bool value);
		bool isDisabled();

		//
		// Atualiza os estados e a imagem para o desenho
		//
		void update();

		~IrrGUIButton(void);
	};
}