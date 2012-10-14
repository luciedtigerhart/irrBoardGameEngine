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

void IrrBoard::addTileBehavior(int i, int j, IrrTileBehavior * behavior)
{
	board[i][j]->addBehaviour(behavior);

	behavior->driver = IrrEngine::getInstance()->getDriver();
	behavior->smgr = IrrEngine::getInstance()->getSceneManager();
	behavior->soundEngine = IrrEngine::getInstance()->getSoundEngine();
	behavior->input = IrrEngine::getInstance()->getInput();
	behavior->setTile(board[i][j]);
	behavior->init();
}

void IrrBoard::startTokens(int idx, IrrTokenBehavior * behavior)
{
	for(int j = 0; j < tile_j; j++)
	{
		for(int i = 0; i < tile_j; i++)
		{
			if(board[i][j]->start == idx)
			{
				createToken(i,j,behavior);
			}
		}
	}
}

bool IrrBoard::createToken(int i, int j, IrrTokenBehavior * behavior)
{
	if(board[i][j]->token == NULL)
	{
		board[i][j]->token = new IrrToken();
		board[i][j]->token->parentNode = board[i][j]->node;

		behavior->setToken(board[i][j]->token);
		behavior->driver = IrrEngine::getInstance()->getDriver();
		behavior->smgr = IrrEngine::getInstance()->getSceneManager();
		behavior->soundEngine = IrrEngine::getInstance()->getSoundEngine();
		behavior->input = IrrEngine::getInstance()->getInput();	
		behavior->init();

		board[i][j]->token->addBehaviour(behavior);
	}
	else
	{
		return false;
	}
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