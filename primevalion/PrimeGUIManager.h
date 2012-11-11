#ifndef _PRIMEGUIMANAGER_H
#define _PRIMEGUIMANAGER_H

#include <iostream>
#include <sstream>
#include "PrimePlayState.h"

//Some GUI definitions
//----------------------------

	#define SORT_MESSAGE true
	#define TURN_MESSAGE true

	#define BUTTON_LIGHT 1
	#define BUTTON_HEAVY 2
	#define BUTTON_RACE 2

	#define TITLE_TRANSITION 3
	#define MATCH_TRANSITION 4
	#define TUTORIAL_TRANSITION 5
	#define CREDITS_TRANSITION 6

	#define FADING_IN 0
	#define FADING_OUT 1
	#define FADED_OUT 2

//----------------------------

using namespace IrrBoardGameEngine;

class PrimeGUIManager
{
private:
	int playersActive; //Amount of players active in a match
	int tutorialPage; //Current tutorial page
	bool nextReleased, previousReleased; //Tutorial buttons released state storages

	//GUI element names:
	enum
	{
		//Fonts
		FONT_DUNGEON_TURN_COUNT = 1,
		FONT_DUNGEON_RESOURCES,

		//Backgrounds
		BACKGROUND_LOADING_SCREEN,
		BACKGROUND_TITLE_SCREEN,
		BACKGROUND_CREDITS_SCREEN,
		BACKGROUND_TUTORIAL_SCREEN_PAGE_1,
		BACKGROUND_TUTORIAL_SCREEN_PAGE_2,
		BACKGROUND_TUTORIAL_SCREEN_PAGE_3,
		BACKGROUND_TUTORIAL_SCREEN_PAGE_4,
		BACKGROUND_TUTORIAL_SCREEN_PAGE_5,

		//------------------
		// TITLE SCREEN
		//------------------

		//Active player indicators
		INDICATOR_PLAYER_1_ON,
		INDICATOR_PLAYER_2_ON,
		INDICATOR_PLAYER_3_ON,
		INDICATOR_PLAYER_4_ON,

		//Inactive player indicators
		INDICATOR_PLAYER_1_OFF,
		INDICATOR_PLAYER_2_OFF,
		INDICATOR_PLAYER_3_OFF,
		INDICATOR_PLAYER_4_OFF,

		//Player activation buttons
		BUTTON_PLAYER_1_ACTIVATE,
		BUTTON_PLAYER_2_ACTIVATE,
		BUTTON_PLAYER_3_ACTIVATE,
		BUTTON_PLAYER_4_ACTIVATE,

		//Player deactivation buttons
		BUTTON_PLAYER_1_DEACTIVATE,
		BUTTON_PLAYER_2_DEACTIVATE,
		BUTTON_PLAYER_3_DEACTIVATE,
		BUTTON_PLAYER_4_DEACTIVATE,

		//Selected race PLAYER 1
		IMAGE_PLAYER_1_KOBOLD,
		IMAGE_PLAYER_1_GNOLL,
		IMAGE_PLAYER_1_TROLL,
		IMAGE_PLAYER_1_HOG,
		
		//Selected race PLAYER 2
		IMAGE_PLAYER_2_KOBOLD,
		IMAGE_PLAYER_2_GNOLL,
		IMAGE_PLAYER_2_TROLL,
		IMAGE_PLAYER_2_HOG,

		//Selected race PLAYER 3
		IMAGE_PLAYER_3_KOBOLD,
		IMAGE_PLAYER_3_GNOLL,
		IMAGE_PLAYER_3_TROLL,
		IMAGE_PLAYER_3_HOG,

		//Selected race PLAYER 4
		IMAGE_PLAYER_4_KOBOLD,
		IMAGE_PLAYER_4_GNOLL,
		IMAGE_PLAYER_4_TROLL,
		IMAGE_PLAYER_4_HOG,

		//Unselected race buttons
		BUTTON_UNSELECTED_KOBOLD_P1,
		BUTTON_UNSELECTED_KOBOLD_P2,
		BUTTON_UNSELECTED_KOBOLD_P3,
		BUTTON_UNSELECTED_KOBOLD_P4,
		
		BUTTON_UNSELECTED_GNOLL_P1,
		BUTTON_UNSELECTED_GNOLL_P2,
		BUTTON_UNSELECTED_GNOLL_P3,
		BUTTON_UNSELECTED_GNOLL_P4,
		
		BUTTON_UNSELECTED_TROLL_P1,
		BUTTON_UNSELECTED_TROLL_P2,
		BUTTON_UNSELECTED_TROLL_P3,
		BUTTON_UNSELECTED_TROLL_P4,

		BUTTON_UNSELECTED_HOG_P1,
		BUTTON_UNSELECTED_HOG_P2,
		BUTTON_UNSELECTED_HOG_P3,
		BUTTON_UNSELECTED_HOG_P4,

		//Unselectable race images
		IMAGE_UNSELECTABLE_KOBOLD_P1,
		IMAGE_UNSELECTABLE_KOBOLD_P2,
		IMAGE_UNSELECTABLE_KOBOLD_P3,
		IMAGE_UNSELECTABLE_KOBOLD_P4,

		IMAGE_UNSELECTABLE_GNOLL_P1,
		IMAGE_UNSELECTABLE_GNOLL_P2,
		IMAGE_UNSELECTABLE_GNOLL_P3,
		IMAGE_UNSELECTABLE_GNOLL_P4,

		IMAGE_UNSELECTABLE_TROLL_P1,
		IMAGE_UNSELECTABLE_TROLL_P2,
		IMAGE_UNSELECTABLE_TROLL_P3,
		IMAGE_UNSELECTABLE_TROLL_P4,

		IMAGE_UNSELECTABLE_HOG_P1,
		IMAGE_UNSELECTABLE_HOG_P2,
		IMAGE_UNSELECTABLE_HOG_P3,
		IMAGE_UNSELECTABLE_HOG_P4,

		//Screen transition buttons
		BUTTON_CREDITS,
		BUTTON_START_MATCH,
		BUTTON_TUTORIAL,

		//Disabled buttons
		IMAGE_START_MATCH_DISABLED,

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

		//Disabled buttons
		IMAGE_PREVIOUS_DISABLED,
		IMAGE_NEXT_DISABLED,

		//Screen transition buttons
		BUTTON_BACK_TO_TITLE_TUTORIAL,

		//------------------
		// MATCH SCREEN
		//------------------

		//Buttons
		BUTTON_END_TURN,
		BUTTON_END_MATCH,

		//Disabled buttons
		IMAGE_END_TURN_DISABLED,
		IMAGE_END_MATCH_DISABLED,

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
	IrrGUI* env_loader;
	IrrGUI* env_title;
	IrrGUI* env_credits;
	IrrGUI* env_tutorial;
	IrrGUI* env_match;

	//Enable or disable match buttons
	void EnableEndTurnButton(bool enable);
	void EnableEndMatchButton(bool enable);

	//Show, hide, reset or update turn count and player turn indicator
	void SetTurnCount(bool show, int turn);
	void SetPlayerIndicator(bool show, int turnPlayer);

	//Show and hide match messages
	void SetGenericMessage(bool sortMessage, bool turnMessage, int player);
	void ShowVictoryMessage(PrimePlayState* playState);
	void HideVictoryMessage();

	//Show and hide player turn markers
	void ShowTurnMarkers(PrimePlayState* playState);
	void HideTurnMarkers();

	//Show, hide and update resource indicators and labels
	void UpdateMatchIndicator(bool show, irr::s32 indicator, irr::s32 label, std::string counter);
	void ShowResourceIndicators(int players, PrimeTeam p1, PrimeTeam p2, PrimeTeam p3, PrimeTeam p4);
	void HideResourceIndicators();

	//Show or hide player indicators and "On/Off" buttons in title screen
	void ShowPlayerIndicators(PrimeTeam* p1, PrimeTeam* p2, PrimeTeam* p3, PrimeTeam* p4);
	void ShowPlayerOnOffButtons(PrimeTeam* p1, PrimeTeam* p2, PrimeTeam* p3, PrimeTeam* p4);

	//Show or hide race buttons in title screen
	void ShowRaces(PrimeTeam* p1, PrimeTeam* p2, PrimeTeam* p3, PrimeTeam* p4);
	void ShowUnselectedRaces(int player);
	void ShowUnselectableRaces(int player);
	void HideUnselectableRaces();
	void HideUnselectedRaces();
	void HideSelectedRaces();

	//Set pages manually or flip pages automatically in tutorial screen
	void SetTutorialPage(int page);
	void FlipTutorialPages();

	//Button press verification methods

		//Title screen
		bool VerifyTitlePlayerOnOffButtons(PrimeTeam* p1, PrimeTeam* p2, PrimeTeam* p3, PrimeTeam* p4);
		bool VerifyTitleRaceButtons(PrimeTeam* p1, PrimeTeam* p2, PrimeTeam* p3, PrimeTeam* p4);
		bool VerifyTitleStartMatchButton(PrimeTeam* p1, PrimeTeam* p2, PrimeTeam* p3, PrimeTeam* p4);
		bool VerifyTitleTutorialButton();
		bool VerifyTitleCreditsButton();

		//Tutorial screen
		bool VerifyTutorialNextButtonPressed();
		bool VerifyTutorialNextButtonReleased();
		bool VerifyTutorialPreviousButtonPressed();
		bool VerifyTutorialPreviousButtonReleased();
		bool VerifyTutorialBackToTitleButton();

		//Credits screen
		bool VerifyCreditsBackToTitleButton();

		//Match screen
		bool VerifyMatchEndTurnButton();
		bool VerifyMatchEndMatchButton();


	//Methods that create GUI elements
	void BuildGUILoadingScreen();
	void BuildGUITitleScreen();
	void BuildGUITutorialScreen();
	void BuildGUICreditsScreen();
	void BuildGUIMatchScreen();

	//Methods that manage screens
	int ManageGUITitleScreen(PrimeTeam* p1, PrimeTeam* p2, PrimeTeam* p3, PrimeTeam* p4);
	int ManageGUICreditsScreen();
	int ManageGUITutorialScreen();
	int ManageGUIMatchScreen(int turn, PrimePlayState* playState);
};

#endif