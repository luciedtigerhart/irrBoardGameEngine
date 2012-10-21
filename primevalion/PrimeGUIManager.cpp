#include "PrimeGUIManager.h"

PrimeGUIManager::PrimeGUIManager()
{
	//Initialize some things
	tutorialPage = 1;
};

PrimeGUIManager::~PrimeGUIManager()
{
	//Delete GUI environments
	delete env_title;
	delete env_credits;
	delete env_tutorial;
	delete env_match;
};

void PrimeGUIManager::SetTurnCount(bool show, int turn)
{
	std::string turnCount;
	ostringstream convert;

	if (show)
	{
		//Convert turn to text
		convert << turn;
		turnCount = convert.str();

		//Show and update turn counter
		env_match->setImage("Label Turn Count", true);
		env_match->setText("Label Turn Count", (char*)turnCount.c_str());
	}

	else if (!show)
	{
		//Hide turn counter
		env_match->setImage("Label Turn Count", false);
		env_match->setText("Label Turn Count", "1");
	}
}

void PrimeGUIManager::SetTurnMarkers(bool show, int p1, int p2, int p3, int p4)
{
	if (show)
	{
		//Show turn markers according to player turn order
		switch (p1)
		{
			case 1: { env_match->setImage("Indicator Turn Marker P1 1st", true); break; }
			case 2: { env_match->setImage("Indicator Turn Marker P1 2nd", true); break; }
			case 3: { env_match->setImage("Indicator Turn Marker P1 3rd", true); break; }
			case 4: { env_match->setImage("Indicator Turn Marker P1 4th", true); break; }
		}

		switch (p2)
		{
			case 1: { env_match->setImage("Indicator Turn Marker P2 1st", true); break; }
			case 2: { env_match->setImage("Indicator Turn Marker P2 2nd", true); break; }
			case 3: { env_match->setImage("Indicator Turn Marker P2 3rd", true); break; }
			case 4: { env_match->setImage("Indicator Turn Marker P2 4th", true); break; }
		}

		switch (p3)
		{
			case 1: { env_match->setImage("Indicator Turn Marker P3 1st", true); break; }
			case 2: { env_match->setImage("Indicator Turn Marker P3 2nd", true); break; }
			case 3: { env_match->setImage("Indicator Turn Marker P3 3rd", true); break; }
			case 4: { env_match->setImage("Indicator Turn Marker P3 4th", true); break; }
		}

		switch (p4)
		{
			case 1: { env_match->setImage("Indicator Turn Marker P4 1st", true); break; }
			case 2: { env_match->setImage("Indicator Turn Marker P4 2nd", true); break; }
			case 3: { env_match->setImage("Indicator Turn Marker P4 3rd", true); break; }
			case 4: { env_match->setImage("Indicator Turn Marker P4 4th", true); break; }
		}
	}

	else if (!show)
	{
		//Hide all turn markers
		env_match->setImage("Indicator Turn Marker P1 1st", false);
		env_match->setImage("Indicator Turn Marker P1 2nd", false);
		env_match->setImage("Indicator Turn Marker P1 3rd", false);
		env_match->setImage("Indicator Turn Marker P1 4th", false);
		env_match->setImage("Indicator Turn Marker P2 1st", false);
		env_match->setImage("Indicator Turn Marker P2 2nd", false);
		env_match->setImage("Indicator Turn Marker P2 3rd", false);
		env_match->setImage("Indicator Turn Marker P2 4th", false);
		env_match->setImage("Indicator Turn Marker P3 1st", false);
		env_match->setImage("Indicator Turn Marker P3 2nd", false);
		env_match->setImage("Indicator Turn Marker P3 3rd", false);
		env_match->setImage("Indicator Turn Marker P3 4th", false);
		env_match->setImage("Indicator Turn Marker P4 1st", false);
		env_match->setImage("Indicator Turn Marker P4 2nd", false);
		env_match->setImage("Indicator Turn Marker P4 3rd", false);
		env_match->setImage("Indicator Turn Marker P4 4th", false);
	}
}

void PrimeGUIManager::SetPlayerIndicator(bool show, int turnPlayer)
{
	if (show)
	{
		//If this is player 1's turn...
		if (turnPlayer == 1)
		{
			env_match->setImage("Indicator Turn Player 1", true);
			env_match->setImage("Indicator Turn Player 2", false);
			env_match->setImage("Indicator Turn Player 3", false);
			env_match->setImage("Indicator Turn Player 4", false);
		}

		//If this is player 2's turn...
		else if (turnPlayer == 2)
		{
			env_match->setImage("Indicator Turn Player 1", false);
			env_match->setImage("Indicator Turn Player 2", true);
			env_match->setImage("Indicator Turn Player 3", false);
			env_match->setImage("Indicator Turn Player 4", false);
		}

		//If this is player 3's turn...
		else if (turnPlayer == 3)
		{
			env_match->setImage("Indicator Turn Player 1", false);
			env_match->setImage("Indicator Turn Player 2", false);
			env_match->setImage("Indicator Turn Player 3", true);
			env_match->setImage("Indicator Turn Player 4", false);
		}

		//If this is player 4's turn...
		else if (turnPlayer == 4)
		{
			env_match->setImage("Indicator Turn Player 1", false);
			env_match->setImage("Indicator Turn Player 2", false);
			env_match->setImage("Indicator Turn Player 3", false);
			env_match->setImage("Indicator Turn Player 4", true);
		}
	}

	else if (!show)
	{
		//Hide player indicators
		env_match->setImage("Indicator Turn Player 1", false);
		env_match->setImage("Indicator Turn Player 2", false);
		env_match->setImage("Indicator Turn Player 3", false);
		env_match->setImage("Indicator Turn Player 4", false);
	}
}

void PrimeGUIManager::BuildGUITitleScreen()
{
	//Backgrounds
	env_title->addImage("Background Title Screen","gui/outgame/background_title.jpg",0,0);

	//Player indicators
	env_title->addImage("Indicator Player 1","gui/outgame/team_player1.jpg",30,60);
	env_title->addImage("Indicator Player 2","gui/outgame/team_player2.jpg",300,60);
	env_title->addImage("Indicator Player 3","gui/outgame/team_player3.jpg",30,180);
	env_title->addImage("Indicator Player 4","gui/outgame/team_player4.jpg",300,180);

	//Player activation buttons
	env_title->addButton("Button Player 1 Activate","gui/outgame/team_on.jpg","gui/outgame/team_off.jpg",110,60,29,26);
	env_title->addButton("Button Player 2 Activate","gui/outgame/team_on.jpg","gui/outgame/team_off.jpg",380,60,29,26);
	env_title->addButton("Button Player 3 Activate","gui/outgame/team_on.jpg","gui/outgame/team_off.jpg",110,180,29,26);
	env_title->addButton("Button Player 4 Activate","gui/outgame/team_on.jpg","gui/outgame/team_off.jpg",380,180,29,26);

	//Race buttons PLAYER 1
	env_title->addButton("Button Player 1 Kobold","gui/outgame/race_kobold.jpg","gui/outgame/race_kobold_toggled.jpg",30,90,29,26);
	env_title->addButton("Button Player 1 Gnoll","gui/outgame/race_gnoll.jpg","gui/outgame/race_gnoll_toggled.jpg",60,90,29,26);
	env_title->addButton("Button Player 1 Troll","gui/outgame/race_troll.jpg","gui/outgame/race_troll_toggled.jpg",90,90,29,26);
	env_title->addButton("Button Player 1 Hog","gui/outgame/race_hog.jpg","gui/outgame/race_hog_toggled.jpg",120,90,29,26);

	//Race buttons PLAYER 2
	env_title->addButton("Button Player 2 Kobold","gui/outgame/race_kobold.jpg","gui/outgame/race_kobold_toggled.jpg",300,90,29,26);
	env_title->addButton("Button Player 2 Gnoll","gui/outgame/race_gnoll.jpg","gui/outgame/race_gnoll_toggled.jpg",330,90,29,26);
	env_title->addButton("Button Player 2 Troll","gui/outgame/race_troll.jpg","gui/outgame/race_troll_toggled.jpg",360,90,29,26);
	env_title->addButton("Button Player 2 Hog","gui/outgame/race_hog.jpg","gui/outgame/race_hog_toggled.jpg",390,90,29,26);

	//Race buttons PLAYER 3
	env_title->addButton("Button Player 3 Kobold","gui/outgame/race_kobold.jpg","gui/outgame/race_kobold_toggled.jpg",30,210,29,26);
	env_title->addButton("Button Player 3 Gnoll","gui/outgame/race_gnoll.jpg","gui/outgame/race_gnoll_toggled.jpg",60,210,29,26);
	env_title->addButton("Button Player 3 Troll","gui/outgame/race_troll.jpg","gui/outgame/race_troll_toggled.jpg",90,210,29,26);
	env_title->addButton("Button Player 3 Hog","gui/outgame/race_hog.jpg","gui/outgame/race_hog_toggled.jpg",120,210,29,26);

	//Race buttons PLAYER 4
	env_title->addButton("Button Player 4 Kobold","gui/outgame/race_kobold.jpg","gui/outgame/race_kobold_toggled.jpg",300,210,29,26);
	env_title->addButton("Button Player 4 Gnoll","gui/outgame/race_gnoll.jpg","gui/outgame/race_gnoll_toggled.jpg",330,210,29,26);
	env_title->addButton("Button Player 4 Troll","gui/outgame/race_troll.jpg","gui/outgame/race_troll_toggled.jpg",360,210,29,26);
	env_title->addButton("Button Player 4 Hog","gui/outgame/race_hog.jpg","gui/outgame/race_hog_toggled.jpg",390,210,29,26);

	//Screen transition buttons
	env_title->addButton("Button Start Match","gui/outgame/button_start_match.jpg","gui/outgame/button_start_match.jpg",250,400,124,35);
	env_title->addButton("Button Credits","gui/outgame/button_credits.jpg","gui/outgame/button_credits.jpg",80,400,124,35);
	env_title->addButton("Button Tutorial","gui/outgame/button_tutorial.jpg","gui/outgame/button_tutorial.jpg",420,400,124,35);
}

void PrimeGUIManager::BuildGUICreditsScreen()
{
	//Backgrounds
	env_credits->addImage("Background Credits Screen","gui/outgame/background_credits.jpg",0,0);

	//Screen transition buttons
	env_credits->addButton("Button Back To Title Credits","gui/outgame/button_title.jpg","gui/outgame/button_title.jpg",250,400,124,35);
}

void PrimeGUIManager::BuildGUITutorialScreen()
{
	//Backgrounds
	env_tutorial->addImage("Background Tutorial Screen Page 1","gui/outgame/background_tutorial1.jpg",0,0);
	env_tutorial->addImage("Background Tutorial Screen Page 2","gui/outgame/background_tutorial2.jpg",0,0);
	env_tutorial->addImage("Background Tutorial Screen Page 3","gui/outgame/background_tutorial3.jpg",0,0);
	env_tutorial->addImage("Background Tutorial Screen Page 4","gui/outgame/background_tutorial4.jpg",0,0);
	env_tutorial->addImage("Background Tutorial Screen Page 5","gui/outgame/background_tutorial5.jpg",0,0);

	//Browsing buttons
	env_tutorial->addButton("Button Previous","gui/outgame/button_previous.jpg","gui/outgame/button_previous.jpg",400,400,90,35);
	env_tutorial->addButton("Button Next","gui/outgame/button_next.jpg","gui/outgame/button_next.jpg",510,400,90,35);

	//Screen transition buttons
	env_tutorial->addButton("Button Back To Title Tutorial","gui/outgame/button_title.jpg","gui/outgame/button_title.jpg",50,400,124,35);
}

void PrimeGUIManager::BuildGUIMatchScreen()
{
	//Turn indicator
	env_match->addImage("Indicator Turn Widget","gui/ingame/turn_widget.jpg",10,10);
	env_match->addImage("Indicator Turn Player 1","gui/ingame/team_player1.jpg",120,15);
	env_match->addImage("Indicator Turn Player 2","gui/ingame/team_player2.jpg",120,15);
	env_match->addImage("Indicator Turn Player 3","gui/ingame/team_player3.jpg",120,15);
	env_match->addImage("Indicator Turn Player 4","gui/ingame/team_player4.jpg",120,15);
	env_match->addLabel("Label Turn Count", "1", 80,20,100,30);

	SetTurnCount(false, 0); //Reset and hide turn count
	SetPlayerIndicator(false, 0); //Hide player indicators

	//Turn markers
	env_match->addImage("Indicator Turn Marker P1 1st","gui/ingame/turn_marker_player1.jpg",20,40);
	env_match->addImage("Indicator Turn Marker P1 2nd","gui/ingame/turn_marker_player1.jpg",40,40);
	env_match->addImage("Indicator Turn Marker P1 3rd","gui/ingame/turn_marker_player1.jpg",60,40);
	env_match->addImage("Indicator Turn Marker P1 4th","gui/ingame/turn_marker_player1.jpg",80,40);

	env_match->addImage("Indicator Turn Marker P2 1st","gui/ingame/turn_marker_player2.jpg",20,40);
	env_match->addImage("Indicator Turn Marker P2 2nd","gui/ingame/turn_marker_player2.jpg",40,40);
	env_match->addImage("Indicator Turn Marker P2 3rd","gui/ingame/turn_marker_player2.jpg",60,40);
	env_match->addImage("Indicator Turn Marker P2 4th","gui/ingame/turn_marker_player2.jpg",80,40);

	env_match->addImage("Indicator Turn Marker P3 1st","gui/ingame/turn_marker_player3.jpg",20,40);
	env_match->addImage("Indicator Turn Marker P3 2nd","gui/ingame/turn_marker_player3.jpg",40,40);
	env_match->addImage("Indicator Turn Marker P3 3rd","gui/ingame/turn_marker_player3.jpg",60,40);
	env_match->addImage("Indicator Turn Marker P3 4th","gui/ingame/turn_marker_player3.jpg",80,40);

	env_match->addImage("Indicator Turn Marker P4 1st","gui/ingame/turn_marker_player4.jpg",20,40);
	env_match->addImage("Indicator Turn Marker P4 2nd","gui/ingame/turn_marker_player4.jpg",40,40);
	env_match->addImage("Indicator Turn Marker P4 3rd","gui/ingame/turn_marker_player4.jpg",60,40);
	env_match->addImage("Indicator Turn Marker P4 4th","gui/ingame/turn_marker_player4.jpg",80,40);

	SetTurnMarkers(false, 0,0,0,0); //Hide all turn markers
}

void PrimeGUIManager::ManageGUITitleScreen()
{
}

void PrimeGUIManager::ManageGUICreditsScreen()
{
}

void PrimeGUIManager::ManageGUITutorialScreen()
{
	//Draw elements according to page
	switch (tutorialPage)
	{
		case 1: //Page ONE
		{
			env_tutorial->setButton("Button Previous", false);
			env_tutorial->setButton("Button Next", true);

			env_tutorial->setImage("Background Tutorial Screen Page 1", true);
			env_tutorial->setImage("Background Tutorial Screen Page 2", false);
			env_tutorial->setImage("Background Tutorial Screen Page 3", false);
			env_tutorial->setImage("Background Tutorial Screen Page 4", false);
			env_tutorial->setImage("Background Tutorial Screen Page 5", false);

			break;
		}

		case 2: //Page TWO
		{
			env_tutorial->setButton("Button Previous", true);
			env_tutorial->setButton("Button Next", true);

			env_tutorial->setImage("Background Tutorial Screen Page 1", false);
			env_tutorial->setImage("Background Tutorial Screen Page 2", true);
			env_tutorial->setImage("Background Tutorial Screen Page 3", false);
			env_tutorial->setImage("Background Tutorial Screen Page 4", false);
			env_tutorial->setImage("Background Tutorial Screen Page 5", false);

			break;
		}

		case 3: //Page THREE
		{
			env_tutorial->setButton("Button Previous", true);
			env_tutorial->setButton("Button Next", true);

			env_tutorial->setImage("Background Tutorial Screen Page 1", false);
			env_tutorial->setImage("Background Tutorial Screen Page 2", false);
			env_tutorial->setImage("Background Tutorial Screen Page 3", true);
			env_tutorial->setImage("Background Tutorial Screen Page 4", false);
			env_tutorial->setImage("Background Tutorial Screen Page 5", false);

			break;
		}

		case 4: //Page FOUR
		{
			env_tutorial->setButton("Button Previous", true);
			env_tutorial->setButton("Button Next", true);

			env_tutorial->setImage("Background Tutorial Screen Page 1", false);
			env_tutorial->setImage("Background Tutorial Screen Page 2", false);
			env_tutorial->setImage("Background Tutorial Screen Page 3", false);
			env_tutorial->setImage("Background Tutorial Screen Page 4", true);
			env_tutorial->setImage("Background Tutorial Screen Page 5", false);

			break;
		}

		case 5: //Page FIVE
		{
			env_tutorial->setButton("Button Previous", true);
			env_tutorial->setButton("Button Next", false);

			env_tutorial->setImage("Background Tutorial Screen Page 1", false);
			env_tutorial->setImage("Background Tutorial Screen Page 2", false);
			env_tutorial->setImage("Background Tutorial Screen Page 3", false);
			env_tutorial->setImage("Background Tutorial Screen Page 4", false);
			env_tutorial->setImage("Background Tutorial Screen Page 5", true);

			break;
		}
	}
}

void PrimeGUIManager::ManageGUIMatchScreen(int turn, PrimePlayState playState, PrimeTeam player1, PrimeTeam player2, PrimeTeam player3, PrimeTeam player4)
{
	//Show turn markers in their correct order
	SetTurnMarkers(true, player1.assignedTurn, player2.assignedTurn, player3.assignedTurn, player4.assignedTurn);
	
	//Show player indicator according to turn
	SetPlayerIndicator(true, playState.turnPlayer);

	//Update turn count
	SetTurnCount(true, turn);
}