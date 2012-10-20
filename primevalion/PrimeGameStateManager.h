#ifndef _PRIMEGAMESTATEMANAGER_H
#define _PRIMEGAMESTATEMANAGER_H

#include <iostream>
#include "PrimeTileManager.h"
#include "PrimeTokenManager.h"

using namespace IrrBoardGameEngine;

class PrimeGameStateManager
{
private:
	//Engine
	IrrEngine *engine;

	//GUI environments
	IrrGUI *guienv_title;
	IrrGUI *guienv_credits;
	IrrGUI *guienv_tutorial;
	IrrGUI *guienv_match;

	//Scenes
	IrrScene *title;
	IrrScene *credits;
	IrrScene *tutorial;
	IrrScene *match;

	//Game board and camera
	IrrBoard * board;
	IrrGameObject *camera;

	//Players
	PrimeTeam player1;
	PrimeTeam player2;
	PrimeTeam player3;
	PrimeTeam player4;

	PrimeToken *tokenTeam1;
	PrimeToken *tokenTeam2;
	PrimeToken *tokenTeam3;
	PrimeToken *tokenTeam4;

public:
	PrimeGameStateManager();
	~PrimeGameStateManager();

	void loop(); //Runs game
};

#endif