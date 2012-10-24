#include "IrrBoard.h"
#include "IrrEngine.h"

using namespace IrrBoardGameEngine;

IrrBoard::IrrBoard(void)
{
	objs = new vector<std::string>();
}

IrrBoard::~IrrBoard(void)
{
	delete objs;

	for(int j = 0; j < tile_j; j++)
	{
		for(int i = 0; i < tile_j; i++)
		{
			delete board[i][j];
		}
	}
}

void IrrBoard::addTileBehavior(IrrTile * tile, IrrTileBehavior * behavior)
{
	tile->addBehaviour(behavior);
	tile->parentNode = this;

	behavior->driver = IrrEngine::getInstance()->getDriver();
	behavior->smgr = IrrEngine::getInstance()->getSceneManager();
	behavior->soundEngine = IrrEngine::getInstance()->getSoundEngine();
	behavior->input = IrrEngine::getInstance()->getInput();
	behavior->setTile(tile);
	behavior->init();
}

void IrrBoard::addTileBehavior(int i, int j, IrrTileBehavior * behavior)
{
	addTileBehavior(board[i][j],behavior);
}

/*
void IrrBoard::startTileBehavior(int inf, IrrTileBehavior * behavior)
{
	for(int j = 0; j < tile_j; j++)
	{
		for(int i = 0; i < tile_j; i++)
		{
			if(board[i][j]->inf == inf)
			{
				addTileBehavior(i,j,behavior);
			}
		}
	}
}
*/
std::list<IrrTile*> *IrrBoard::getTiles(int inf)
{
	std::list<IrrTile*> * list = new std::list<IrrTile*>();
	for(int j = 0; j < tile_j; j++)
	{
		for(int i = 0; i < tile_j; i++)
		{
			if(board[i][j]->inf == inf)
			{
				list->push_back(board[i][j]);
			}
		}
	}
	return list;
}

std::list<IrrTile*> *IrrBoard::getAllTiles()
{
	std::list<IrrTile*> * list = new std::list<IrrTile*>();
	for(int j = 0; j < tile_j; j++)
	{
		for(int i = 0; i < tile_j; i++)
		{
			list->push_back(board[i][j]);
		}
	}
	return list;
}

std::list<IrrToken*> *IrrBoard::createTokens(int start)
{
	std::list<IrrToken*> *list = new std::list<IrrToken*>();
	for(int j = 0; j < tile_j; j++)
	{
		for(int i = 0; i < tile_j; i++)
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

IrrToken *IrrBoard::getToken(int i, int j)
{
	return board[i][j]->token;
}

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
		return true;
	}
	else
	{
		return false;
	}
}

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

bool IrrBoard::deleteToken(int i, int j)
{
	IrrToken * token = getToken(i, j);
	if(token != NULL)
	{
		token->node->getParent()->removeChild(token->node);
		board[i][j]->token = NULL;
		delete token;
	}
}

void IrrBoard::changeHighlightToken(int type, int player)
{
	for(int j = 0; j < tile_j; j++)
	{
		for(int i = 0; i < tile_j; i++)
		{
			if(board[i][j]->token != NULL && board[i][j]->token->player == player) board[i][j]->token->highlight = type;
		}
	}
}

void IrrBoard::changeHighlightTile(int type, int inf)
{
	for(int j = 0; j < tile_j; j++)
	{
		for(int i = 0; i < tile_j; i++)
		{
			if(board[i][j]->inf == inf) board[i][j]->highlight = type;
		}
	}
}

void IrrBoard::setHighlight(ISceneNode *node)
{
	//FAZ A MAGICA
	for(int j = 0; j < tile_j; j++)
	{
		for(int i = 0; i < tile_j; i++)
		{
			if(board[i][j]->node == node)
			{
				board[i][j]->isMouseHover = true;
				//std::cout << "isHighlighted";
			}
			else
			{
				board[i][j]->isMouseHover = false;
				if(board[i][j]->token != NULL)
				{
					if(board[i][j]->token->node == node)
					{
						board[i][j]->token->isMouseHover = true;
						//std::cout << "isHighlighted";
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
	for(int j = 0; j < tile_j; j++)
	{
		for(int i = 0; i < tile_j; i++)
		{
			board[i][j]->update();
		}
	}
}