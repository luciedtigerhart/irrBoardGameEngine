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
    
	IrrScene *scene = engine->getScene();

	IrrGameObject *cam = scene->addCamera(new Vector(0.0f, 20.0f, 0.0f),new Vector(0.0f, 0.0f, 0.0f));
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
	IrrScene *scene_dois = engine->createScene();

	scene_dois->addCube(new Vector(0.0f, 0.0f, 0.0f));

	IrrGameObject *cam_dois = scene->addCamera(new Vector(2.0f, 20.0f, 20.0f),new Vector(0.0f, 0.0f, 0.0f));

	engine->setCurrentScene(scene_dois);
	*/

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

	//
	// CONSTRUÇÃO DO GUI
	//
	IrrGUI * gui = engine->getGUI();

	gui->addLabel("teste","meu texto meu texto meu texto meu texto meu texto",0,0,50,80);

	
	IrrGUI * gui_dois = engine->createGUI();

	gui_dois->addLabel("mostro","mostro texto meu mostro meu mostro meu mostro meu mostro",0,0,50,80);

	engine->setCurrentGUI(gui_dois);
	


	engine->loop();

	delete scene;
	delete engine;
	delete gui;
	delete cam;
	delete board;

	return 0;
}