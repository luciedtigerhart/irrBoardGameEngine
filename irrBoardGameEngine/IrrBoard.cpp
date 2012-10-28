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
		for(int i = 0; i < tile_i; i++)
		{
			delete board[j][i];
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

void IrrBoard::addTileBehavior(int j, int i, IrrTileBehavior * behavior)
{
	addTileBehavior(board[j][i],behavior);
}

std::list<IrrTile*> *IrrBoard::getTiles(int inf)
{
	std::list<IrrTile*> * list = new std::list<IrrTile*>();
	for(int j = 0; j < tile_j; j++)
	{
		for(int i = 0; i < tile_i; i++)
		{
			if(board[j][i]->inf == inf)
			{
				list->push_back(board[j][i]);
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
		for(int i = 0; i < tile_i; i++)
		{
			list->push_back(board[j][i]);
		}
	}
	return list;
}

std::list<IrrToken*> *IrrBoard::createTokens(int start)
{
	std::list<IrrToken*> *list = new std::list<IrrToken*>();
	for(int j = 0; j < tile_j; j++)
	{
		for(int i = 0; i < tile_i; i++)
		{
			if(board[j][i]->start == start)
			{
				board[j][i]->token = new IrrToken();
				board[j][i]->token->parentNode = board[j][i];
				list->push_back(board[j][i]->token);
			}
		}
	}
	return list;
}

bool IrrBoard::createToken(int j, int i, IrrTokenBehavior * behavior)
{
	if(board[j][i]->token == NULL)
	{
		board[j][i]->token = new IrrToken();
		board[j][i]->token->parentNode = board[j][i];

		addTokenBehavior(board[j][i]->token, behavior);
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

IrrToken *IrrBoard::getToken(int j, int i)
{
	return board[j][i]->token;
}

bool IrrBoard::addToken(int j, int i, IrrToken * token)
{
	if(board[j][i]->token == NULL)
	{
		if(token->node != NULL)
		{
			board[j][i]->node->addChild(token->node);
			token->node->setParent(board[j][i]->node);
		}
		board[j][i]->token = token;
		return true;
	}
	else
	{
		return false;
	}
}

bool IrrBoard::moveToken(int oj, int oi, int tj, int ti)
{
	IrrToken * token = getToken(oj, oi);
	if(token != NULL)
	{
		if(addToken(tj,ti, token))
		{
			board[oj][oi]->token = NULL;
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

bool IrrBoard::deleteToken(int j, int i)
{
	IrrToken * token = getToken(j, i);
	if(token != NULL)
	{
		token->node->getParent()->removeChild(token->node);
		board[j][i]->token = NULL;
		delete token;
	}
}

void IrrBoard::changeHighlightToken(int type, int player)
{
	for(int j = 0; j < tile_j; j++)
	{
		for(int i = 0; i < tile_i; i++)
		{
			if(board[j][i]->token != NULL && board[j][i]->token->player == player) board[j][i]->token->highlight = type;
		}
	}
}

void IrrBoard::changeHighlightTile(int type, int inf)
{
	for(int j = 0; j < tile_j; j++)
	{
		for(int i = 0; i < tile_i; i++)
		{
			if(board[j][i]->inf == inf) board[j][i]->highlight = type;
		}
	}
}

void IrrBoard::setHighlight(ISceneNode *node)
{
	//FAZ A MAGICA
	for(int j = 0; j < tile_j; j++)
	{
		for(int i = 0; i < tile_i; i++)
		{
			if(board[j][i]->node == node)
			{
				board[j][i]->isMouseHover = true;
				//std::cout << "isHighlighted";
			}
			else
			{
				board[j][i]->isMouseHover = false;
				if(board[j][i]->token != NULL)
				{
					if(board[j][i]->token->node == node)
					{
						board[j][i]->token->isMouseHover = true;
						//std::cout << "isHighlighted";
					}
					else
					{
						board[j][i]->token->isMouseHover = false;
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
		for(int i = 0; i < tile_i; i++)
		{
			board[j][i]->update();
		}
	}
}