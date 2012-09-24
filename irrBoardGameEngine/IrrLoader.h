#pragma once
#include "IrrBoard.h"

using namespace irr;
using namespace scene;
using namespace core;
using namespace std;

/*

Classe Loader (carrega arquivos - board com índices separados por espaços, strings que definem o comportamento dos índices e caminhos de imagem)

*/

namespace IrrBoardGameEngine {

	class IrrLoader
	{
	public:
		IrrLoader(void);
		~IrrLoader(void);
	};

}