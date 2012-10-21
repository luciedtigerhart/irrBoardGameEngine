#include "PrimeGameStateManager.h"

PrimeGameStateManager::PrimeGameStateManager()
{
	//Initialize engine
	engine = IrrEngine::getInstance(video::EDT_OPENGL, dimension2d<u32>(800,600), 16, false, false, false,L"Primevalion");

	//Initialize GUI environments
	//guimgr.env_title = engine->createGUI();
	//guimgr.env_credits = engine->createGUI();
	//guimgr.env_tutorial = engine->createGUI();
	guimgr.env_match = engine->createGUI();

	//Build GUI environments
	//guimgr.BuildGUITitleScreen();
	//guimgr.BuildGUICreditsScreen();
	//guimgr.BuildGUITutorialScreen();
	guimgr.BuildGUIMatchScreen();

	//Initialize scenes
	//title = engine->createScene();
	//credits = engine->createScene();
	//tutorial = engine->createScene();
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

		turn = 1;

	//----------------------------------------------
};

PrimeGameStateManager::~PrimeGameStateManager()
{
	//Bye bye engine and GUI environment!
	delete engine;
	
	//Bye bye scenes!
	delete title;
	delete credits;
	delete tutorial;
	delete match;
	
	//Bye bye board and camera!
	delete board;
	delete camera;
};

void PrimeGameStateManager::loop()
{
	//----- FOR TESTING PURPOSES, DELETE LATER -----

		engine->setCurrentScene(match);
		engine->setCurrentGUI(guimgr.env_match);

		camera = match->addCamera(new Vector(15.0f, 15.0f, 15.0f),new Vector(0.0f, 0.0f, 0.0f));
		camera->setName("Match Camera");

		board = match->addBoard("boards/board-01.txt",new Vector(0.0f, 0.0f, 0.0f));

		light = match->smgr->addLightSceneNode(0, vector3df(20,5,0), SColorf(1.0f,1.0f,1.0f,1.0f), 30.0f);

		//Tiles...
		std::list<IrrTile*> * tileList = board->getAllTiles();
		std::list<IrrTile*>::iterator i;

		for(i = tileList->begin(); i != tileList->end(); i++)
		{
			board->addTileBehavior((*i), new PrimeTile());
		}

		//Tokens...
		std::list<IrrToken*>::iterator t;

		//Player 1 tokens...
		std::list<IrrToken*> * tokensTeam1 = board->createTokens(1);
		for(t = tokensTeam1->begin(); t != tokensTeam1->end(); t++)
		{
			board->addTokenBehavior((*t), new PrimeToken(player1));
		}

		//Player 2 tokens...
		std::list<IrrToken*> * tokensTeam2 = board->createTokens(2);
		for(t = tokensTeam2->begin(); t != tokensTeam2->end(); t++)
		{
			board->addTokenBehavior((*t), new PrimeToken(player2));
		}

		//Player 3 tokens...
		std::list<IrrToken*> * tokensTeam3 = board->createTokens(3);
		for(t = tokensTeam3->begin(); t != tokensTeam3->end(); t++)
		{
			board->addTokenBehavior((*t), new PrimeToken(player3));
		}

		//Player 4 tokens...
		std::list<IrrToken*> * tokensTeam4 = board->createTokens(4);
		for(t = tokensTeam4->begin(); t != tokensTeam4->end(); t++)
		{
			board->addTokenBehavior((*t), new PrimeToken(player4));
		}

		playersActive = 4;

		//Find which player the current turn belongs to
		playState.SetTurnPlayer(turn, playersActive, player1, player2, player3, player4);

		//Update match interface
		guimgr.ManageGUIMatchScreen(turn, playState, player1, player2, player3, player4);

		
		playState.SetupTileHighlight(board, player1);

	//----------------------------------------------

	//Run game
	engine->loop();
}