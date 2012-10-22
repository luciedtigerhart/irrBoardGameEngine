#include "PrimeGUIManager.h"

PrimeGUIManager::PrimeGUIManager()
{
	//Initialize some things
	tutorialPage = 1;
	playersActive = 0;
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
		env_match->setLabel("Label Turn Count", true);
		env_match->setText("Label Turn Count", (char*)turnCount.c_str());
	}

	else if (!show)
	{
		//Hide and reset turn counter
		env_match->setLabel("Label Turn Count", false);
		env_match->setText("Label Turn Count", "1");
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

void PrimeGUIManager::SetGenericMessage(bool sortMessage, bool turnMessage, int player)
{
	if (sortMessage)
	{
		//Show "Sorting turn order..." message
		env_match->setImage("Message Sort", true);
	}

	else if (turnMessage)
	{
		//Show the correct "Player X Turn" message

		env_match->setImage("Message Turn", true);

		if (player == 1) env_match->setImage("Message Player 1", true);
		else if (player == 2) env_match->setImage("Message Player 2", true);
		else if (player == 3) env_match->setImage("Message Player 3", true);
		else if (player == 4) env_match->setImage("Message Player 4", true);
	}

	else
	{
		//Hide all messages
		env_match->setImage("Message Sort", false);
		env_match->setImage("Message Turn", false);
		env_match->setImage("Message Player 1", false);
		env_match->setImage("Message Player 2", false);
		env_match->setImage("Message Player 3", false);
		env_match->setImage("Message Player 4", false);
	}
}

void PrimeGUIManager::ShowVictoryMessage(PrimePlayState playState)
{
	int playersVictorious = 0;

	//Count how many players won the match (Draw)
	if (playState.player1.isVictorious) playersVictorious++;
	if (playState.player2.isVictorious) playersVictorious++;
	if (playState.player3.isVictorious) playersVictorious++;
	if (playState.player4.isVictorious) playersVictorious++;

	//Check victory condition and display messages accordingly

	//One winner...
	if (playersVictorious == 1)
	{
		env_match->setImage("Message Victory Single", true);

		if (playState.player1.isVictorious) env_match->setImage("Message Victory P1 Single", true);
		else if (playState.player2.isVictorious) env_match->setImage("Message Victory P2 Single", true);
		else if (playState.player3.isVictorious) env_match->setImage("Message Victory P3 Single", true);
		else if (playState.player4.isVictorious) env_match->setImage("Message Victory P4 Single", true);
	}

	//Two winners...
	if (playersVictorious == 2)
	{
		env_match->setImage("Message Victory Double", true);

		if (playState.player1.isVictorious)
		{
			env_match->setImage("Message Victory P1 Double Top", true);
			if (playState.player2.isVictorious) env_match->setImage("Message Victory P2 Double Bottom", true);
			else if (playState.player3.isVictorious) env_match->setImage("Message Victory P3 Double Bottom", true);
			else if (playState.player4.isVictorious) env_match->setImage("Message Victory P4 Double Bottom", true);
		}

		else if (playState.player2.isVictorious)
		{
			env_match->setImage("Message Victory P2 Double Top", true);
			if (playState.player3.isVictorious) env_match->setImage("Message Victory P3 Double Bottom", true);
			else if (playState.player4.isVictorious) env_match->setImage("Message Victory P4 Double Bottom", true);
		}

		else if (playState.player3.isVictorious)
		{
			env_match->setImage("Message Victory P3 Double Top", true);
			env_match->setImage("Message Victory P4 Double Bottom", true);
		}
	}

	//Three winners...
	if (playersVictorious == 3)
	{
		env_match->setImage("Message Victory Triple", true);

		if (playState.player1.isVictorious)
		{
			env_match->setImage("Message Victory P1 Triple Top", true);
			
			if (playState.player2.isVictorious)
			{
				env_match->setImage("Message Victory P2 Triple Middle", true);
				if (playState.player3.isVictorious) env_match->setImage("Message Victory P3 Triple Bottom", true);
				else if (playState.player4.isVictorious) env_match->setImage("Message Victory P4 Triple Bottom", true);
			}

			else if (playState.player3.isVictorious)
			{
				env_match->setImage("Message Victory P3 Triple Middle", true);
				env_match->setImage("Message Victory P4 Triple Bottom", true);
			}
		}

		else if (playState.player2.isVictorious)
		{
			env_match->setImage("Message Victory P2 Triple Top", true);
			env_match->setImage("Message Victory P3 Triple Middle", true);
			env_match->setImage("Message Victory P4 Triple Bottom", true);
		}
	}

	//Four winners...
	if (playersVictorious == 4)
	{
		env_match->setImage("Message Victory Quadruple", true);
		env_match->setImage("Message Victory P1 Quadruple Top", true);
		env_match->setImage("Message Victory P2 Quadruple Middle Top", true);
		env_match->setImage("Message Victory P3 Quadruple Middle Bottom", true);
		env_match->setImage("Message Victory P4 Quadruple Bottom", true);
	}
}

void PrimeGUIManager::HideVictoryMessage()
{
	//Hide all victory messages
	env_match->setImage("Message Victory Single", false);
	env_match->setImage("Message Victory Double", false);
	env_match->setImage("Message Victory Triple", false);
	env_match->setImage("Message Victory Quadruple", false);

	env_match->setImage("Message Victory P1 Single", false);
	env_match->setImage("Message Victory P1 Double Top", false);
	env_match->setImage("Message Victory P1 Triple Top", false);
	env_match->setImage("Message Victory P1 Quadruple Top", false);

	env_match->setImage("Message Victory P2 Single", false);
	env_match->setImage("Message Victory P2 Double Top", false);
	env_match->setImage("Message Victory P2 Double Bottom", false);
	env_match->setImage("Message Victory P2 Triple Top", false);
	env_match->setImage("Message Victory P2 Triple Middle", false);
	env_match->setImage("Message Victory P2 Quadruple Middle Top", false);
	
	env_match->setImage("Message Victory P3 Single", false);
	env_match->setImage("Message Victory P3 Double Top", false);
	env_match->setImage("Message Victory P3 Double Bottom", false);
	env_match->setImage("Message Victory P3 Triple Middle", false);
	env_match->setImage("Message Victory P3 Triple Bottom", false);
	env_match->setImage("Message Victory P3 Quadruple Middle Bottom", false);

	env_match->setImage("Message Victory P4 Single", false);
	env_match->setImage("Message Victory P4 Double Bottom", false);
	env_match->setImage("Message Victory P4 Triple Bottom", false);
	env_match->setImage("Message Victory P4 Quadruple Bottom", false);
}

void PrimeGUIManager::ShowTurnMarkers(PrimePlayState playState)
{
	//Get turn order
	int p1 = playState.player1.assignedTurn;
	int p2 = playState.player2.assignedTurn;
	int p3 = playState.player3.assignedTurn;
	int p4 = playState.player4.assignedTurn;

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

void PrimeGUIManager::HideTurnMarkers()
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

void PrimeGUIManager::UpdateMatchIndicator(bool show, char* indicator, char* label, std::string counter)
{
	//Show indicator widget
	env_match->setImage(indicator, show);

	//Show and update label
	env_match->setLabel(label, show);
	env_match->setText(label, (char*)counter.c_str());
}

void PrimeGUIManager::ShowResourceIndicators(int players, PrimeTeam p1, PrimeTeam p2, PrimeTeam p3, PrimeTeam p4)
{
	std::string resourceCount;
	ostringstream convertP1, convertP2, convertP3, convertP4;

	playersActive = players;

	//Convert player resources to text
	convertP1 << p1.primevalium;
	convertP2 << p2.primevalium;
	convertP3 << p3.primevalium;
	convertP4 << p4.primevalium;

	//Show resource indicators accordingly

	//Two active players...
	if (playersActive == 2)
	{
		if (p1.isActive)
		{
			resourceCount = convertP1.str();

			if (p1.assignedTurn == 1) UpdateMatchIndicator(true, "Indicator Resources P1 2nd", "Label Resources 2nd", resourceCount);
			else if (p1.assignedTurn == 2) UpdateMatchIndicator(true, "Indicator Resources P1 3rd", "Label Resources 3rd", resourceCount);
		}

		if (p2.isActive)
		{
			resourceCount = convertP2.str();

			if (p2.assignedTurn == 1) UpdateMatchIndicator(true, "Indicator Resources P2 2nd", "Label Resources 2nd", resourceCount);
			else if (p2.assignedTurn == 2) UpdateMatchIndicator(true, "Indicator Resources P2 3rd", "Label Resources 3rd", resourceCount);
		}

		if (p3.isActive)
		{
			resourceCount = convertP3.str();

			if (p3.assignedTurn == 1) UpdateMatchIndicator(true, "Indicator Resources P3 2nd", "Label Resources 2nd", resourceCount);
			else if (p3.assignedTurn == 2) UpdateMatchIndicator(true, "Indicator Resources P3 3rd", "Label Resources 3rd", resourceCount);
		}

		if (p4.isActive)
		{
			resourceCount = convertP4.str();

			if (p4.assignedTurn == 1) UpdateMatchIndicator(true, "Indicator Resources P4 2nd", "Label Resources 2nd", resourceCount);
			else if (p4.assignedTurn == 2) UpdateMatchIndicator(true, "Indicator Resources P4 3rd", "Label Resources 3rd", resourceCount);
		}
	}

	//Three active players...
	else if (playersActive == 3)
	{
		if (p1.isActive)
		{
			resourceCount = convertP1.str();

			if (p1.assignedTurn == 1) UpdateMatchIndicator(true, "Indicator Resources P1 1st Odd", "Label Resources 1st Odd", resourceCount);
			else if (p1.assignedTurn == 2) UpdateMatchIndicator(true, "Indicator Resources P1 2nd Odd", "Label Resources 2nd Odd", resourceCount);
			else if (p1.assignedTurn == 3) UpdateMatchIndicator(true, "Indicator Resources P1 3rd Odd", "Label Resources 3rd Odd", resourceCount);
		}

		if (p2.isActive)
		{
			resourceCount = convertP2.str();

			if (p2.assignedTurn == 1) UpdateMatchIndicator(true, "Indicator Resources P2 1st Odd", "Label Resources 1st Odd", resourceCount);
			else if (p2.assignedTurn == 2) UpdateMatchIndicator(true, "Indicator Resources P2 2nd Odd", "Label Resources 2nd Odd", resourceCount);
			else if (p2.assignedTurn == 3) UpdateMatchIndicator(true, "Indicator Resources P2 3rd Odd", "Label Resources 3rd Odd", resourceCount);
		}

		if (p3.isActive)
		{
			resourceCount = convertP3.str();

			if (p3.assignedTurn == 1) UpdateMatchIndicator(true, "Indicator Resources P3 1st Odd", "Label Resources 1st Odd", resourceCount);
			else if (p3.assignedTurn == 2) UpdateMatchIndicator(true, "Indicator Resources P3 2nd Odd", "Label Resources 2nd Odd", resourceCount);
			else if (p3.assignedTurn == 3) UpdateMatchIndicator(true, "Indicator Resources P3 3rd Odd", "Label Resources 3rd Odd", resourceCount);
		}

		if (p4.isActive)
		{
			resourceCount = convertP4.str();

			if (p4.assignedTurn == 1)  UpdateMatchIndicator(true, "Indicator Resources P4 1st Odd", "Label Resources 1st Odd", resourceCount);
			else if (p4.assignedTurn == 2) UpdateMatchIndicator(true, "Indicator Resources P4 2nd Odd", "Label Resources 2nd Odd", resourceCount);
			else if (p4.assignedTurn == 3) UpdateMatchIndicator(true, "Indicator Resources P4 3rd Odd", "Label Resources 3rd Odd", resourceCount);
		}
	}

	//Four active players...
	else if (playersActive == 4)
	{
		if (p1.isActive)
		{
			resourceCount = convertP1.str();

			if (p1.assignedTurn == 1) UpdateMatchIndicator(true, "Indicator Resources P1 1st", "Label Resources 1st", resourceCount);
			else if (p1.assignedTurn == 2) UpdateMatchIndicator(true, "Indicator Resources P1 2nd", "Label Resources 2nd", resourceCount);
			else if (p1.assignedTurn == 3) UpdateMatchIndicator(true, "Indicator Resources P1 3rd", "Label Resources 3rd", resourceCount);
			else if (p1.assignedTurn == 4) UpdateMatchIndicator(true, "Indicator Resources P1 4th", "Label Resources 4th", resourceCount);
		}

		if (p2.isActive)
		{
			resourceCount = convertP2.str();

			if (p2.assignedTurn == 1) UpdateMatchIndicator(true, "Indicator Resources P2 1st", "Label Resources 1st", resourceCount);
			else if (p2.assignedTurn == 2) UpdateMatchIndicator(true, "Indicator Resources P2 2nd", "Label Resources 2nd", resourceCount);
			else if (p2.assignedTurn == 3) UpdateMatchIndicator(true, "Indicator Resources P2 3rd", "Label Resources 3rd", resourceCount);
			else if (p2.assignedTurn == 4) UpdateMatchIndicator(true, "Indicator Resources P2 4th", "Label Resources 4th", resourceCount);
		}

		if (p3.isActive)
		{
			resourceCount = convertP3.str();

			if (p3.assignedTurn == 1) UpdateMatchIndicator(true, "Indicator Resources P3 1st", "Label Resources 1st", resourceCount);
			else if (p3.assignedTurn == 2) UpdateMatchIndicator(true, "Indicator Resources P3 2nd", "Label Resources 2nd", resourceCount);
			else if (p3.assignedTurn == 3) UpdateMatchIndicator(true, "Indicator Resources P3 3rd", "Label Resources 3rd", resourceCount);
			else if (p3.assignedTurn == 4) UpdateMatchIndicator(true, "Indicator Resources P3 4th", "Label Resources 4th", resourceCount);
		}

		if (p4.isActive)
		{
			resourceCount = convertP4.str();

			if (p4.assignedTurn == 1) UpdateMatchIndicator(true, "Indicator Resources P4 1st", "Label Resources 1st", resourceCount);
			else if (p4.assignedTurn == 2) UpdateMatchIndicator(true, "Indicator Resources P4 2nd", "Label Resources 2nd", resourceCount);
			else if (p4.assignedTurn == 3) UpdateMatchIndicator(true, "Indicator Resources P4 3rd", "Label Resources 3rd", resourceCount);
			else if (p4.assignedTurn == 4) UpdateMatchIndicator(true, "Indicator Resources P4 4th", "Label Resources 4th", resourceCount);
		}
	}
}

void PrimeGUIManager::HideResourceIndicators()
{
	//Hide all resource indicators

	env_match->setImage("Indicator Resources P1 1st", false);
	env_match->setImage("Indicator Resources P1 2nd", false);
	env_match->setImage("Indicator Resources P1 3rd", false);
	env_match->setImage("Indicator Resources P1 4th", false);
	env_match->setImage("Indicator Resources P1 1st Odd", false);
	env_match->setImage("Indicator Resources P1 2nd Odd", false);
	env_match->setImage("Indicator Resources P1 3rd Odd", false);

	env_match->setImage("Indicator Resources P2 1st", false);
	env_match->setImage("Indicator Resources P2 2nd", false);
	env_match->setImage("Indicator Resources P2 3rd", false);
	env_match->setImage("Indicator Resources P2 4th", false);
	env_match->setImage("Indicator Resources P2 1st Odd", false);
	env_match->setImage("Indicator Resources P2 2nd Odd", false);
	env_match->setImage("Indicator Resources P2 3rd Odd", false);

	env_match->setImage("Indicator Resources P3 1st", false);
	env_match->setImage("Indicator Resources P3 2nd", false);
	env_match->setImage("Indicator Resources P3 3rd", false);
	env_match->setImage("Indicator Resources P3 4th", false);
	env_match->setImage("Indicator Resources P3 1st Odd", false);
	env_match->setImage("Indicator Resources P3 2nd Odd", false);
	env_match->setImage("Indicator Resources P3 3rd Odd", false);

	env_match->setImage("Indicator Resources P4 1st", false);
	env_match->setImage("Indicator Resources P4 2nd", false);
	env_match->setImage("Indicator Resources P4 3rd", false);
	env_match->setImage("Indicator Resources P4 4th", false);
	env_match->setImage("Indicator Resources P4 1st Odd", false);
	env_match->setImage("Indicator Resources P4 2nd Odd", false);
	env_match->setImage("Indicator Resources P4 3rd Odd", false);

	//Hide and reset resource labels

	env_match->setLabel("Label Resources 1st", false);
	env_match->setLabel("Label Resources 2nd", false);
	env_match->setLabel("Label Resources 3rd", false);
	env_match->setLabel("Label Resources 4th", false);
	env_match->setLabel("Label Resources 1st Odd", false);
	env_match->setLabel("Label Resources 2nd Odd", false);
	env_match->setLabel("Label Resources 3rd Odd", false);

	env_match->setText("Label Resources 1st", "0");
	env_match->setText("Label Resources 2nd", "0");
	env_match->setText("Label Resources 3rd", "0");
	env_match->setText("Label Resources 4th", "0");
	env_match->setText("Label Resources 1st Odd", "0");
	env_match->setText("Label Resources 2nd Odd", "0");
	env_match->setText("Label Resources 3rd Odd", "0");
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

	HideTurnMarkers(); //Hide all turn markers

	//Resource indicator widgets
	env_match->addImage("Indicator Resources P1 1st","gui/ingame/resources_player1.jpg",140,700);
	env_match->addImage("Indicator Resources P1 2nd","gui/ingame/resources_player1.jpg",340,700);
	env_match->addImage("Indicator Resources P1 3rd","gui/ingame/resources_player1.jpg",540,700);
	env_match->addImage("Indicator Resources P1 4th","gui/ingame/resources_player1.jpg",740,700);
	env_match->addImage("Indicator Resources P1 1st Odd","gui/ingame/resources_player1.jpg",240,700);
	env_match->addImage("Indicator Resources P1 2nd Odd","gui/ingame/resources_player1.jpg",440,700);
	env_match->addImage("Indicator Resources P1 3rd Odd","gui/ingame/resources_player1.jpg",640,700);

	env_match->addImage("Indicator Resources P2 1st","gui/ingame/resources_player2.jpg",140,700);
	env_match->addImage("Indicator Resources P2 2nd","gui/ingame/resources_player2.jpg",340,700);
	env_match->addImage("Indicator Resources P2 3rd","gui/ingame/resources_player2.jpg",540,700);
	env_match->addImage("Indicator Resources P2 4th","gui/ingame/resources_player2.jpg",740,700);
	env_match->addImage("Indicator Resources P2 1st Odd","gui/ingame/resources_player2.jpg",240,700);
	env_match->addImage("Indicator Resources P2 2nd Odd","gui/ingame/resources_player2.jpg",440,700);
	env_match->addImage("Indicator Resources P2 3rd Odd","gui/ingame/resources_player2.jpg",640,700);

	env_match->addImage("Indicator Resources P3 1st","gui/ingame/resources_player3.jpg",140,700);
	env_match->addImage("Indicator Resources P3 2nd","gui/ingame/resources_player3.jpg",340,700);
	env_match->addImage("Indicator Resources P3 3rd","gui/ingame/resources_player3.jpg",540,700);
	env_match->addImage("Indicator Resources P3 4th","gui/ingame/resources_player3.jpg",740,700);
	env_match->addImage("Indicator Resources P3 1st Odd","gui/ingame/resources_player3.jpg",240,700);
	env_match->addImage("Indicator Resources P3 2nd Odd","gui/ingame/resources_player3.jpg",440,700);
	env_match->addImage("Indicator Resources P3 3rd Odd","gui/ingame/resources_player3.jpg",640,700);

	env_match->addImage("Indicator Resources P4 1st","gui/ingame/resources_player4.jpg",140,700);
	env_match->addImage("Indicator Resources P4 2nd","gui/ingame/resources_player4.jpg",340,700);
	env_match->addImage("Indicator Resources P4 3rd","gui/ingame/resources_player4.jpg",540,700);
	env_match->addImage("Indicator Resources P4 4th","gui/ingame/resources_player4.jpg",740,700);
	env_match->addImage("Indicator Resources P4 1st Odd","gui/ingame/resources_player4.jpg",240,700);
	env_match->addImage("Indicator Resources P4 2nd Odd","gui/ingame/resources_player4.jpg",440,700);
	env_match->addImage("Indicator Resources P4 3rd Odd","gui/ingame/resources_player4.jpg",640,700);

	//Resource labels
	env_match->addLabel("Label Resources 1st", "0", 180,710,240,730);
	env_match->addLabel("Label Resources 2nd", "0", 380,710,440,730);
	env_match->addLabel("Label Resources 3rd", "0", 580,710,640,730);
	env_match->addLabel("Label Resources 4th", "0", 780,710,840,730);
	env_match->addLabel("Label Resources 1st Odd", "0", 280,710,340,730);
	env_match->addLabel("Label Resources 2nd Odd", "0", 480,710,540,730);
	env_match->addLabel("Label Resources 3rd Odd", "0", 680,710,740,730);

	HideResourceIndicators(); //Hide resource indicators

	//Buttons
	env_match->addButton("Button End Turn","gui/ingame/button_end_turn.jpg","gui/ingame/button_end_turn.jpg",750,10,124,35);
	env_match->addButton("Button End Match","gui/ingame/button_end_match.jpg","gui/ingame/button_end_match.jpg",880,10,124,35);

	//Generic messages
	env_match->addImage("Message Sort","gui/ingame/message_sorting_turn_order.jpg",380,330);
	env_match->addImage("Message Turn","gui/ingame/message_turn.jpg",380,360);
	env_match->addImage("Message Player 1","gui/ingame/team_player1.jpg",465,320);
	env_match->addImage("Message Player 2","gui/ingame/team_player2.jpg",465,320);
	env_match->addImage("Message Player 3","gui/ingame/team_player3.jpg",465,320);
	env_match->addImage("Message Player 4","gui/ingame/team_player4.jpg",465,320);

	SetGenericMessage(false, false, 0); //Hide generic messages

	//Victory messages
	env_match->addImage("Message Victory Single","gui/ingame/message_victory.jpg",380,360);
	env_match->addImage("Message Victory Double","gui/ingame/message_victory.jpg",380,400);
	env_match->addImage("Message Victory Triple","gui/ingame/message_victory.jpg",380,440);
	env_match->addImage("Message Victory Quadruple","gui/ingame/message_victory.jpg",380,480);

	env_match->addImage("Message Victory P1 Single","gui/ingame/team_player1.jpg",465,320);
	env_match->addImage("Message Victory P1 Double Top","gui/ingame/team_player1.jpg",465,300);
	env_match->addImage("Message Victory P1 Triple Top","gui/ingame/team_player1.jpg",465,270);
	env_match->addImage("Message Victory P1 Quadruple Top","gui/ingame/team_player1.jpg",465,240);

	env_match->addImage("Message Victory P2 Single","gui/ingame/team_player2.jpg",465,320);
	env_match->addImage("Message Victory P2 Double Top","gui/ingame/team_player2.jpg",465,300);
	env_match->addImage("Message Victory P2 Double Bottom","gui/ingame/team_player2.jpg",465,350);
	env_match->addImage("Message Victory P2 Triple Top","gui/ingame/team_player2.jpg",465,270);
	env_match->addImage("Message Victory P2 Triple Middle","gui/ingame/team_player2.jpg",465,320);
	env_match->addImage("Message Victory P2 Quadruple Middle Top","gui/ingame/team_player2.jpg",465,300);

	env_match->addImage("Message Victory P3 Single","gui/ingame/team_player3.jpg",465,320);
	env_match->addImage("Message Victory P3 Double Top","gui/ingame/team_player3.jpg",465,300);
	env_match->addImage("Message Victory P3 Double Bottom","gui/ingame/team_player3.jpg",465,350);
	env_match->addImage("Message Victory P3 Triple Middle","gui/ingame/team_player3.jpg",465,320);
	env_match->addImage("Message Victory P3 Triple Bottom","gui/ingame/team_player3.jpg",465,370);
	env_match->addImage("Message Victory P3 Quadruple Middle Bottom","gui/ingame/team_player3.jpg",465,360);

	env_match->addImage("Message Victory P4 Single","gui/ingame/team_player4.jpg",465,320);
	env_match->addImage("Message Victory P4 Double Bottom","gui/ingame/team_player4.jpg",465,350);
	env_match->addImage("Message Victory P4 Triple Bottom","gui/ingame/team_player4.jpg",465,370);
	env_match->addImage("Message Victory P4 Quadruple Bottom","gui/ingame/team_player4.jpg",465,420);

	HideVictoryMessage(); //Hide all victory messages
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

void PrimeGUIManager::ManageGUIMatchScreen(int turn, PrimePlayState playState)
{
	//Update turn count
	SetTurnCount(true, turn);
	
	//Show player indicator according to turn
	SetPlayerIndicator(true, playState.turnPlayer);

	//Show turn markers in their correct order
	ShowTurnMarkers(playState);

	//Show resource indicators according to active players and play order
	ShowResourceIndicators(playState.playersActive, playState.player1, playState.player2, playState.player3, playState.player4);

	//Show a generic match message
	//SetGenericMessage(SORT_MESSAGE, false, 0);
	//SetGenericMessage(false, TURN_MESSAGE, playState.turnPlayer);

	//Show victory message
	//ShowVictoryMessage(playState);
}