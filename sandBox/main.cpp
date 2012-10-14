#include <string>
#include <iostream>

#include "IrrEngine.h"
#include "TokenNoob.h"
#include "TokenDummy.h"

using namespace IrrBoardGameEngine;

int main() {
	IrrEngine *engine = IrrEngine::getInstance();
    
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
	
	TokenNoob * tokenNoob = new TokenNoob();
	TokenDummy * tokenDummy = new TokenDummy();

	board->startTokens(1,tokenNoob);
	board->startTokens(2,tokenDummy);
	
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
	delete tokenNoob;
	delete tokenDummy;

	return 0;
}