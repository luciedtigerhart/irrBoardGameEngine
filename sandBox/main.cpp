#include <string>
#include <iostream>
#include <list>
#include <list>

#include "IrrEngine.h"
#include "TokenNoob.h"
#include "TokenDummy.h"
#include "TileComum.h"

using namespace IrrBoardGameEngine;

int main()
{
	IrrEngine *engine = IrrEngine::getInstance(video::EDT_SOFTWARE, dimension2d<u32>(800, 600), 16, false, false, false,L"Jogo Dummy");
    
	IrrScene *scene = engine->createScene();

	IrrGUI *gui = engine->createGUI();

	//gui->addLabel("TESTE","AVISO DE TEXTO",0,0,60,20);
	//gui->addImage("IMAGEM","gui/botao-off.png",10,60);

	gui->addButton("IMAGEM","gui/botao-off.png","gui/botao-on.png",30,60,228,117);

	engine->setCurrentScene(scene);
	engine->setCurrentGUI(gui);

	IrrGameObject *cam = scene->addCamera(new Vector(15.0f, 15.0f, 15.0f),new Vector(0.0f, 0.0f, 0.0f));
	cam->setName("Camera principal");
	
	IrrBoard * board = scene->addBoard("boards/board-01.txt",new Vector(0.0f, 0.0f, 0.0f));
	
	//
	// CONFIGURA TILES
	//

	std::list<IrrTile*> * list_tiles = board->getAllTiles();
	std::list<IrrTile*>::iterator i;
	for(i=list_tiles->begin(); i!=list_tiles->end(); i++)
	{
		board->addTileBehavior((*i), new TileComum());
	}

	//
	// CONFIGURA TOKENS
	//

	std::list<IrrToken*>::iterator t;

	std::list<IrrToken*> * list_token_player_one = board->createTokens(1);
	for(t=list_token_player_one->begin(); t!=list_token_player_one->end(); t++)
	{
		board->addTokenBehavior((*t), new TokenNoob());
	}

	std::list<IrrToken*> * list_token_player_two = board->createTokens(2);
	for(t=list_token_player_two->begin(); t!=list_token_player_two->end(); t++)
	{
		board->addTokenBehavior((*t), new TokenDummy());
	}

	/*
	if(board->moveToken(0,3,5,2))
	{
		cout << "aa";
	}
	else
	{
		cout << "nao";
	}
	*/

	engine->loop();

	delete scene;
	delete engine;
	delete gui;
	delete cam;
	delete board;

	return 0;
}