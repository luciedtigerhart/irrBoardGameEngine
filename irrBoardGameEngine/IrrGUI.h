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

		//
		// TEXTOS NORMAIS
		//
		void addLabel(s32 id, char *text, int minX, int minY, int maxX, int maxY, video::SColor color = video::SColor(255, 0, 0, 0), s32 idFont = -1);
        void setText(s32 id, char *text);
		void setLabelColor(s32 id, video::SColor color);
        void setLabelVisible(s32 id, bool visible);
        bool getLabelIsVisible(s32 id);
        void removeLabel(s32 id);

		//
		// TEXTOS COM FONT
		//
		void addFont(s32 id, char * src, s32 space = 1, s32 lineHeight = 1);
		IGUIFont* getFont(s32 id);		

		//
		// IMAGENS
		//
        void addImage(s32 id, char* file, int x, int y);
        void setImage(s32 id, bool visible);
        bool getImage(s32 id);
        void removeImage(s32 id);

		//
		// BOTOES
		//
		void setDisabledButton(s32 id, bool value);
		bool isDisabledButton(s32 id);
		void setPressedButton(s32 id, bool value);
		void setPressedButton(bool value);
		bool isPressedButton(s32 id);
		void setMouseOver(s32 id, bool value);
		bool isMouseOver(s32 id);

		void addButton(s32 id, char* fileNormal, char* fileHover, char* filePressed, char* filePressedHover, int x, int y, bool toggle = false, char* fileDisabled = NULL);
		void setButton(s32 id, bool visible);
		void removeButton(s32 id);

		//
		// ATUALIZA
		//
		void update();

		//
		// Controla o 'fade' da gui
		//
		void fadeIn(u32 time, video::SColor color = video::SColor(255, 0, 0, 0));
		void fadeOut(u32 time, video::SColor color = video::SColor(255, 0, 0, 0));
		void fade(u32 time, bool in = true, video::SColor color = video::SColor(255, 0, 0, 0));
		bool isReadyfade();

		//
		// ATIVA A CENA
		//
		void setActive(bool flag);

		IGUIEnvironment * getGUIenv();

		//
		// Desenha a 'gui'
		//
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
		std::map<s32, IGUIFont*> fonts;
		IGUIFont* font2;
	};
}
