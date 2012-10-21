#ifndef _PRIMEGUIMANAGER_H
#define _PRIMEGUIMANAGER_H

#include <iostream>
#include <sstream>
#include "PrimePlayState.h"

using namespace IrrBoardGameEngine;

class PrimeGUIManager
{
private:
	int tutorialPage;

public:
	PrimeGUIManager();
	~PrimeGUIManager();

	//GUI environments
	IrrGUI* env_title;
	IrrGUI* env_credits;
	IrrGUI* env_tutorial;
	IrrGUI* env_match;

	void SetTurnCount(bool show, int turn); //Show, hide, reset or update turn count
	void SetTurnMarkers(bool show, int p1, int p2, int p3, int p4); //Show or hide player turn markers
	void SetPlayerIndicator(bool show, int turnPlayer); //Show, hide or update player turn indicator

	//Methods that create GUI elements
	void BuildGUITitleScreen();
	void BuildGUICreditsScreen();
	void BuildGUITutorialScreen();
	void BuildGUIMatchScreen();

	//Methods that manage screens
	void ManageGUITitleScreen();
	void ManageGUICreditsScreen();
	void ManageGUITutorialScreen();
	void ManageGUIMatchScreen(int turn, PrimePlayState playState, PrimeTeam player1, PrimeTeam player2, PrimeTeam player3, PrimeTeam player4);
};

#endif