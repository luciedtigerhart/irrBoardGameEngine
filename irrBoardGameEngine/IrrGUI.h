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
	class IrrGUI
	{
	protected:

		IGUIElement * rootGUI;

		IGUIEnvironment *guienv;
		IVideoDriver *driver;
		IrrInput *input;

		std::map<std::string, IGUIImage*> imagens;
		std::map<std::string, IGUIStaticText*> labels;
		std::map<std::string, IGUIButton*> buttons;

	public:

		IrrGUI(IrrlichtDevice *, IrrInput *);
		~IrrGUI(void);

		//TEXTOS
		void addLabel(char *name, char *text, int minX, int minY, int maxX, int maxY);
        void setText(char *name, char *text);
        void setLabel(char *name, bool visible);
        bool getLabel(char *name);
        void removeLabel(char *name);

		//IMAGENS
        void addImage(char *name, char* file, int x, int y);
        void setImage(char *name, bool visible);
        bool getImage(char *name);
        void removeImage(char *name);

		//BOTOES
		void addButton(char *name, char* fileNormal, char* filePressed, int x, int y, int w, int h);
		void setButton(char *name, bool visible);
		void removeButton(char *name);

		void update();

		//ativa a scena
		void setActive(bool flag);

		IGUIEnvironment * getGUIenv();
		void drawAll();
	};
}
