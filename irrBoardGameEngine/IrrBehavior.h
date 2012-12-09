#pragma once
#include "irrlicht.h"
#include "irrKlang.h"

#include <map>
#include <string>

#include "IrrInput.h"
#include "Vector.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace irrklang;

//
// Classe responsavel pelo controle de comportamento
// de qualquer objeto adicionado na cena
//

namespace IrrBoardGameEngine {
class IrrBehavior
{
	public:
		IVideoDriver *driver;
		ISceneManager *smgr;
		ISoundEngine *soundEngine;
		IrrInput * input;

		//
		// Executado ao iniciar o comportamento
		//
		virtual void init() = 0;

		//
		// Executado a cada loop
		//
		virtual void update() = 0;

		//
		// Pode ser usado para apagar ou reconfigurar variaveis
		//
		virtual void reset() = 0;

		//
		// Funções de retorno de variaveis diversas
		//
		virtual void setInt(char const * key, int value) = 0;
		virtual int getInt(char const * key) = 0;

		virtual void setFloat(char const * key, float value) = 0;
		virtual float getFloat(char const * key) = 0;

		virtual void setBool(char const * key, bool value) = 0;
		virtual bool getBool(char const * key) = 0;

		virtual void setVector(char const * key, Vector value) = 0;
		virtual Vector getVector(char const * key) = 0;
	};
}
