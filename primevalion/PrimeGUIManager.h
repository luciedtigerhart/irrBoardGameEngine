#ifndef _PRIMEGUIMANAGER_H
#define _PRIMEGUIMANAGER_H

#include <iostream>
#include <sstream>
#include "PrimePlayState.h"

#define SORT_MESSAGE true
#define TURN_MESSAGE true

using namespace IrrBoardGameEngine;

class PrimeGUIManager
{
private:
	int tutorialPage; //Current tutorial page
	int playersActive; //Amount of players active in match

public:
	PrimeGUIManager();
	~PrimeGUIManager();

	//GUI environments
	IrrGUI* env_title;
	IrrGUI* env_credits;
	IrrGUI* env_tutorial;
	IrrGUI* env_match;

	void SetTurnCount(bool show, int turn); //Show, hide, reset or update turn count
	void SetPlayerIndicator(bool show, int turnPlayer); //Show, hide or update player turn indicator

	//Show and hide match messages
	void SetGenericMessage(bool sortMessage, bool turnMessage, int player);
	void ShowVictoryMessage(PrimePlayState playState);
	void HideVictoryMessage();

	//Show and hide player turn markers
	void ShowTurnMarkers(PrimePlayState playState);
	void HideTurnMarkers();

	//Show, hide and update resource indicators and labels
	void UpdateMatchIndicator(bool show, char* indicator, char* label, std::string counter);
	void ShowResourceIndicators(int players, PrimeTeam p1, PrimeTeam p2, PrimeTeam p3, PrimeTeam p4);
	void HideResourceIndicators();

	//Methods that create GUI elements
	void BuildGUITitleScreen();
	void BuildGUICreditsScreen();
	void BuildGUITutorialScreen();
	void BuildGUIMatchScreen();

	//Methods that manage screens
	void ManageGUITitleScreen();
	void ManageGUICreditsScreen();
	void ManageGUITutorialScreen();
	void ManageGUIMatchScreen(int turn, PrimePlayState playState);
};

#endif