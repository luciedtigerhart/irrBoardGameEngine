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
	gameGoal = 100;

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

	//Initialize GUI transition effects
	guimgr.env_title->fadeOut(0);
	guimgr.env_credits->fadeOut(0);
	guimgr.env_tutorial->fadeOut(0);
	guimgr.env_match->fadeOut(0, SColor(255,255,255,255));

	//Initialize GUI transition variables
	transition = 0;
	fade = FADED_OUT;
	fTimeOutGame = 350;
	fTimeInGame = 1200;

	//Initialize scenes
	title = engine->createScene();
	credits = engine->createScene();
	tutorial = engine->createScene();
	match = engine->createScene();
	
	//Load music and sound effects
	LoadAudio();

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
	
	//Bye bye camera!
	delete camera;

	//Bye bye audio!
	BGM.clear();
	SFX.clear();
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
	camera = match->addCameraDefault(new Vector(0.0f, 20.0f, -10.0f), new Vector(0.0f, 0.0f, 1.0f));
	camera->setName("Match Camera");

	//Add particle systems to scene
	CreateParticles();

	//Initialize game elements
	CreateBoard();

	//Initialize play state
	playState.Initialize(engine, playersActive, tokensActive, gameGoal,
						 bloodParticles, abilityParticles,
						 resourceParticlesNW, resourceParticlesNE,
						 resourceParticlesSW, resourceParticlesSE,
						 player1, player2, player3, player4,
						 tokensTeam1, tokensTeam2, tokensTeam3, tokensTeam4,
						 &BGM, &SFX);
}

void PrimeGameStateManager::ResetPlayers()
{
	player1.isVictorious = player2.isVictorious = player3.isVictorious = player4.isVictorious = false;
	player1.assignedTurn = player2.assignedTurn = player3.assignedTurn = player4.assignedTurn = -1;
	player1.primevalium = player2.primevalium = player3.primevalium = player4.primevalium = 0;
}

void PrimeGameStateManager::CreateParticles()
{
	//Add multiple particle systems to match

	bloodParticles = match->addParticleSystem();
	abilityParticles = match->addParticleSystem();
	resourceParticlesNW = match->addParticleSystem();
	resourceParticlesNE = match->addParticleSystem();
	resourceParticlesSW = match->addParticleSystem();
	resourceParticlesSE = match->addParticleSystem();
}

void PrimeGameStateManager::CreateBoard()
{
	//Add new board to scene
	board = match->addStaticBoard("boards/board-01.txt",new Vector(0.0f, 1.0f, 0.0f));

	//Create light
	light = match->addLightSceneNode(board->node, -1, vector3df(0,5,-20), SColorf(1.0f,1.0f,1.0f,1.0f), 30.0f);

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

void PrimeGameStateManager::LoadAudio()
{
	//Add 3 musics to BGM list and 14 sound effects to SFX list
	for (int i=0; i<3; i++) BGM.push_back(new IrrGameObject);
	for (int i=0; i<14; i++) SFX.push_back(new IrrGameObject);

	//Load music files

	BGM[0] = match->addAudio("sound/bgm/bgm_outgame.ogg", BGM_OUTGAME, new Vector(0,0,0));
	BGM[1] = match->addAudio("sound/bgm/bgm_match.ogg", BGM_MATCH, new Vector(0,0,0));
	BGM[2] = match->addAudio("sound/bgm/bgm_victory.ogg", BGM_VICTORY, new Vector(0,0,0));

	//Load sound effect files

	SFX[0] = match->addAudio("sound/sgx/sfx_iface_button.wav", SFX_BUTTON, new Vector(0,0,0));
	SFX[1] = match->addAudio("sound/sgx/sfx_iface_unitSelect.wav", SFX_TOKEN_SELECT, new Vector(0,0,0));
	SFX[2] = match->addAudio("sound/sgx/sfx_motion_drag.wav", SFX_TOKEN_DRAG, new Vector(0,0,0));
	SFX[3] = match->addAudio("sound/sgx/sfx_motion_positionFit.wav", SFX_TOKEN_FIT, new Vector(0,0,0));

	SFX[4] = match->addAudio("sound/sgx/sfx_gameplay_abilityActivate.wav", SFX_ABILITY, new Vector(0,0,0));
	SFX[5] = match->addAudio("sound/sgx/sfx_gameplay_bonusExtract.wav", SFX_EXTRACTION, new Vector(0,0,0));

	SFX[6] = match->addAudio("sound/sgx/sfx_special_unitDie_attackKobold.wav", SFX_DIE_KOBOLD, new Vector(0,0,0));
	SFX[7] = match->addAudio("sound/sgx/sfx_special_unitDie_attackGnoll.wav", SFX_DIE_GNOLL, new Vector(0,0,0));
	SFX[8] = match->addAudio("sound/sgx/sfx_special_unitDie_attackTroll.wav", SFX_DIE_TROLL, new Vector(0,0,0));
	SFX[9] = match->addAudio("sound/sgx/sfx_special_unitDie_attackHog.wav", SFX_DIE_HOG, new Vector(0,0,0));

	SFX[10] = match->addAudio("sound/sgx/sfx_special_unitDie_trapKobold.wav", SFX_TRAP_KOBOLD, new Vector(0,0,0));
	SFX[11] = match->addAudio("sound/sgx/sfx_special_unitDie_trapGnoll.wav", SFX_TRAP_GNOLL, new Vector(0,0,0));
	SFX[12] = match->addAudio("sound/sgx/sfx_special_unitDie_trapTroll.wav", SFX_TRAP_TROLL, new Vector(0,0,0));
	SFX[13] = match->addAudio("sound/sgx/sfx_special_unitDie_trapHog.wav", SFX_TRAP_HOG, new Vector(0,0,0));
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
	if (fade == FADED_OUT)
	{
		//Fade in screen
		guimgr.env_title->fadeIn(fTimeOutGame);
		fade = FADING_IN;

		//Start playing outgame BGM
		BGM[BGM_OUTGAME]->getAudio()->setLoopingStreamMode();
	}

	//Update title screen and return a possible screen transition
	if (!transition) transition = guimgr.ManageGUITitleScreen(&player1, &player2, &player3, &player4);

	//Transfer to Match screen
	if (transition == MATCH_TRANSITION)
	{
		if (!fade)
		{
			//Fade out screen
			guimgr.env_title->fadeOut(fTimeInGame, SColor(255,255,255,255));
			fade = FADING_OUT;

			//Stop playing outgame BGM
			BGM[BGM_OUTGAME]->getAudio()->stop();
		}

		//When fade is complete...
		if (guimgr.env_title->isReadyfade())
		{
			transition = 0; fade = FADED_OUT;

			//Fade match screen in full white
			guimgr.env_match->fadeOut(0, SColor(255,255,255,255));

			//Initialize match
			SetupMatch();
		}
	}

	//Transfer to Tutorial screen
	else if (transition == TUTORIAL_TRANSITION)
	{
		//Fade out screen
		if (!fade) { guimgr.env_title->fadeOut(fTimeOutGame); fade = FADING_OUT; }

		//When fade is complete...
		if (guimgr.env_title->isReadyfade())
		{
			transition = 0; fade = FADED_OUT;

			//Initialize Tutorial
			guimgr.SetTutorialPage(1);

			//Change scene and GUI
			engine->setCurrentScene(tutorial);
			engine->setCurrentGUI(guimgr.env_tutorial);
		}
	}

	//Transfer to Credits screen
	else if (transition == CREDITS_TRANSITION)
	{
		//Fade out screen
		if (!fade) { guimgr.env_title->fadeOut(fTimeOutGame); fade = FADING_OUT; }

		//When fade is complete...
		if (guimgr.env_title->isReadyfade())
		{
			transition = 0; fade = FADED_OUT;
			
			//Change scene and GUI
			engine->setCurrentScene(credits);
			engine->setCurrentGUI(guimgr.env_credits);
		}
	}
}

void PrimeGameStateManager::ManageTutorialScreen()
{
	//Fade in screen
	if (fade == FADED_OUT) { guimgr.env_tutorial->fadeIn(fTimeOutGame); fade = FADING_IN; }

	//Manage tutorial screen
	if (!transition) transition = guimgr.ManageGUITutorialScreen();

	//Return to title when "Back to Title" button is pressed
	if (transition == TITLE_TRANSITION)
	{
		//Fade out screen
		if (!fade) { guimgr.env_tutorial->fadeOut(fTimeOutGame); fade = FADING_OUT; }

		//When fade is complete...
		if (guimgr.env_tutorial->isReadyfade())
		{
			transition = 0; fade = FADED_OUT;

			//Change scene and GUI
			engine->setCurrentScene(title);
			engine->setCurrentGUI(guimgr.env_title);
		}
	}
}

void PrimeGameStateManager::ManageCreditsScreen()
{
	//Fade in screen
	if (fade == FADED_OUT) { guimgr.env_credits->fadeIn(fTimeOutGame); fade = FADING_IN; }

	//Manage credits screen
	if (!transition) transition = guimgr.ManageGUICreditsScreen();

	//Return to title when "Back to Title" button is pressed
	if (transition == TITLE_TRANSITION)
	{
		//Fade out screen
		if (!fade) { guimgr.env_credits->fadeOut(fTimeOutGame); fade = FADING_OUT; }

		//When fade is complete...
		if (guimgr.env_credits->isReadyfade())
		{
			transition = 0; fade = FADED_OUT;

			//Change scene and GUI
			engine->setCurrentScene(title);
			engine->setCurrentGUI(guimgr.env_title);
		}
	}
}

void PrimeGameStateManager::ManageMatch()
{
	if (fade == FADED_OUT)
	{
		//Fade in match screen (white)
		guimgr.env_match->fadeIn(fTimeInGame, SColor(255,255,255,255));
		fade = FADING_IN;

		//Fade out title screen (full black)
		guimgr.env_title->fadeOut(0, SColor(255,0,0,0));
	}

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
		//Fade out screen
		if (!fade) { guimgr.env_match->fadeOut(fTimeInGame); fade = FADING_OUT; }

		//When fade is complete...
		if (guimgr.env_match->isReadyfade())
		{
			transition = 0; fade = FADED_OUT;

			//Deactivate board
			if (board != NULL)
			{
				match->removeBoard();
				board = NULL;
			}

			//Deactivate particle systems

			if (bloodParticles != NULL) { bloodParticles->node->remove(); bloodParticles = NULL; }
			if (abilityParticles != NULL) { abilityParticles->node->remove(); abilityParticles = NULL; }
			if (resourceParticlesNW != NULL) { resourceParticlesNW->node->remove(); resourceParticlesNW = NULL; }
			if (resourceParticlesNE != NULL) { resourceParticlesNE->node->remove(); resourceParticlesNE = NULL; }
			if (resourceParticlesSW != NULL) { resourceParticlesSW->node->remove(); resourceParticlesSW = NULL; }
			if (resourceParticlesSE != NULL) { resourceParticlesSE->node->remove(); resourceParticlesSE = NULL; }

			//Change scene and GUI
			engine->setCurrentScene(title);
			engine->setCurrentGUI(guimgr.env_title);
		}
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

void PrimeGameStateManager::loop(void(*f)())
{
	//Run game!
	engine->loop(f);
}