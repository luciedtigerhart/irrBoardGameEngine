#ifndef _PRIMEGAMESTATEMANAGER_H
#define _PRIMEGAMESTATEMANAGER_H

#include <iostream>
#include "PrimeTileManager.h"
#include "PrimeTokenManager.h"
#include "PrimeGUIManager.h"

using namespace IrrBoardGameEngine;

class PrimeGameStateManager
{
private:
	//Engine
	IrrEngine* engine;

	//Scenes
	IrrScene* title;
	IrrScene* credits;
	IrrScene* tutorial;
	IrrScene* match;

	//Game board, camera and light
	IrrBoard* board;
	IrrGameObject* camera;
	ILightSceneNode *light;

	//Managers
	PrimeTileManager tilemgr;
	PrimeTokenManager tokenmgr;
	PrimeGUIManager guimgr;

	//Play State
	PrimePlayState playState;

	//Players
	PrimeTeam player1;
	PrimeTeam player2;
	PrimeTeam player3;
	PrimeTeam player4;

	//Other data

	int turn; //Match turn counter
	int playersActive; //How many players are playing

	//Scene management methods
	void ManageTitleScreen();

public:
	PrimeGameStateManager();
	~PrimeGameStateManager();

	void loop(); //Runs game
};

#endif