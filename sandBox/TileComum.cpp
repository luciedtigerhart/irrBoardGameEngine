#include "TileComum.h"


TileComum::TileComum(void)
{
	//faz alguma coisa
}


TileComum::~TileComum(void)
{
	//destroi alguma coisa
}


void TileComum::init(void)
{	
	//tile->node->setMaterialTexture(0, driver->getTexture("obj/texturas/grama.jpg"));
}

void TileComum::update(void)
{
	// Movimentação
	float dT = IrrEngine::getInstance()->getDeltaTime();

	if(tile->isMouseHover)
	{
		//
		// CASO CLICAR O BOTÃO ESQUERDO
		//
		if(input->mouseState.leftButtonDown)
		{
			//
			// FAZ UMA LEITURA DE TODOS OS TILES
			//
			std::list<IrrTile*> * list = tile->parentNode->getAllTiles();
			std::list<IrrTile*>::iterator it_list;
			for(it_list=list->begin(); it_list!=list->end(); it_list++)
			{
				//
				// SE EXISTIR O TOKEN
				//
				if((*it_list)->token!=NULL)
				{
					//
					// PEGA O COMPORTAMENTO 1 E MUDA UM DOS ATRIBUTOS BOOL DELE
					//
					(*it_list)->token->getBehavior(0)->setBool("flag_cor",true);
				}
			}
		}
		if(input->mouseState.rightButtonDown)
		{
			//
			// FAZ UMA LEITURA DE TODOS OS TILES
			//
			std::list<IrrTile*> * list = tile->parentNode->getAllTiles();
			std::list<IrrTile*>::iterator it_list;
			for(it_list=list->begin(); it_list!=list->end(); it_list++)
			{
				//
				// SE EXISTIR O TOKEN
				//
				if((*it_list)->token!=NULL)
				{
					//
					// PEGA O COMPORTAMENTO 1 E MUDA UM DOS ATRIBUTOS BOOL DELE
					//
					(*it_list)->token->getBehavior(0)->setBool("flag_cor",false);
				}
			}
		}
		tile->node->setMaterialFlag(irr::video::EMF_WIREFRAME,true);
	}
	else
	{
		tile->node->setMaterialFlag(irr::video::EMF_WIREFRAME,false);
	}
}


void TileComum::setInt(char const * key, int value)
{
	if (key == "pontos")
	{
		pontos = value;
	}
	else if (key == "energia")
	{
		energia = value;
	}
}

int TileComum::getInt(char const * key)
{
	if (key == "pontos")
	{
		return pontos;
	}
	else if (key == "energia")
	{
		return energia;
	}
}

void TileComum::setBool(char const * key, bool value)
{
	if (key == "flag_cor")
	{
		flag_cor = value;
	}
	else if (key == "flag_estado")
	{
		flag_estado = value;
	}
}

bool TileComum::getBool(char const * key)
{
	if (key == "flag_cor")
	{
		return flag_cor;
	}
	else if (key == "flag_estado")
	{
		return flag_estado;
	}
}