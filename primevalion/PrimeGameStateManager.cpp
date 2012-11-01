#include "PrimeGameStateManager.h"

#define FULLSCREEN true
#define WINDOWED false

//Random generator function:
ptrdiff_t myrandom (ptrdiff_t i) { return rand() % i; }

//Pointer object to it:
ptrdiff_t (*p_myrandom)(ptrdiff_t) = myrandom;

PrimeGameStateManager::PrimeGameStateManager()
{
	//Specify game goal, in resources
	gameGoal = 400;

	//Initialize random seed
	srand ( unsigned (time(NULL)) );

	//Initialize engine
	engine = IrrEngine::getInstance(video::EDT_OPENGL, dimension2d<u32>(1024,768), 16, WINDOWED, false, false,L"Primevalion");

	//Initialize GUI environments
	guimgr.env_title = engine->createGUI();
	guimgr.env_credits = engine->createGUI();
	guimgr.env_tutorial = engine->createGUI();
	guimgr.env_match = engine->createGUI();

	//Build GUI environments
	guimgr.BuildGUITitleScreen();
	guimgr.BuildGUICreditsScreen();
	guimgr.BuildGUITutorialScreen();
	guimgr.BuildGUIMatchScreen();

	//Initialize scenes
	title = engine->createScene();
	credits = engine->createScene();
	tutorial = engine->createScene();
	match = engine->createScene();
	
	//Initialize board
	board = NULL;

	//Initialize players
	
	playersActive = 0;

	player1.idx = 1;
	player2.idx = 2;
	player3.idx = 3;
	player4.idx = 4;

	player1.isAI = player2.isAI = player3.isAI = player4.isAI = false;
	player1.isActive = player2.isActive = player3.isActive = player4.isActive = true;
	player1.assignedRace = player2.assignedRace = player3.assignedRace = player4.assignedRace = KOBOLD;

	ResetPlayers();

	//Specify initial scene and GUI (Title Screen)
	engine->setCurrentScene(title);
	engine->setCurrentGUI(guimgr.env_title);
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

void PrimeGameStateManager::SetupMatch()
{
	//Reset game flow data
	turn = 1;
	tokensActive = 0;
	playersActive = 0;

	//Change scene and GUI
	engine->setCurrentScene(match);
	engine->setCurrentGUI(guimgr.env_match);

	//Configure camera
	//camera = match->addCamera(new Vector(0.0f, 25.0f, 0.0f), new Vector(0.0f, 0.0f, 1.0f));
	camera = match->addCamera(new Vector(0.0f, 20.0f, -10.0f), new Vector(0.0f, 0.0f, 1.0f));
	camera->setName("Match Camera");

	//Initialize game elements
	CreateBoard();

	//Initialize play state
	playState.Initialize(engine, playersActive, tokensActive, gameGoal,
						 player1, player2, player3, player4,
						 tokensTeam1, tokensTeam2, tokensTeam3, tokensTeam4);
}

void PrimeGameStateManager::ResetPlayers()
{
	player1.isVictorious = player2.isVictorious = player3.isVictorious = player4.isVictorious = false;
	player1.assignedTurn = player2.assignedTurn = player3.assignedTurn = player4.assignedTurn = -1;
	player1.primevalium = player2.primevalium = player3.primevalium = player4.primevalium = 0;
}

void PrimeGameStateManager::CreateBoard()
{
	//Deactivate old board
	if (board != NULL)
	{
		board->node->grab();
		board->node->remove();
	}

	//Add new board to scene
	board = match->addBoard("boards/board-01.txt",new Vector(0.0f, 1.0f, 0.0f));

	//Create light
	light = engine->getSceneManager()->addLightSceneNode(board->node, vector3df(0,5,-20), SColorf(1.0f,1.0f,1.0f,1.0f), 30.0f);

	//Initialize game elements (tiles always BEFORE tokens)
	LoadTiles();
	LoadTokens();
}

void PrimeGameStateManager::LoadTiles()
{
	//Get list of board tiles
	std::list<IrrTile*> * tileList = board->getAllTiles();

	//Add "PrimeTile" behavior to all board tiles
	std::list<IrrTile*>::iterator i;
	for(i = tileList->begin(); i != tileList->end(); i++)
	{
		board->addTileBehavior((*i), new PrimeTile(player1, player2, player3, player4));
	}
}

void PrimeGameStateManager::LoadTokens()
{
	tokensActive = 0;
	std::list<IrrToken*>::iterator t;

	//Re-initialize players
	ResetPlayers();

	//Sort turns
	SortTurnOrder();

	//Add "PrimeToken" behavior to all tokens,
	//according to match configuration

	//Player 1 tokens...
	if (player1.isActive)
	{
		tokensTeam1 = board->createTokens(player1.idx);

		for(t = tokensTeam1->begin(); t != tokensTeam1->end(); t++)
		{
			board->addTokenBehavior((*t), new PrimeToken(player1));
			
			//Count active tokens
			tokensActive++;
		}
	}

	//Player 2 tokens...
	if (player2.isActive)
	{
		tokensTeam2 = board->createTokens(player2.idx);
		for(t = tokensTeam2->begin(); t != tokensTeam2->end(); t++)
		{
			board->addTokenBehavior((*t), new PrimeToken(player2));

			//Count active tokens
			if (!player1.isActive) tokensActive++;
		}
	}

	//Player 3 tokens...
	if (player3.isActive)
	{
		tokensTeam3 = board->createTokens(player3.idx);
		for(t = tokensTeam3->begin(); t != tokensTeam3->end(); t++)
		{
			board->addTokenBehavior((*t), new PrimeToken(player3));

			//Count active tokens
			if (!player1.isActive && !player2.isActive)
				tokensActive++;
		}
	}

	//Player 4 tokens...
	if (player4.isActive)
	{
		tokensTeam4 = board->createTokens(player4.idx);
		for(t = tokensTeam4->begin(); t != tokensTeam4->end(); t++)
		{
			board->addTokenBehavior((*t), new PrimeToken(player4));

			//Count active tokens
			if (!player1.isActive && !player2.isActive && !player3.isActive)
				tokensActive++;
		}
	}
}

void PrimeGameStateManager::SortTurnOrder()
{
	vector<int> turnOrder;
	vector<int>::iterator itOrder;

	//Count active players
	if (player1.isActive) playersActive++;
	if (player2.isActive) playersActive++;
	if (player3.isActive) playersActive++;
	if (player4.isActive) playersActive++;

	//Add values to turn order:
	for (int i = 1; i <= playersActive; ++i) turnOrder.push_back(i);

	//Shuffle turn order
	random_shuffle(turnOrder.begin(), turnOrder.end(), p_myrandom);

	//Assign turns to active players
	for (itOrder = turnOrder.begin(); itOrder != turnOrder.end(); itOrder++)
	{
		if (player1.isActive && player1.assignedTurn == -1) player1.assignedTurn = (*itOrder);
		else if (player2.isActive && player2.assignedTurn == -1) player2.assignedTurn = (*itOrder);
		else if (player3.isActive && player3.assignedTurn == -1) player3.assignedTurn = (*itOrder);
		else if (player4.isActive && player4.assignedTurn == -1) player4.assignedTurn = (*itOrder);
	}
}

void PrimeGameStateManager::ManageTitleScreen()
{
	int transition = 0;

	//Update title screen and return a possible screen transition
	transition = guimgr.ManageGUITitleScreen(&player1, &player2, &player3, &player4);

	//Transfer to Match screen
	if (transition == MATCH_TRANSITION)
	{
		//Initialize match
		SetupMatch();
	}

	//Transfer to Tutorial screen
	else if (transition == TUTORIAL_TRANSITION)
	{
		//Initialize Tutorial
		guimgr.SetTutorialPage(1);
		
		//Change scene and GUI
		engine->setCurrentScene(tutorial);
		engine->setCurrentGUI(guimgr.env_tutorial);
	}

	//Transfer to Credits screen
	else if (transition == CREDITS_TRANSITION)
	{
		//Change scene and GUI
		engine->setCurrentScene(credits);
		engine->setCurrentGUI(guimgr.env_credits);
	}
}

void PrimeGameStateManager::ManageTutorialScreen()
{
	//Manage tutorial screen and return to title when
	//"Back to Title" button is pressed.

	if (guimgr.ManageGUITutorialScreen())
	{
		//Change scene and GUI
		engine->setCurrentScene(title);
		engine->setCurrentGUI(guimgr.env_title);
	}
}

void PrimeGameStateManager::ManageCreditsScreen()
{
	//Manage credits screen and return to title when
	//"Back to Title" button is pressed.

	if (guimgr.ManageGUICreditsScreen())
	{
		//Change scene and GUI
		engine->setCurrentScene(title);
		engine->setCurrentGUI(guimgr.env_title);
	}
}

void PrimeGameStateManager::ManageMatch()
{
	//While play state hasn't signaled match termination...
	if (!playState.signalBackToTitle)
	{
		//Update play state
		playState.Update(board, turn);

		//Update match interface
		//!! Must come AFTER play state updates, otherwise game breaks !!
		guimgr.ManageGUIMatchScreen(turn, &playState);

		//When a turn is over, go to the next one
		if (playState.turnOver) turn++;
	}

	//If play state signaled match has ended, head back to title screen
	else if (playState.signalBackToTitle)
	{
		//Change scene and GUI
		engine->setCurrentScene(title);
		engine->setCurrentGUI(guimgr.env_title);
	}
}

void PrimeGameStateManager::Update()
{
	//Manage game states/scenes
	IrrScene* currentScene = engine->getScene();

	if (currentScene == title) ManageTitleScreen();
	else if (currentScene == tutorial) ManageTutorialScreen();
	else if (currentScene == credits) ManageCreditsScreen();
	else if (currentScene == match) ManageMatch();
}

void PrimeGameStateManager::loop()
{
	//Run game!
	while(engine->getDevice()->run())
	{
		//Update engine
		engine->getScene()->update();
		engine->getGUI()->update();
		engine->getInput()->update();

		//Update game state
		Update();

		//Begin frame...
		engine->getDriver()->beginScene(true, true, SColor(255,100,101,140));

			//Draw stuff!
			engine->getSceneManager()->drawAll();
			engine->getGUIenv()->drawAll();

		//...End frame.
		engine->getDriver()->endScene();
	}

	//Close game!
	engine->getDevice()->drop();
}