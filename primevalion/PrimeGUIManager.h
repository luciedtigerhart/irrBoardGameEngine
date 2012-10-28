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

	//GUI element names:
	enum
	{
		//Backgrounds
		BACKGROUND_TITLE_SCREEN = 1,
		BACKGROUND_CREDITS_SCREEN,
		BACKGROUND_TUTORIAL_SCREEN_PAGE_1,
		BACKGROUND_TUTORIAL_SCREEN_PAGE_2,
		BACKGROUND_TUTORIAL_SCREEN_PAGE_3,
		BACKGROUND_TUTORIAL_SCREEN_PAGE_4,
		BACKGROUND_TUTORIAL_SCREEN_PAGE_5,

		//------------------
		// TITLE SCREEN
		//------------------

		//Player indicators
		INDICATOR_PLAYER_1,
		INDICATOR_PLAYER_2,
		INDICATOR_PLAYER_3,
		INDICATOR_PLAYER_4,

		//Player activation buttons
		BUTTON_PLAYER_1_ACTIVATE,
		BUTTON_PLAYER_2_ACTIVATE,
		BUTTON_PLAYER_3_ACTIVATE,
		BUTTON_PLAYER_4_ACTIVATE,

		//Race buttons PLAYER 1
		BUTTON_PLAYER_1_KOBOLD,
		BUTTON_PLAYER_1_GNOLL,
		BUTTON_PLAYER_1_TROLL,
		BUTTON_PLAYER_1_HOG,
		
		//Race buttons PLAYER 2
		BUTTON_PLAYER_2_KOBOLD,
		BUTTON_PLAYER_2_GNOLL,
		BUTTON_PLAYER_2_TROLL,
		BUTTON_PLAYER_2_HOG,

		//Race buttons PLAYER 3
		BUTTON_PLAYER_3_KOBOLD,
		BUTTON_PLAYER_3_GNOLL,
		BUTTON_PLAYER_3_TROLL,
		BUTTON_PLAYER_3_HOG,

		//Race buttons PLAYER 4
		BUTTON_PLAYER_4_KOBOLD,
		BUTTON_PLAYER_4_GNOLL,
		BUTTON_PLAYER_4_TROLL,
		BUTTON_PLAYER_4_HOG,

		//Screen transition buttons
		BUTTON_CREDITS,
		BUTTON_START_MATCH,
		BUTTON_TUTORIAL,

		//------------------
		// CREDITS SCREEN
		//------------------

		//Screen transition buttons
		BUTTON_BACK_TO_TITLE_CREDITS,

		//------------------
		// TUTORIAL SCREEN
		//------------------

		//Browsing buttons
		BUTTON_PREVIOUS,
		BUTTON_NEXT,

		//Screen transition buttons
		BUTTON_BACK_TO_TITLE_TUTORIAL,

		//------------------
		// MATCH SCREEN
		//------------------

		//Buttons
		BUTTON_END_TURN,
		BUTTON_END_MATCH,

		//Turn indicator
		INDICATOR_TURN_WIDGET,
		INDICATOR_TURN_PLAYER_1,
		INDICATOR_TURN_PLAYER_2,
		INDICATOR_TURN_PLAYER_3,
		INDICATOR_TURN_PLAYER_4,
		LABEL_TURN_COUNT,

		//Turn markers
		INDICATOR_TURN_MARKER_P1_1ST,
		INDICATOR_TURN_MARKER_P1_2ND,
		INDICATOR_TURN_MARKER_P1_3RD,
		INDICATOR_TURN_MARKER_P1_4TH,

		INDICATOR_TURN_MARKER_P2_1ST,
		INDICATOR_TURN_MARKER_P2_2ND,
		INDICATOR_TURN_MARKER_P2_3RD,
		INDICATOR_TURN_MARKER_P2_4TH,

		INDICATOR_TURN_MARKER_P3_1ST,
		INDICATOR_TURN_MARKER_P3_2ND,
		INDICATOR_TURN_MARKER_P3_3RD,
		INDICATOR_TURN_MARKER_P3_4TH,

		INDICATOR_TURN_MARKER_P4_1ST,
		INDICATOR_TURN_MARKER_P4_2ND,
		INDICATOR_TURN_MARKER_P4_3RD,
		INDICATOR_TURN_MARKER_P4_4TH,

		//Resource indicator widgets
		INDICATOR_RESOURCES_P1_1ST,
		INDICATOR_RESOURCES_P1_2ND,
		INDICATOR_RESOURCES_P1_3RD,
		INDICATOR_RESOURCES_P1_4TH,
		INDICATOR_RESOURCES_P1_1ST_ODD,
		INDICATOR_RESOURCES_P1_2ND_ODD,
		INDICATOR_RESOURCES_P1_3RD_ODD,

		INDICATOR_RESOURCES_P2_1ST,
		INDICATOR_RESOURCES_P2_2ND,
		INDICATOR_RESOURCES_P2_3RD,
		INDICATOR_RESOURCES_P2_4TH,
		INDICATOR_RESOURCES_P2_1ST_ODD,
		INDICATOR_RESOURCES_P2_2ND_ODD,
		INDICATOR_RESOURCES_P2_3RD_ODD,

		INDICATOR_RESOURCES_P3_1ST,
		INDICATOR_RESOURCES_P3_2ND,
		INDICATOR_RESOURCES_P3_3RD,
		INDICATOR_RESOURCES_P3_4TH,
		INDICATOR_RESOURCES_P3_1ST_ODD,
		INDICATOR_RESOURCES_P3_2ND_ODD,
		INDICATOR_RESOURCES_P3_3RD_ODD,

		INDICATOR_RESOURCES_P4_1ST,
		INDICATOR_RESOURCES_P4_2ND,
		INDICATOR_RESOURCES_P4_3RD,
		INDICATOR_RESOURCES_P4_4TH,
		INDICATOR_RESOURCES_P4_1ST_ODD,
		INDICATOR_RESOURCES_P4_2ND_ODD,
		INDICATOR_RESOURCES_P4_3RD_ODD,

		//Resource labels
		LABEL_RESOURCES_1ST,
		LABEL_RESOURCES_2ND,
		LABEL_RESOURCES_3RD,
		LABEL_RESOURCES_4TH,
		LABEL_RESOURCES_1ST_ODD,
		LABEL_RESOURCES_2ND_ODD,
		LABEL_RESOURCES_3RD_ODD,

		//Generic messages
		MESSAGE_SORT,
		MESSAGE_TURN,
		MESSAGE_PLAYER_1,
		MESSAGE_PLAYER_2,
		MESSAGE_PLAYER_3,
		MESSAGE_PLAYER_4,

		//Victory messages
		MESSAGE_VICTORY_SINGLE,
		MESSAGE_VICTORY_DOUBLE,
		MESSAGE_VICTORY_TRIPLE,
		MESSAGE_VICTORY_QUADRUPLE,

		MESSAGE_VICTORY_P1_SINGLE,
		MESSAGE_VICTORY_P1_DOUBLE_TOP,
		MESSAGE_VICTORY_P1_TRIPLE_TOP,
		MESSAGE_VICTORY_P1_QUADRUPLE_TOP,

		MESSAGE_VICTORY_P2_SINGLE,
		MESSAGE_VICTORY_P2_DOUBLE_TOP,
		MESSAGE_VICTORY_P2_DOUBLE_BOTTOM,
		MESSAGE_VICTORY_P2_TRIPLE_TOP,
		MESSAGE_VICTORY_P2_TRIPLE_MIDDLE,
		MESSAGE_VICTORY_P2_QUADRUPLE_MIDDLE_TOP,

		MESSAGE_VICTORY_P3_SINGLE,
		MESSAGE_VICTORY_P3_DOUBLE_TOP,
		MESSAGE_VICTORY_P3_DOUBLE_BOTTOM,
		MESSAGE_VICTORY_P3_TRIPLE_MIDDLE,
		MESSAGE_VICTORY_P3_TRIPLE_BOTTOM,
		MESSAGE_VICTORY_P3_QUADRUPLE_MIDDLE_BOTTOM,

		MESSAGE_VICTORY_P4_SINGLE,
		MESSAGE_VICTORY_P4_DOUBLE_BOTTOM,
		MESSAGE_VICTORY_P4_TRIPLE_BOTTOM,
		MESSAGE_VICTORY_P4_QUADRUPLE_BOTTOM,
	};

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
	void UpdateMatchIndicator(bool show, irr::s32 indicator, irr::s32 label, std::string counter);
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