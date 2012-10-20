#include "PrimeGameStateManager.h"

PrimeGameStateManager::PrimeGameStateManager()
{
	//Initializes engine
	engine = IrrEngine::getInstance();

	//Initialize GUI environments
	guienv_title = engine->createGUI();
	guienv_credits = engine->createGUI();
	guienv_tutorial = engine->createGUI();
	guienv_match = engine->createGUI();

	//Initialize scenes
	title = engine->createScene();
	credits = engine->createScene();
	tutorial = engine->createScene();
	match = engine->createScene();

	//Initialize players

	player1.idx = 1;
	player2.idx = 2;
	player3.idx = 3;
	player4.idx = 4;

	player1.isActive = player2.isActive = player3.isActive = player4.isActive = true;
	player1.isAI = player2.isAI = player3.isAI = player4.isAI = false;
	//player1.assignedTurn = player2.assignedTurn = player3.assignedTurn = player4.assignedTurn = -1;
	//player1.assignedRace = player2.assignedRace = player3.assignedRace = player4.assignedRace = KOBOLD;
	player1.primevalium = player2.primevalium = player3.primevalium = player4.primevalium = 0;

	//----- FOR TESTING PURPOSES, DELETE LATER -----

		player1.assignedRace = KOBOLD;
		player2.assignedRace = GNOLL;
		player3.assignedRace = TROLL;
		player4.assignedRace = HOG;

		player1.assignedTurn = 1;
		player2.assignedTurn = 2;
		player3.assignedTurn = 3;
		player4.assignedTurn = 4;

		guienv_match->addButton("IMAGEM","gui/botao-off.png","gui/botao-on.png",30,60,228,117);

		engine->setCurrentScene(match);
		engine->setCurrentGUI(guienv_match);

		camera = match->addCamera(new Vector(15.0f, 15.0f, 15.0f),new Vector(0.0f, 0.0f, 0.0f));
		camera->setName("Camera principal");

		board = match->addBoard("boards/board-01.txt",new Vector(0.0f, 0.0f, 0.0f));

		tokenTeam1 = new PrimeToken(player1);
		tokenTeam2 = new PrimeToken(player2);
		tokenTeam3 = new PrimeToken(player3);
		tokenTeam4 = new PrimeToken(player4);

		board->startTokens(player1.idx, tokenTeam1);
		board->startTokens(player2.idx, tokenTeam2);
		board->startTokens(player3.idx, tokenTeam3);
		board->startTokens(player4.idx, tokenTeam4);

	//----------------------------------------------
};

PrimeGameStateManager::~PrimeGameStateManager()
{
	//Bye bye engine!
	delete engine;

	//Bye bye GUI environments!
	delete guienv_title;
	delete guienv_credits;
	delete guienv_tutorial;
	delete guienv_match;
	
	//Bye bye scenes!
	delete title;
	delete credits;
	delete tutorial;
	delete match;
	
	//Bye bye board and camera!
	delete board;
	delete camera;

	delete tokenTeam1;
	delete tokenTeam2;
	delete tokenTeam3;
	delete tokenTeam4;
};

void PrimeGameStateManager::loop()
{
	//Run game
	engine->loop();
}