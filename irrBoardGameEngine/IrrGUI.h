#pragma once

#include <map>
#include <string>

#include "irrlicht.h"
#include "irrKlang.h"
#include "IrrInput.h"
#include "IrrGUIButton.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace irrklang;
using namespace gui;

namespace IrrBoardGameEngine {
	class IrrGUI
	{
	public:
		IrrGUI(IrrlichtDevice *);
		~IrrGUI(void);
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
		void setPressedButton(s32 id, bool value);
		void setPressedButton(bool value);
		bool isPressedButton(s32 id);
		void setMouseOver(s32 id, bool value);
		bool isMouseOver(s32 id);

		void addButton(s32 id, char* fileNormal, char* fileHover, char* filePressed, char* filePressedHover, int x, int y, bool toggle = false);
		void setButton(s32 id, bool visible);
		void removeButton(s32 id);

		//ATUALIZA
		void update();

		void fadeIn(u32 time);
		void fadeOut(u32 time);
		void fade(u32 time, bool in = true);
		bool isReadyfade();

		//ATIVA A CENA
		void setActive(bool flag);

		IGUIEnvironment * getGUIenv();
		void drawAll();

	protected:

		IGUIElement * rootGUI;
		IGUIInOutFader* fader;
		bool isfadein;

		IGUIEnvironment *guienv;
		IVideoDriver *driver;	

		std::map<s32, IGUIImage*> imagens;
		std::map<s32, IGUIStaticText*> labels;
		std::map<s32, IrrGUIButton*> buttons;
	};
}
