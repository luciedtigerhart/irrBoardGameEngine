#include "IrrBoard.h"
#include "IrrEngine.h"

using namespace IrrBoardGameEngine;

IrrBoard::IrrBoard(void)
{
	//
	// Inicializa a lista de objs, lista que é preenchida pelo IrrLoader
	// 
	objs = new vector<std::string>();
}

IrrBoard::~IrrBoard(void)
{
	//
	// Apaga da memoria
	//
	delete objs;
	for(int i = 0; i < tile_i; i++)
	{
		for(int j = 0; j < tile_j; j++)
		{	
			delete board[i][j];
		}
	}
	node->remove();
}

void IrrBoard::addTileBehavior(IrrTile * tile, IrrTileBehavior * behavior)
{
	//
	// Adiciona um comportamento para o 'Tile'
	//
	tile->addBehaviour(behavior);

	//
	// configura o pai do 'tile'
	//
	tile->parentNode = this;

	//
	// Configura no comportamento as instancias do motor
	//
	behavior->driver = IrrEngine::getInstance()->getDriver();
	behavior->smgr = IrrEngine::getInstance()->getSceneManager();
	behavior->soundEngine = IrrEngine::getInstance()->getSoundEngine();
	behavior->input = IrrEngine::getInstance()->getInput();

	//
	// Configura no comportamento o 'tile'
	//
	behavior->setTile(tile);

	//
	// Inicia o comportamento
	//
	behavior->init();
}

//
// Configura um comportamento para um 'tile' do tabuleiro
//
void IrrBoard::addTileBehavior(int i, int j, IrrTileBehavior * behavior)
{
	addTileBehavior(board[i][j],behavior);
}

//
// Devolve uma lista de 'tiles' especificado pela informação de 'inf'
//
std::list<IrrTile*> *IrrBoard::getTiles(int inf)
{
	std::list<IrrTile*> * list = new std::list<IrrTile*>();
	for(int i = 0; i < tile_i; i++)
	{
		for(int j = 0; j < tile_j; j++)
		{
			if(board[i][j]->inf == inf)
			{
				list->push_back(board[i][j]);
			}
		}
	}
	return list;
}

//
// Devolve uma lista de todos os 'tiles'
//
std::list<IrrTile*> *IrrBoard::getAllTiles()
{
	std::list<IrrTile*> * list = new std::list<IrrTile*>();
	for(int i = 0; i < tile_i; i++)
	{
		for(int j = 0; j < tile_j; j++)
		{
			list->push_back(board[i][j]);
		}
	}
	return list;
}

//
// Cria vários 'tokens', deacordo com a leitura do arquivo
// onde houver o a informação 'start'
//
std::list<IrrToken*> *IrrBoard::createTokens(int start)
{
	std::list<IrrToken*> *list = new std::list<IrrToken*>();
	for(int i = 0; i < tile_i; i++)
	{
		for(int j = 0; j < tile_j; j++)
		{
			if(board[i][j]->start == start)
			{
				board[i][j]->token = new IrrToken();
				board[i][j]->token->parentNode = board[i][j];
				list->push_back(board[i][j]->token);
			}
		}
	}
	return list;
}

//
// Cria um 'token' especifico numa posição do tabuleiro
// e também é possivel passar um comportamento para esse 'token'
//
bool IrrBoard::createToken(int i, int j, IrrTokenBehavior * behavior)
{
	if(board[i][j]->token == NULL)
	{
		board[i][j]->token = new IrrToken();
		board[i][j]->token->parentNode = board[i][j];

		addTokenBehavior(board[i][j]->token, behavior);
	}
	else
	{
		return false;
	}
}

//
// Aciciona um comportamento para um 'token' já existente
//
void IrrBoard::addTokenBehavior(IrrToken *token, IrrTokenBehavior * behavior)
{
	behavior->setToken(token);

	behavior->driver = IrrEngine::getInstance()->getDriver();
	behavior->smgr = IrrEngine::getInstance()->getSceneManager();
	behavior->soundEngine = IrrEngine::getInstance()->getSoundEngine();
	behavior->input = IrrEngine::getInstance()->getInput();	
	behavior->init();

	token->addBehaviour(behavior);
}

//
// Devolve um 'token' da posição especificada
//
IrrToken *IrrBoard::getToken(int i, int j)
{
	return board[i][j]->token;
}

//
// Adiciona um token existente na posição especificada
//
bool IrrBoard::addToken(int i, int j, IrrToken * token)
{
	if(board[i][j]->token == NULL)
	{
		if(token->node != NULL)
		{
			board[i][j]->node->addChild(token->node);
			token->node->setParent(board[i][j]->node);
		}
		board[i][j]->token = token;
		token->parentNode = board[i][j];
		return true;
	}
	else
	{
		return false;
	}
}

//
// Move o token de (oi, oj) para (ti, tj)
//
bool IrrBoard::moveToken(int oi, int oj, int ti, int tj)
{
	IrrToken * token = getToken(oi, oj);
	if(token != NULL)
	{
		if(addToken(ti,tj, token))
		{
			board[oi][oj]->token = NULL;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

//
// Apaga um token
//
bool IrrBoard::deleteToken(int j, int i)
{
	IrrToken * token = getToken(i, j);
	if(token != NULL)
	{
		token->node->getParent()->removeChild(token->node);
		board[i][j]->token = NULL;
		delete token;
	}
}

//
// Muda o estado 'highlight' de um 'token' de um determinado jogador,
// passando o tipo definido pelo o jogo
//
void IrrBoard::changeHighlightToken(int type, int player)
{
	for(int i = 0; i < tile_i; i++)
	{
		for(int j = 0; j < tile_j; j++)
		{
			if(board[i][j]->token != NULL && board[i][j]->token->player == player) board[i][j]->token->highlight = type;
		}
	}
}

//
// Muda o estado 'highlight' do 'tile', de acordo com a 'inf' do tile
//
void IrrBoard::changeHighlightTile(int type, int inf)
{
	for(int i = 0; i < tile_i; i++)
	{
		for(int j = 0; j < tile_j; j++)
		{
			if(board[i][j]->inf == inf) board[i][j]->highlight = type;
		}
	}
}

//
// Usado para o evento do mouse, quando o mouse passar por um 'tile' ou 'token'
// ele fica com o estado isMouseHover / true ou false
//
void IrrBoard::setHighlight(ISceneNode *node)
{	
	for(int i = 0; i < tile_i; i++)
	{
		for(int j = 0; j < tile_j; j++)
		{
			if(board[i][j]->node == node)
			{
				board[i][j]->isMouseHover = true;				
			}
			else
			{
				board[i][j]->isMouseHover = false;
				if(board[i][j]->token != NULL)
				{
					if(board[i][j]->token->node == node)
					{
						board[i][j]->token->isMouseHover = true;
					}
					else
					{
						board[i][j]->token->isMouseHover = false;
					}
				}
			}
		}
	}
}

void IrrBoard::update()
{
	__super::update();
	for(int i = 0; i < tile_i; i++)
	{
		for(int j = 0; j < tile_j; j++)
		{	
			board[i][j]->update();
		}
	}
}