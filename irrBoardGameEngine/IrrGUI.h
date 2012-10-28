#pragma once

#include <map>
#include <string>

#include "irrlicht.h"
#include "irrKlang.h"
#include "IrrInput.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace irrklang;
using namespace gui;

namespace IrrBoardGameEngine {
	struct EState
	{
		bool mouseOver;
		bool clicked;
		EState() : mouseOver(false), clicked(false) { }

	};

	class IrrGUI
	{
	public:
		IrrGUI(IrrlichtDevice *);
		~IrrGUI(void);

		void resetPressed();
		void setButtonPressed(s32 id, bool value);
		void setMouseOver(s32 id, bool value);


		EState getElementState(s32 id);	
		//bool getMouseOver(s32 id);

		//TEXTOS
		void addLabel(s32 id, char *text, int minX, int minY, int maxX, int maxY);
        void setText(s32 id, char *text);
        void setLabel(s32 id, bool visible);
        bool getLabel(s32 id);
        void removeLabel(s32 id);

		//IMAGENS
        void addImage(s32 id, char* file, int x, int y);
        void setImage(s32 id, bool visible);
        bool getImage(s32 id);
        void removeImage(s32 id);

		//BOTOES
		void addButton(s32 id, char* fileNormal, char* filePressed, int x, int y, int w, int h);
		void setButton(s32 id, bool visible);
		void removeButton(s32 id);

		void update();

		//ativa a scena
		void setActive(bool flag);

		IGUIEnvironment * getGUIenv();
		void drawAll();

	protected:

		IGUIElement * rootGUI;

		IGUIEnvironment *guienv;
		IVideoDriver *driver;		

		std::map<s32, IGUIImage*> imagens;
		std::map<s32, IGUIStaticText*> labels;
		std::map<s32, IGUIButton*> buttons;

		std::map<s32, EState> elementState;
	};
}
