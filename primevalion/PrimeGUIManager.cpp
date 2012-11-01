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

void PrimeGUIManager::EnableEndTurnButton(bool enable)
{
	//Swap enabled button for its unclickable
	//disabled image, or vice-versa.

	env_match->setButton(BUTTON_END_TURN, enable);
	env_match->setImage(IMAGE_END_TURN_DISABLED, !enable);
}

void PrimeGUIManager::EnableEndMatchButton(bool enable)
{
	//Swap enabled button for its unclickable
	//disabled image, or vice-versa.
	
	env_match->setButton(BUTTON_END_MATCH, enable);
	env_match->setImage(IMAGE_END_MATCH_DISABLED, !enable);
}

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
		env_match->setLabel(LABEL_TURN_COUNT, true);
		env_match->setText(LABEL_TURN_COUNT, (char*)turnCount.c_str());
	}

	else if (!show)
	{
		//Hide and reset turn counter
		env_match->setLabel(LABEL_TURN_COUNT, false);
		env_match->setText(LABEL_TURN_COUNT, "1");
	}
}

void PrimeGUIManager::SetPlayerIndicator(bool show, int turnPlayer)
{
	if (show)
	{
		//If this is player 1's turn...
		if (turnPlayer == 1)
		{
			env_match->setImage(INDICATOR_TURN_PLAYER_1, true);
			env_match->setImage(INDICATOR_TURN_PLAYER_2, false);
			env_match->setImage(INDICATOR_TURN_PLAYER_3, false);
			env_match->setImage(INDICATOR_TURN_PLAYER_4, false);
		}

		//If this is player 2's turn...
		else if (turnPlayer == 2)
		{
			env_match->setImage(INDICATOR_TURN_PLAYER_1, false);
			env_match->setImage(INDICATOR_TURN_PLAYER_2, true);
			env_match->setImage(INDICATOR_TURN_PLAYER_3, false);
			env_match->setImage(INDICATOR_TURN_PLAYER_4, false);
		}

		//If this is player 3's turn...
		else if (turnPlayer == 3)
		{
			env_match->setImage(INDICATOR_TURN_PLAYER_1, false);
			env_match->setImage(INDICATOR_TURN_PLAYER_2, false);
			env_match->setImage(INDICATOR_TURN_PLAYER_3, true);
			env_match->setImage(INDICATOR_TURN_PLAYER_4, false);
		}

		//If this is player 4's turn...
		else if (turnPlayer == 4)
		{
			env_match->setImage(INDICATOR_TURN_PLAYER_1, false);
			env_match->setImage(INDICATOR_TURN_PLAYER_2, false);
			env_match->setImage(INDICATOR_TURN_PLAYER_3, false);
			env_match->setImage(INDICATOR_TURN_PLAYER_4, true);
		}
	}

	else if (!show)
	{
		//Hide player indicators
		env_match->setImage(INDICATOR_TURN_PLAYER_1, false);
		env_match->setImage(INDICATOR_TURN_PLAYER_2, false);
		env_match->setImage(INDICATOR_TURN_PLAYER_3, false);
		env_match->setImage(INDICATOR_TURN_PLAYER_4, false);
	}
}

void PrimeGUIManager::SetGenericMessage(bool sortMessage, bool turnMessage, int player)
{
	if (sortMessage)
	{
		//Show "Sorting turn order..." message
		env_match->setImage(MESSAGE_SORT, true);
	}

	else if (turnMessage)
	{
		//Show the correct "Player X Turn" message

		env_match->setImage(MESSAGE_TURN, true);

		if (player == 1) env_match->setImage(MESSAGE_PLAYER_1, true);
		else if (player == 2) env_match->setImage(MESSAGE_PLAYER_2, true);
		else if (player == 3) env_match->setImage(MESSAGE_PLAYER_3, true);
		else if (player == 4) env_match->setImage(MESSAGE_PLAYER_4, true);
	}

	else
	{
		//Hide all messages
		env_match->setImage(MESSAGE_SORT, false);
		env_match->setImage(MESSAGE_TURN, false);
		env_match->setImage(MESSAGE_PLAYER_1, false);
		env_match->setImage(MESSAGE_PLAYER_2, false);
		env_match->setImage(MESSAGE_PLAYER_3, false);
		env_match->setImage(MESSAGE_PLAYER_4, false);
	}
}

void PrimeGUIManager::ShowVictoryMessage(PrimePlayState* playState)
{
	int playersVictorious = 0;

	//Count how many players won the match (Draw)
	if (playState->player1.isVictorious) playersVictorious++;
	if (playState->player2.isVictorious) playersVictorious++;
	if (playState->player3.isVictorious) playersVictorious++;
	if (playState->player4.isVictorious) playersVictorious++;

	//Check victory condition and display messages accordingly

	//One winner...
	if (playersVictorious == 1)
	{
		env_match->setImage(MESSAGE_VICTORY_SINGLE, true);

		if (playState->player1.isVictorious) env_match->setImage(MESSAGE_VICTORY_P1_SINGLE, true);
		else if (playState->player2.isVictorious) env_match->setImage(MESSAGE_VICTORY_P2_SINGLE, true);
		else if (playState->player3.isVictorious) env_match->setImage(MESSAGE_VICTORY_P3_SINGLE, true);
		else if (playState->player4.isVictorious) env_match->setImage(MESSAGE_VICTORY_P4_SINGLE, true);
	}

	//Two winners...
	if (playersVictorious == 2)
	{
		env_match->setImage(MESSAGE_VICTORY_DOUBLE, true);

		if (playState->player1.isVictorious)
		{
			env_match->setImage(MESSAGE_VICTORY_P1_DOUBLE_TOP, true);
			if (playState->player2.isVictorious) env_match->setImage(MESSAGE_VICTORY_P2_DOUBLE_BOTTOM, true);
			else if (playState->player3.isVictorious) env_match->setImage(MESSAGE_VICTORY_P3_DOUBLE_BOTTOM, true);
			else if (playState->player4.isVictorious) env_match->setImage(MESSAGE_VICTORY_P4_DOUBLE_BOTTOM, true);
		}

		else if (playState->player2.isVictorious)
		{
			env_match->setImage(MESSAGE_VICTORY_P2_DOUBLE_TOP, true);
			if (playState->player3.isVictorious) env_match->setImage(MESSAGE_VICTORY_P3_DOUBLE_BOTTOM, true);
			else if (playState->player4.isVictorious) env_match->setImage(MESSAGE_VICTORY_P4_DOUBLE_BOTTOM, true);
		}

		else if (playState->player3.isVictorious)
		{
			env_match->setImage(MESSAGE_VICTORY_P3_DOUBLE_TOP, true);
			env_match->setImage(MESSAGE_VICTORY_P4_DOUBLE_BOTTOM, true);
		}
	}

	//Three winners...
	if (playersVictorious == 3)
	{
		env_match->setImage(MESSAGE_VICTORY_TRIPLE, true);

		if (playState->player1.isVictorious)
		{
			env_match->setImage(MESSAGE_VICTORY_P1_TRIPLE_TOP, true);
			
			if (playState->player2.isVictorious)
			{
				env_match->setImage(MESSAGE_VICTORY_P2_TRIPLE_MIDDLE, true);
				if (playState->player3.isVictorious) env_match->setImage(MESSAGE_VICTORY_P3_TRIPLE_BOTTOM, true);
				else if (playState->player4.isVictorious) env_match->setImage(MESSAGE_VICTORY_P4_TRIPLE_BOTTOM, true);
			}

			else if (playState->player3.isVictorious)
			{
				env_match->setImage(MESSAGE_VICTORY_P3_TRIPLE_MIDDLE, true);
				env_match->setImage(MESSAGE_VICTORY_P4_TRIPLE_BOTTOM, true);
			}
		}

		else if (playState->player2.isVictorious)
		{
			env_match->setImage(MESSAGE_VICTORY_P2_TRIPLE_TOP, true);
			env_match->setImage(MESSAGE_VICTORY_P3_TRIPLE_MIDDLE, true);
			env_match->setImage(MESSAGE_VICTORY_P4_TRIPLE_BOTTOM, true);
		}
	}

	//Four winners...
	if (playersVictorious == 4)
	{
		env_match->setImage(MESSAGE_VICTORY_QUADRUPLE, true);
		env_match->setImage(MESSAGE_VICTORY_P1_QUADRUPLE_TOP, true);
		env_match->setImage(MESSAGE_VICTORY_P2_QUADRUPLE_MIDDLE_TOP, true);
		env_match->setImage(MESSAGE_VICTORY_P3_QUADRUPLE_MIDDLE_BOTTOM, true);
		env_match->setImage(MESSAGE_VICTORY_P4_QUADRUPLE_BOTTOM, true);
	}
}

void PrimeGUIManager::HideVictoryMessage()
{
	//Hide all victory messages
	env_match->setImage(MESSAGE_VICTORY_SINGLE, false);
	env_match->setImage(MESSAGE_VICTORY_DOUBLE, false);
	env_match->setImage(MESSAGE_VICTORY_TRIPLE, false);
	env_match->setImage(MESSAGE_VICTORY_QUADRUPLE, false);

	env_match->setImage(MESSAGE_VICTORY_P1_SINGLE, false);
	env_match->setImage(MESSAGE_VICTORY_P1_DOUBLE_TOP, false);
	env_match->setImage(MESSAGE_VICTORY_P1_TRIPLE_TOP, false);
	env_match->setImage(MESSAGE_VICTORY_P1_QUADRUPLE_TOP, false);

	env_match->setImage(MESSAGE_VICTORY_P2_SINGLE, false);
	env_match->setImage(MESSAGE_VICTORY_P2_DOUBLE_TOP, false);
	env_match->setImage(MESSAGE_VICTORY_P2_DOUBLE_BOTTOM, false);
	env_match->setImage(MESSAGE_VICTORY_P2_TRIPLE_TOP, false);
	env_match->setImage(MESSAGE_VICTORY_P2_TRIPLE_MIDDLE, false);
	env_match->setImage(MESSAGE_VICTORY_P2_QUADRUPLE_MIDDLE_TOP, false);
	
	env_match->setImage(MESSAGE_VICTORY_P3_SINGLE, false);
	env_match->setImage(MESSAGE_VICTORY_P3_DOUBLE_TOP, false);
	env_match->setImage(MESSAGE_VICTORY_P3_DOUBLE_BOTTOM, false);
	env_match->setImage(MESSAGE_VICTORY_P3_TRIPLE_MIDDLE, false);
	env_match->setImage(MESSAGE_VICTORY_P3_TRIPLE_BOTTOM, false);
	env_match->setImage(MESSAGE_VICTORY_P3_QUADRUPLE_MIDDLE_BOTTOM, false);

	env_match->setImage(MESSAGE_VICTORY_P4_SINGLE, false);
	env_match->setImage(MESSAGE_VICTORY_P4_DOUBLE_BOTTOM, false);
	env_match->setImage(MESSAGE_VICTORY_P4_TRIPLE_BOTTOM, false);
	env_match->setImage(MESSAGE_VICTORY_P4_QUADRUPLE_BOTTOM, false);
}

void PrimeGUIManager::ShowTurnMarkers(PrimePlayState* playState)
{
	//Get turn order
	int p1 = playState->player1.assignedTurn;
	int p2 = playState->player2.assignedTurn;
	int p3 = playState->player3.assignedTurn;
	int p4 = playState->player4.assignedTurn;

	//Show turn markers according to player turn order
	switch (p1)
	{
		case 1: { env_match->setImage(INDICATOR_TURN_MARKER_P1_1ST, true); break; }
		case 2: { env_match->setImage(INDICATOR_TURN_MARKER_P1_2ND, true); break; }
		case 3: { env_match->setImage(INDICATOR_TURN_MARKER_P1_3RD, true); break; }
		case 4: { env_match->setImage(INDICATOR_TURN_MARKER_P1_4TH, true); break; }
	}

	switch (p2)
	{
		case 1: { env_match->setImage(INDICATOR_TURN_MARKER_P2_1ST, true); break; }
		case 2: { env_match->setImage(INDICATOR_TURN_MARKER_P2_2ND, true); break; }
		case 3: { env_match->setImage(INDICATOR_TURN_MARKER_P2_3RD, true); break; }
		case 4: { env_match->setImage(INDICATOR_TURN_MARKER_P2_4TH, true); break; }
	}

	switch (p3)
	{
		case 1: { env_match->setImage(INDICATOR_TURN_MARKER_P3_1ST, true); break; }
		case 2: { env_match->setImage(INDICATOR_TURN_MARKER_P3_2ND, true); break; }
		case 3: { env_match->setImage(INDICATOR_TURN_MARKER_P3_3RD, true); break; }
		case 4: { env_match->setImage(INDICATOR_TURN_MARKER_P3_4TH, true); break; }
	}

	switch (p4)
	{
		case 1: { env_match->setImage(INDICATOR_TURN_MARKER_P4_1ST, true); break; }
		case 2: { env_match->setImage(INDICATOR_TURN_MARKER_P4_2ND, true); break; }
		case 3: { env_match->setImage(INDICATOR_TURN_MARKER_P4_3RD, true); break; }
		case 4: { env_match->setImage(INDICATOR_TURN_MARKER_P4_4TH, true); break; }
	}
}

void PrimeGUIManager::HideTurnMarkers()
{
	//Hide all turn markers
	env_match->setImage(INDICATOR_TURN_MARKER_P1_1ST, false);
	env_match->setImage(INDICATOR_TURN_MARKER_P1_2ND, false);
	env_match->setImage(INDICATOR_TURN_MARKER_P1_3RD, false);
	env_match->setImage(INDICATOR_TURN_MARKER_P1_4TH, false);

	env_match->setImage(INDICATOR_TURN_MARKER_P2_1ST, false);
	env_match->setImage(INDICATOR_TURN_MARKER_P2_2ND, false);
	env_match->setImage(INDICATOR_TURN_MARKER_P2_3RD, false);
	env_match->setImage(INDICATOR_TURN_MARKER_P2_4TH, false);

	env_match->setImage(INDICATOR_TURN_MARKER_P3_1ST, false);
	env_match->setImage(INDICATOR_TURN_MARKER_P3_2ND, false);
	env_match->setImage(INDICATOR_TURN_MARKER_P3_3RD, false);
	env_match->setImage(INDICATOR_TURN_MARKER_P3_4TH, false);

	env_match->setImage(INDICATOR_TURN_MARKER_P4_1ST, false);
	env_match->setImage(INDICATOR_TURN_MARKER_P4_2ND, false);
	env_match->setImage(INDICATOR_TURN_MARKER_P4_3RD, false);
	env_match->setImage(INDICATOR_TURN_MARKER_P4_4TH, false);
}

void PrimeGUIManager::UpdateMatchIndicator(bool show, irr::s32 indicator, irr::s32 label, std::string counter)
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

			if (p1.assignedTurn == 1) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P1_2ND, LABEL_RESOURCES_2ND, resourceCount);
			else if (p1.assignedTurn == 2) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P1_3RD, LABEL_RESOURCES_3RD, resourceCount);
		}

		if (p2.isActive)
		{
			resourceCount = convertP2.str();

			if (p2.assignedTurn == 1) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P2_2ND, LABEL_RESOURCES_2ND, resourceCount);
			else if (p2.assignedTurn == 2) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P2_3RD, LABEL_RESOURCES_3RD, resourceCount);
		}

		if (p3.isActive)
		{
			resourceCount = convertP3.str();

			if (p3.assignedTurn == 1) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P3_2ND, LABEL_RESOURCES_2ND, resourceCount);
			else if (p3.assignedTurn == 2) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P3_3RD, LABEL_RESOURCES_3RD, resourceCount);
		}

		if (p4.isActive)
		{
			resourceCount = convertP4.str();

			if (p4.assignedTurn == 1) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P4_2ND, LABEL_RESOURCES_2ND, resourceCount);
			else if (p4.assignedTurn == 2) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P4_3RD, LABEL_RESOURCES_3RD, resourceCount);
		}
	}

	//Three active players...
	else if (playersActive == 3)
	{
		if (p1.isActive)
		{
			resourceCount = convertP1.str();

			if (p1.assignedTurn == 1) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P1_1ST_ODD, LABEL_RESOURCES_1ST_ODD, resourceCount);
			else if (p1.assignedTurn == 2) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P1_2ND_ODD, LABEL_RESOURCES_2ND_ODD, resourceCount);
			else if (p1.assignedTurn == 3) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P1_3RD_ODD, LABEL_RESOURCES_3RD_ODD, resourceCount);
		}

		if (p2.isActive)
		{
			resourceCount = convertP2.str();

			if (p2.assignedTurn == 1) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P2_1ST_ODD, LABEL_RESOURCES_1ST_ODD, resourceCount);
			else if (p2.assignedTurn == 2) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P2_2ND_ODD, LABEL_RESOURCES_2ND_ODD, resourceCount);
			else if (p2.assignedTurn == 3) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P2_3RD_ODD, LABEL_RESOURCES_3RD_ODD, resourceCount);
		}

		if (p3.isActive)
		{
			resourceCount = convertP3.str();

			if (p3.assignedTurn == 1) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P3_1ST_ODD, LABEL_RESOURCES_1ST_ODD, resourceCount);
			else if (p3.assignedTurn == 2) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P3_2ND_ODD, LABEL_RESOURCES_2ND_ODD, resourceCount);
			else if (p3.assignedTurn == 3) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P3_3RD_ODD, LABEL_RESOURCES_3RD_ODD, resourceCount);
		}

		if (p4.isActive)
		{
			resourceCount = convertP4.str();

			if (p4.assignedTurn == 1)  UpdateMatchIndicator(true, INDICATOR_RESOURCES_P4_1ST_ODD, LABEL_RESOURCES_1ST_ODD, resourceCount);
			else if (p4.assignedTurn == 2) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P4_2ND_ODD, LABEL_RESOURCES_2ND_ODD, resourceCount);
			else if (p4.assignedTurn == 3) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P4_3RD_ODD, LABEL_RESOURCES_3RD_ODD, resourceCount);
		}
	}

	//Four active players...
	else if (playersActive == 4)
	{
		if (p1.isActive)
		{
			resourceCount = convertP1.str();

			if (p1.assignedTurn == 1) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P1_1ST, LABEL_RESOURCES_1ST, resourceCount);
			else if (p1.assignedTurn == 2) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P1_2ND, LABEL_RESOURCES_2ND, resourceCount);
			else if (p1.assignedTurn == 3) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P1_3RD, LABEL_RESOURCES_3RD, resourceCount);
			else if (p1.assignedTurn == 4) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P1_4TH, LABEL_RESOURCES_4TH, resourceCount);
		}

		if (p2.isActive)
		{
			resourceCount = convertP2.str();

			if (p2.assignedTurn == 1) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P2_1ST, LABEL_RESOURCES_1ST, resourceCount);
			else if (p2.assignedTurn == 2) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P2_2ND, LABEL_RESOURCES_2ND, resourceCount);
			else if (p2.assignedTurn == 3) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P2_3RD, LABEL_RESOURCES_3RD, resourceCount);
			else if (p2.assignedTurn == 4) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P2_4TH, LABEL_RESOURCES_4TH, resourceCount);
		}

		if (p3.isActive)
		{
			resourceCount = convertP3.str();

			if (p3.assignedTurn == 1) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P3_1ST, LABEL_RESOURCES_1ST, resourceCount);
			else if (p3.assignedTurn == 2) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P3_2ND, LABEL_RESOURCES_2ND, resourceCount);
			else if (p3.assignedTurn == 3) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P3_3RD, LABEL_RESOURCES_3RD, resourceCount);
			else if (p3.assignedTurn == 4) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P3_4TH, LABEL_RESOURCES_4TH, resourceCount);
		}

		if (p4.isActive)
		{
			resourceCount = convertP4.str();

			if (p4.assignedTurn == 1) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P4_1ST, LABEL_RESOURCES_1ST, resourceCount);
			else if (p4.assignedTurn == 2) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P4_2ND, LABEL_RESOURCES_2ND, resourceCount);
			else if (p4.assignedTurn == 3) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P4_3RD, LABEL_RESOURCES_3RD, resourceCount);
			else if (p4.assignedTurn == 4) UpdateMatchIndicator(true, INDICATOR_RESOURCES_P4_4TH, LABEL_RESOURCES_4TH, resourceCount);
		}
	}
}

void PrimeGUIManager::HideResourceIndicators()
{
	//Hide all resource indicators

	env_match->setImage(INDICATOR_RESOURCES_P1_1ST, false);
	env_match->setImage(INDICATOR_RESOURCES_P1_2ND, false);
	env_match->setImage(INDICATOR_RESOURCES_P1_3RD, false);
	env_match->setImage(INDICATOR_RESOURCES_P1_4TH, false);
	env_match->setImage(INDICATOR_RESOURCES_P1_1ST_ODD, false);
	env_match->setImage(INDICATOR_RESOURCES_P1_2ND_ODD, false);
	env_match->setImage(INDICATOR_RESOURCES_P1_3RD_ODD, false);

	env_match->setImage(INDICATOR_RESOURCES_P2_1ST, false);
	env_match->setImage(INDICATOR_RESOURCES_P2_2ND, false);
	env_match->setImage(INDICATOR_RESOURCES_P2_3RD, false);
	env_match->setImage(INDICATOR_RESOURCES_P2_4TH, false);
	env_match->setImage(INDICATOR_RESOURCES_P2_1ST_ODD, false);
	env_match->setImage(INDICATOR_RESOURCES_P2_2ND_ODD, false);
	env_match->setImage(INDICATOR_RESOURCES_P2_3RD_ODD, false);

	env_match->setImage(INDICATOR_RESOURCES_P3_1ST, false);
	env_match->setImage(INDICATOR_RESOURCES_P3_2ND, false);
	env_match->setImage(INDICATOR_RESOURCES_P3_3RD, false);
	env_match->setImage(INDICATOR_RESOURCES_P3_4TH, false);
	env_match->setImage(INDICATOR_RESOURCES_P3_1ST_ODD, false);
	env_match->setImage(INDICATOR_RESOURCES_P3_2ND_ODD, false);
	env_match->setImage(INDICATOR_RESOURCES_P3_3RD_ODD, false);

	env_match->setImage(INDICATOR_RESOURCES_P4_1ST, false);
	env_match->setImage(INDICATOR_RESOURCES_P4_2ND, false);
	env_match->setImage(INDICATOR_RESOURCES_P4_3RD, false);
	env_match->setImage(INDICATOR_RESOURCES_P4_4TH, false);
	env_match->setImage(INDICATOR_RESOURCES_P4_1ST_ODD, false);
	env_match->setImage(INDICATOR_RESOURCES_P4_2ND_ODD, false);
	env_match->setImage(INDICATOR_RESOURCES_P4_3RD_ODD, false);

	//Hide and reset resource labels

	env_match->setLabel(LABEL_RESOURCES_1ST, false);
	env_match->setLabel(LABEL_RESOURCES_2ND, false);
	env_match->setLabel(LABEL_RESOURCES_3RD, false);
	env_match->setLabel(LABEL_RESOURCES_4TH, false);
	env_match->setLabel(LABEL_RESOURCES_1ST_ODD, false);
	env_match->setLabel(LABEL_RESOURCES_2ND_ODD, false);
	env_match->setLabel(LABEL_RESOURCES_3RD_ODD, false);

	env_match->setText(LABEL_RESOURCES_1ST, "0");
	env_match->setText(LABEL_RESOURCES_2ND, "0");
	env_match->setText(LABEL_RESOURCES_3RD, "0");
	env_match->setText(LABEL_RESOURCES_4TH, "0");
	env_match->setText(LABEL_RESOURCES_1ST_ODD, "0");
	env_match->setText(LABEL_RESOURCES_2ND_ODD, "0");
	env_match->setText(LABEL_RESOURCES_3RD_ODD, "0");
}

void PrimeGUIManager::ShowPlayerIndicators(PrimeTeam* p1, PrimeTeam* p2, PrimeTeam* p3, PrimeTeam* p4)
{
	//Show or hide player ON/OFF indicators

	if (p1->isActive) { env_title->setImage(INDICATOR_PLAYER_1_ON, true); env_title->setImage(INDICATOR_PLAYER_1_OFF, false); }
	else if (!p1->isActive) { env_title->setImage(INDICATOR_PLAYER_1_ON, false); env_title->setImage(INDICATOR_PLAYER_1_OFF, true); }

	if (p2->isActive) { env_title->setImage(INDICATOR_PLAYER_2_ON, true); env_title->setImage(INDICATOR_PLAYER_2_OFF, false); }
	else if (!p2->isActive) { env_title->setImage(INDICATOR_PLAYER_2_ON, false); env_title->setImage(INDICATOR_PLAYER_2_OFF, true); }

	if (p3->isActive) { env_title->setImage(INDICATOR_PLAYER_3_ON, true); env_title->setImage(INDICATOR_PLAYER_3_OFF, false); }
	else if (!p3->isActive) { env_title->setImage(INDICATOR_PLAYER_3_ON, false); env_title->setImage(INDICATOR_PLAYER_3_OFF, true); }

	if (p4->isActive) { env_title->setImage(INDICATOR_PLAYER_4_ON, true); env_title->setImage(INDICATOR_PLAYER_4_OFF, false); }
	else if (!p4->isActive) { env_title->setImage(INDICATOR_PLAYER_4_ON, false); env_title->setImage(INDICATOR_PLAYER_4_OFF, true); }

}

void PrimeGUIManager::ShowPlayerOnOffButtons(PrimeTeam* p1, PrimeTeam* p2, PrimeTeam* p3, PrimeTeam* p4)
{
	//Hide and show activation/deactivation buttons, based on active teams

	if (p1->isActive) { env_title->setButton(BUTTON_PLAYER_1_ACTIVATE, false); env_title->setButton(BUTTON_PLAYER_1_DEACTIVATE, true); }
	else if (!p1->isActive) { env_title->setButton(BUTTON_PLAYER_1_ACTIVATE, true); env_title->setButton(BUTTON_PLAYER_1_DEACTIVATE, false); }

	if (p2->isActive) { env_title->setButton(BUTTON_PLAYER_2_ACTIVATE, false); env_title->setButton(BUTTON_PLAYER_2_DEACTIVATE, true); }
	else if (!p2->isActive) { env_title->setButton(BUTTON_PLAYER_2_ACTIVATE, true); env_title->setButton(BUTTON_PLAYER_2_DEACTIVATE, false); }

	if (p3->isActive) { env_title->setButton(BUTTON_PLAYER_3_ACTIVATE, false); env_title->setButton(BUTTON_PLAYER_3_DEACTIVATE, true); }
	else if (!p3->isActive) { env_title->setButton(BUTTON_PLAYER_3_ACTIVATE, true); env_title->setButton(BUTTON_PLAYER_3_DEACTIVATE, false); }

	if (p4->isActive) { env_title->setButton(BUTTON_PLAYER_4_ACTIVATE, false); env_title->setButton(BUTTON_PLAYER_4_DEACTIVATE, true); }
	else if (!p4->isActive) { env_title->setButton(BUTTON_PLAYER_4_ACTIVATE, true); env_title->setButton(BUTTON_PLAYER_4_DEACTIVATE, false); }
}

void PrimeGUIManager::ShowRaces(PrimeTeam* p1, PrimeTeam* p2, PrimeTeam* p3, PrimeTeam* p4)
{
	//By default, hide all selected, unselected and
	//unselectable race images and buttons
	
	HideSelectedRaces();
	HideUnselectedRaces();
	HideUnselectableRaces();

	//For ACTIVE players, show all of their unselected race buttons,
	//then show their selected race image and hide their respective
	//unselected race button.

	//Player 1...
	if (p1->isActive)
	{
		ShowUnselectedRaces(p1->idx);

		if (p1->assignedRace == KOBOLD) { env_title->setImage(IMAGE_PLAYER_1_KOBOLD, true);
										  env_title->setButton(BUTTON_UNSELECTED_KOBOLD_P1, false); }
		else if (p1->assignedRace == GNOLL) { env_title->setImage(IMAGE_PLAYER_1_GNOLL, true);
											  env_title->setButton(BUTTON_UNSELECTED_GNOLL_P1, false); }
		else if (p1->assignedRace == TROLL) { env_title->setImage(IMAGE_PLAYER_1_TROLL, true);
											  env_title->setButton(BUTTON_UNSELECTED_TROLL_P1, false); }
		else if (p1->assignedRace == HOG) { env_title->setImage(IMAGE_PLAYER_1_HOG, true);
										    env_title->setButton(BUTTON_UNSELECTED_HOG_P1, false); }
	}

	//Player 2...
	if (p2->isActive)
	{
		ShowUnselectedRaces(p2->idx);

		if (p2->assignedRace == KOBOLD) { env_title->setImage(IMAGE_PLAYER_2_KOBOLD, true);
										  env_title->setButton(BUTTON_UNSELECTED_KOBOLD_P2, false); }
		else if (p2->assignedRace == GNOLL) { env_title->setImage(IMAGE_PLAYER_2_GNOLL, true);
											  env_title->setButton(BUTTON_UNSELECTED_GNOLL_P2, false); }
		else if (p2->assignedRace == TROLL) { env_title->setImage(IMAGE_PLAYER_2_TROLL, true);
											  env_title->setButton(BUTTON_UNSELECTED_TROLL_P2, false); }
		else if (p2->assignedRace == HOG) { env_title->setImage(IMAGE_PLAYER_2_HOG, true);
										    env_title->setButton(BUTTON_UNSELECTED_HOG_P2, false); }
	}

	//Player 3...
	if (p3->isActive)
	{
		ShowUnselectedRaces(p3->idx);

		if (p3->assignedRace == KOBOLD) { env_title->setImage(IMAGE_PLAYER_3_KOBOLD, true);
										  env_title->setButton(BUTTON_UNSELECTED_KOBOLD_P3, false); }
		else if (p3->assignedRace == GNOLL) { env_title->setImage(IMAGE_PLAYER_3_GNOLL, true);
											  env_title->setButton(BUTTON_UNSELECTED_GNOLL_P3, false); }
		else if (p3->assignedRace == TROLL) { env_title->setImage(IMAGE_PLAYER_3_TROLL, true);
											  env_title->setButton(BUTTON_UNSELECTED_TROLL_P3, false); }
		else if (p3->assignedRace == HOG) { env_title->setImage(IMAGE_PLAYER_3_HOG, true);
										    env_title->setButton(BUTTON_UNSELECTED_HOG_P3, false); }
	}

	//Player 4...
	if (p4->isActive)
	{
		ShowUnselectedRaces(p4->idx);

		if (p4->assignedRace == KOBOLD) { env_title->setImage(IMAGE_PLAYER_4_KOBOLD, true);
										  env_title->setButton(BUTTON_UNSELECTED_KOBOLD_P4, false); }
		else if (p4->assignedRace == GNOLL) { env_title->setImage(IMAGE_PLAYER_4_GNOLL, true);
											  env_title->setButton(BUTTON_UNSELECTED_GNOLL_P4, false); }
		else if (p4->assignedRace == TROLL) { env_title->setImage(IMAGE_PLAYER_4_TROLL, true);
											  env_title->setButton(BUTTON_UNSELECTED_TROLL_P4, false); }
		else if (p4->assignedRace == HOG) { env_title->setImage(IMAGE_PLAYER_4_HOG, true);
										    env_title->setButton(BUTTON_UNSELECTED_HOG_P4, false); }
	}

	//For INACTIVE players, replace unselected race buttons
	//with unselectable race images.

	if (!p1->isActive) ShowUnselectableRaces(p1->idx);
	if (!p2->isActive) ShowUnselectableRaces(p2->idx);
	if (!p3->isActive) ShowUnselectableRaces(p3->idx);
	if (!p4->isActive) ShowUnselectableRaces(p4->idx);
}

void PrimeGUIManager::ShowUnselectedRaces(int player)
{
	//Show a player's unselected race buttons

	if (player == 1)
	{
		env_title->setButton(BUTTON_UNSELECTED_KOBOLD_P1, true);
		env_title->setButton(BUTTON_UNSELECTED_GNOLL_P1, true);
		env_title->setButton(BUTTON_UNSELECTED_TROLL_P1, true);
		env_title->setButton(BUTTON_UNSELECTED_HOG_P1, true);
	}

	else if (player == 2)
	{
		env_title->setButton(BUTTON_UNSELECTED_KOBOLD_P2, true);
		env_title->setButton(BUTTON_UNSELECTED_GNOLL_P2, true);
		env_title->setButton(BUTTON_UNSELECTED_TROLL_P2, true);
		env_title->setButton(BUTTON_UNSELECTED_HOG_P2, true);
	}

	else if (player == 3)
	{
		env_title->setButton(BUTTON_UNSELECTED_KOBOLD_P3, true);
		env_title->setButton(BUTTON_UNSELECTED_GNOLL_P3, true);
		env_title->setButton(BUTTON_UNSELECTED_TROLL_P3, true);
		env_title->setButton(BUTTON_UNSELECTED_HOG_P3, true);
	}

	else if (player == 4)
	{
		env_title->setButton(BUTTON_UNSELECTED_KOBOLD_P4, true);
		env_title->setButton(BUTTON_UNSELECTED_GNOLL_P4, true);
		env_title->setButton(BUTTON_UNSELECTED_TROLL_P4, true);
		env_title->setButton(BUTTON_UNSELECTED_HOG_P4, true);
	}
}

void PrimeGUIManager::ShowUnselectableRaces(int player)
{
	//Show a player's unselectable race images

	if (player == 1)
	{
		env_title->setImage(IMAGE_UNSELECTABLE_KOBOLD_P1, true);
		env_title->setImage(IMAGE_UNSELECTABLE_GNOLL_P1, true);
		env_title->setImage(IMAGE_UNSELECTABLE_TROLL_P1, true);
		env_title->setImage(IMAGE_UNSELECTABLE_HOG_P1, true);
	}

	else if (player == 2)
	{
		env_title->setImage(IMAGE_UNSELECTABLE_KOBOLD_P2, true);
		env_title->setImage(IMAGE_UNSELECTABLE_GNOLL_P2, true);
		env_title->setImage(IMAGE_UNSELECTABLE_TROLL_P2, true);
		env_title->setImage(IMAGE_UNSELECTABLE_HOG_P2, true);
	}

	else if (player == 3)
	{
		env_title->setImage(IMAGE_UNSELECTABLE_KOBOLD_P3, true);
		env_title->setImage(IMAGE_UNSELECTABLE_GNOLL_P3, true);
		env_title->setImage(IMAGE_UNSELECTABLE_TROLL_P3, true);
		env_title->setImage(IMAGE_UNSELECTABLE_HOG_P3, true);
	}

	else if (player == 4)
	{
		env_title->setImage(IMAGE_UNSELECTABLE_KOBOLD_P4, true);
		env_title->setImage(IMAGE_UNSELECTABLE_GNOLL_P4, true);
		env_title->setImage(IMAGE_UNSELECTABLE_TROLL_P4, true);
		env_title->setImage(IMAGE_UNSELECTABLE_HOG_P4, true);
	}
}

void PrimeGUIManager::HideUnselectableRaces()
{
	//Hide all players' unselectable images

	env_title->setImage(IMAGE_UNSELECTABLE_KOBOLD_P1, false);
	env_title->setImage(IMAGE_UNSELECTABLE_KOBOLD_P2, false);
	env_title->setImage(IMAGE_UNSELECTABLE_KOBOLD_P3, false);
	env_title->setImage(IMAGE_UNSELECTABLE_KOBOLD_P4, false);

	env_title->setImage(IMAGE_UNSELECTABLE_GNOLL_P1, false);
	env_title->setImage(IMAGE_UNSELECTABLE_GNOLL_P2, false);
	env_title->setImage(IMAGE_UNSELECTABLE_GNOLL_P3, false);
	env_title->setImage(IMAGE_UNSELECTABLE_GNOLL_P4, false);

	env_title->setImage(IMAGE_UNSELECTABLE_TROLL_P1, false);
	env_title->setImage(IMAGE_UNSELECTABLE_TROLL_P2, false);
	env_title->setImage(IMAGE_UNSELECTABLE_TROLL_P3, false);
	env_title->setImage(IMAGE_UNSELECTABLE_TROLL_P4, false);

	env_title->setImage(IMAGE_UNSELECTABLE_HOG_P1, false);
	env_title->setImage(IMAGE_UNSELECTABLE_HOG_P2, false);
	env_title->setImage(IMAGE_UNSELECTABLE_HOG_P3, false);
	env_title->setImage(IMAGE_UNSELECTABLE_HOG_P4, false);
}

void PrimeGUIManager::HideUnselectedRaces()
{
	//Hide all players' unselected race buttons

	env_title->setButton(BUTTON_UNSELECTED_KOBOLD_P1, false);
	env_title->setButton(BUTTON_UNSELECTED_KOBOLD_P2, false);
	env_title->setButton(BUTTON_UNSELECTED_KOBOLD_P3, false);
	env_title->setButton(BUTTON_UNSELECTED_KOBOLD_P4, false);

	env_title->setButton(BUTTON_UNSELECTED_GNOLL_P1, false);
	env_title->setButton(BUTTON_UNSELECTED_GNOLL_P2, false);
	env_title->setButton(BUTTON_UNSELECTED_GNOLL_P3, false);
	env_title->setButton(BUTTON_UNSELECTED_GNOLL_P4, false);

	env_title->setButton(BUTTON_UNSELECTED_TROLL_P1, false);
	env_title->setButton(BUTTON_UNSELECTED_TROLL_P2, false);
	env_title->setButton(BUTTON_UNSELECTED_TROLL_P3, false);
	env_title->setButton(BUTTON_UNSELECTED_TROLL_P4, false);

	env_title->setButton(BUTTON_UNSELECTED_HOG_P1, false);
	env_title->setButton(BUTTON_UNSELECTED_HOG_P2, false);
	env_title->setButton(BUTTON_UNSELECTED_HOG_P3, false);
	env_title->setButton(BUTTON_UNSELECTED_HOG_P4, false);
}

void PrimeGUIManager::HideSelectedRaces()
{
	//Hide all players' selected race images

	env_title->setImage(IMAGE_PLAYER_1_KOBOLD, false);
	env_title->setImage(IMAGE_PLAYER_2_KOBOLD, false);
	env_title->setImage(IMAGE_PLAYER_3_KOBOLD, false);
	env_title->setImage(IMAGE_PLAYER_4_KOBOLD, false);

	env_title->setImage(IMAGE_PLAYER_1_GNOLL, false);
	env_title->setImage(IMAGE_PLAYER_2_GNOLL, false);
	env_title->setImage(IMAGE_PLAYER_3_GNOLL, false);
	env_title->setImage(IMAGE_PLAYER_4_GNOLL, false);

	env_title->setImage(IMAGE_PLAYER_1_TROLL, false);
	env_title->setImage(IMAGE_PLAYER_2_TROLL, false);
	env_title->setImage(IMAGE_PLAYER_3_TROLL, false);
	env_title->setImage(IMAGE_PLAYER_4_TROLL, false);

	env_title->setImage(IMAGE_PLAYER_1_HOG, false);
	env_title->setImage(IMAGE_PLAYER_2_HOG, false);
	env_title->setImage(IMAGE_PLAYER_3_HOG, false);
	env_title->setImage(IMAGE_PLAYER_4_HOG, false);
}

void PrimeGUIManager::SetTutorialPage(int page)
{
	//Manually specify a page to draw
	tutorialPage = page;
}

void PrimeGUIManager::FlipTutorialPages()
{
	//Draw elements according to tutorial page
	switch (tutorialPage)
	{
		case 1: //Page ONE
		{
			env_tutorial->setButton(BUTTON_PREVIOUS, false);
			env_tutorial->setButton(BUTTON_NEXT, true);

			env_tutorial->setImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_1, true);
			env_tutorial->setImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_2, false);
			env_tutorial->setImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_3, false);
			env_tutorial->setImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_4, false);
			env_tutorial->setImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_5, false);

			break;
		}

		case 2: //Page TWO
		{
			env_tutorial->setButton(BUTTON_PREVIOUS, true);
			env_tutorial->setButton(BUTTON_NEXT, true);

			env_tutorial->setImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_1, false);
			env_tutorial->setImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_2, true);
			env_tutorial->setImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_3, false);
			env_tutorial->setImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_4, false);
			env_tutorial->setImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_5, false);

			break;
		}

		case 3: //Page THREE
		{
			env_tutorial->setButton(BUTTON_PREVIOUS, true);
			env_tutorial->setButton(BUTTON_NEXT, true);

			env_tutorial->setImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_1, false);
			env_tutorial->setImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_2, false);
			env_tutorial->setImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_3, true);
			env_tutorial->setImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_4, false);
			env_tutorial->setImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_5, false);

			break;
		}

		case 4: //Page FOUR
		{
			env_tutorial->setButton(BUTTON_PREVIOUS, true);
			env_tutorial->setButton(BUTTON_NEXT, true);

			env_tutorial->setImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_1, false);
			env_tutorial->setImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_2, false);
			env_tutorial->setImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_3, false);
			env_tutorial->setImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_4, true);
			env_tutorial->setImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_5, false);

			break;
		}

		case 5: //Page FIVE
		{
			env_tutorial->setButton(BUTTON_PREVIOUS, true);
			env_tutorial->setButton(BUTTON_NEXT, false);

			env_tutorial->setImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_1, false);
			env_tutorial->setImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_2, false);
			env_tutorial->setImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_3, false);
			env_tutorial->setImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_4, false);
			env_tutorial->setImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_5, true);

			break;
		}
	}
}

void PrimeGUIManager::VerifyTitlePlayerOnOffButtons(PrimeTeam* p1, PrimeTeam* p2, PrimeTeam* p3, PrimeTeam* p4)
{
	//Activate teams when activation buttons are pressed

	if (env_title->isPressedButton(BUTTON_PLAYER_1_ACTIVATE)) { p1->isActive = true; }
	if (env_title->isPressedButton(BUTTON_PLAYER_2_ACTIVATE)) { p2->isActive = true; }
	if (env_title->isPressedButton(BUTTON_PLAYER_3_ACTIVATE)) { p3->isActive = true; }
	if (env_title->isPressedButton(BUTTON_PLAYER_4_ACTIVATE)) { p4->isActive = true; }

	//Deactivate teams when deactivation buttons are pressed

	if (env_title->isPressedButton(BUTTON_PLAYER_1_DEACTIVATE)) { p1->isActive = false; }
	if (env_title->isPressedButton(BUTTON_PLAYER_2_DEACTIVATE)) { p2->isActive = false; }
	if (env_title->isPressedButton(BUTTON_PLAYER_3_DEACTIVATE)) { p3->isActive = false; }
	if (env_title->isPressedButton(BUTTON_PLAYER_4_DEACTIVATE)) { p4->isActive = false; }
}

void PrimeGUIManager::VerifyTitleRaceButtons(PrimeTeam* p1, PrimeTeam* p2, PrimeTeam* p3, PrimeTeam* p4)
{
	//Set player races when buttons are pressed
	
	if (p1->isActive)
	{
		if (env_title->isPressedButton(BUTTON_UNSELECTED_KOBOLD_P1)) { p1->assignedRace = KOBOLD; }
		if (env_title->isPressedButton(BUTTON_UNSELECTED_GNOLL_P1)) { p1->assignedRace = GNOLL; }
		if (env_title->isPressedButton(BUTTON_UNSELECTED_TROLL_P1)) { p1->assignedRace = TROLL; }
		if (env_title->isPressedButton(BUTTON_UNSELECTED_HOG_P1)) { p1->assignedRace = HOG; }
	}

	if (p2->isActive)
	{
		if (env_title->isPressedButton(BUTTON_UNSELECTED_KOBOLD_P2)) { p2->assignedRace = KOBOLD; }
		if (env_title->isPressedButton(BUTTON_UNSELECTED_GNOLL_P2)) { p2->assignedRace = GNOLL; }
		if (env_title->isPressedButton(BUTTON_UNSELECTED_TROLL_P2)) { p2->assignedRace = TROLL; }
		if (env_title->isPressedButton(BUTTON_UNSELECTED_HOG_P2)) { p2->assignedRace = HOG; }
	}

	if (p3->isActive)
	{
		if (env_title->isPressedButton(BUTTON_UNSELECTED_KOBOLD_P3)) { p3->assignedRace = KOBOLD; }
		if (env_title->isPressedButton(BUTTON_UNSELECTED_GNOLL_P3)) { p3->assignedRace = GNOLL; }
		if (env_title->isPressedButton(BUTTON_UNSELECTED_TROLL_P3)) { p3->assignedRace = TROLL; }
		if (env_title->isPressedButton(BUTTON_UNSELECTED_HOG_P3)) { p3->assignedRace = HOG; }
	}

	if (p4->isActive)
	{
		if (env_title->isPressedButton(BUTTON_UNSELECTED_KOBOLD_P4)) { p4->assignedRace = KOBOLD; }
		if (env_title->isPressedButton(BUTTON_UNSELECTED_GNOLL_P4)) { p4->assignedRace = GNOLL; }
		if (env_title->isPressedButton(BUTTON_UNSELECTED_TROLL_P4)) { p4->assignedRace = TROLL; }
		if (env_title->isPressedButton(BUTTON_UNSELECTED_HOG_P4)) { p4->assignedRace = HOG; }
	}
}

bool PrimeGUIManager::VerifyTitleStartMatchButton(PrimeTeam* p1, PrimeTeam* p2, PrimeTeam* p3, PrimeTeam* p4)
{
	bool buttonPressed = false;
	int playersOn = 0;

	//Count active players
	if (p1->isActive) playersOn++;
	if (p2->isActive) playersOn++;
	if (p3->isActive) playersOn++;
	if (p4->isActive) playersOn++;

	//Enable "Start Match" button if at least 2 players are active
	if (playersOn >= 2)
	{
		env_title->setButton(BUTTON_START_MATCH, true);
		env_title->setImage(IMAGE_START_MATCH_DISABLED, false);

		//Check if this button has been pressed
		if (env_title->isPressedButton(BUTTON_START_MATCH)) buttonPressed = true;
	}

	//Otherwise, disable it and show a grayed out image instead
	else if (playersOn < 2)
	{
		env_title->setButton(BUTTON_START_MATCH, false);
		env_title->setImage(IMAGE_START_MATCH_DISABLED, true);
	}

	//Return button state
	return buttonPressed;
}

bool PrimeGUIManager::VerifyTitleTutorialButton()
{
	//Check if this button has been pressed
	if (env_title->isPressedButton(BUTTON_TUTORIAL)) return true;
	else return false;
}

bool PrimeGUIManager::VerifyTitleCreditsButton()
{
	//Check if this button has been pressed
	if (env_title->isPressedButton(BUTTON_CREDITS)) return true;
	else return false;
}

bool PrimeGUIManager::VerifyTutorialNextButtonPressed()
{
	//Check if this button has been pressed
	if (env_tutorial->isPressedButton(BUTTON_NEXT)) return true;
	else return false;
}

bool PrimeGUIManager::VerifyTutorialNextButtonReleased()
{
	//Check if this button is NOT pressed
	if (env_tutorial->isPressedButton(BUTTON_NEXT)) return false;
	else return true;
}

bool PrimeGUIManager::VerifyTutorialPreviousButtonPressed()
{
	//Check if this button has been pressed
	if (env_tutorial->isPressedButton(BUTTON_PREVIOUS)) return true;
	else return false;
}

bool PrimeGUIManager::VerifyTutorialPreviousButtonReleased()
{
	//Check if this button is NOT pressed
	if (env_tutorial->isPressedButton(BUTTON_PREVIOUS)) return false;
	else return true;
}

bool PrimeGUIManager::VerifyTutorialBackToTitleButton()
{
	//Check if this button has been pressed
	if (env_tutorial->isPressedButton(BUTTON_BACK_TO_TITLE_TUTORIAL)) return true;
	else return false;
}

bool PrimeGUIManager::VerifyCreditsBackToTitleButton()
{
	//Check if this button has been pressed
	if (env_credits->isPressedButton(BUTTON_BACK_TO_TITLE_CREDITS)) return true;
	else return false;
}

bool PrimeGUIManager::VerifyMatchEndTurnButton()
{
	//Check if this button has been pressed
	if (env_match->isPressedButton(BUTTON_END_TURN)) return true;
	else return false;
}

bool PrimeGUIManager::VerifyMatchEndMatchButton()
{
	//Check if this button has been pressed
	if (env_match->isPressedButton(BUTTON_END_MATCH)) return true;
	else return false;
}

void PrimeGUIManager::BuildGUITitleScreen()
{
	//Backgrounds
	env_title->addImage(BACKGROUND_TITLE_SCREEN,"gui/outgame/background_title.jpg",0,0);

	//Active player indicators
	env_title->addImage(INDICATOR_PLAYER_1_ON,"gui/outgame/team_player1.jpg",230,160);
	env_title->addImage(INDICATOR_PLAYER_2_ON,"gui/outgame/team_player2.jpg",650,160);
	env_title->addImage(INDICATOR_PLAYER_3_ON,"gui/outgame/team_player3.jpg",230,380);
	env_title->addImage(INDICATOR_PLAYER_4_ON,"gui/outgame/team_player4.jpg",650,380);

	//Inactive player indicators
	env_title->addImage(INDICATOR_PLAYER_1_OFF,"gui/outgame/team_player1_off.jpg",230,160);
	env_title->addImage(INDICATOR_PLAYER_2_OFF,"gui/outgame/team_player2_off.jpg",650,160);
	env_title->addImage(INDICATOR_PLAYER_3_OFF,"gui/outgame/team_player3_off.jpg",230,380);
	env_title->addImage(INDICATOR_PLAYER_4_OFF,"gui/outgame/team_player4_off.jpg",650,380);

	//Player activation buttons
	env_title->addButton(BUTTON_PLAYER_1_ACTIVATE,"gui/outgame/team_on.jpg","gui/outgame/team_on_hover.jpg",310,160,29,26);
	env_title->addButton(BUTTON_PLAYER_2_ACTIVATE,"gui/outgame/team_on.jpg","gui/outgame/team_on_hover.jpg",730,160,29,26);
	env_title->addButton(BUTTON_PLAYER_3_ACTIVATE,"gui/outgame/team_on.jpg","gui/outgame/team_on_hover.jpg",310,380,29,26);
	env_title->addButton(BUTTON_PLAYER_4_ACTIVATE,"gui/outgame/team_on.jpg","gui/outgame/team_on_hover.jpg",730,380,29,26);

	//Player deactivation buttons
	env_title->addButton(BUTTON_PLAYER_1_DEACTIVATE,"gui/outgame/team_off.jpg","gui/outgame/team_off_hover.jpg",310,160,29,26);
	env_title->addButton(BUTTON_PLAYER_2_DEACTIVATE,"gui/outgame/team_off.jpg","gui/outgame/team_off_hover.jpg",730,160,29,26);
	env_title->addButton(BUTTON_PLAYER_3_DEACTIVATE,"gui/outgame/team_off.jpg","gui/outgame/team_off_hover.jpg",310,380,29,26);
	env_title->addButton(BUTTON_PLAYER_4_DEACTIVATE,"gui/outgame/team_off.jpg","gui/outgame/team_off_hover.jpg",730,380,29,26);

	//Selected race images (for when a race is selected and cannot be clicked anymore)
	env_title->addImage(IMAGE_PLAYER_1_KOBOLD,"gui/outgame/race_kobold_toggled.jpg",230,190);
	env_title->addImage(IMAGE_PLAYER_1_GNOLL,"gui/outgame/race_gnoll_toggled.jpg",260,190);
	env_title->addImage(IMAGE_PLAYER_1_TROLL,"gui/outgame/race_troll_toggled.jpg",290,190);
	env_title->addImage(IMAGE_PLAYER_1_HOG,"gui/outgame/race_hog_toggled.jpg",320,190);

	env_title->addImage(IMAGE_PLAYER_2_KOBOLD,"gui/outgame/race_kobold_toggled.jpg",650,190);
	env_title->addImage(IMAGE_PLAYER_2_GNOLL,"gui/outgame/race_gnoll_toggled.jpg",680,190);
	env_title->addImage(IMAGE_PLAYER_2_TROLL,"gui/outgame/race_troll_toggled.jpg",710,190);
	env_title->addImage(IMAGE_PLAYER_2_HOG,"gui/outgame/race_hog_toggled.jpg",740,190);

	env_title->addImage(IMAGE_PLAYER_3_KOBOLD,"gui/outgame/race_kobold_toggled.jpg",230,410);
	env_title->addImage(IMAGE_PLAYER_3_GNOLL,"gui/outgame/race_gnoll_toggled.jpg",260,410);
	env_title->addImage(IMAGE_PLAYER_3_TROLL,"gui/outgame/race_troll_toggled.jpg",290,410);
	env_title->addImage(IMAGE_PLAYER_3_HOG,"gui/outgame/race_hog_toggled.jpg",320,410);

	env_title->addImage(IMAGE_PLAYER_4_KOBOLD,"gui/outgame/race_kobold_toggled.jpg",650,410);
	env_title->addImage(IMAGE_PLAYER_4_GNOLL,"gui/outgame/race_gnoll_toggled.jpg",680,410);
	env_title->addImage(IMAGE_PLAYER_4_TROLL,"gui/outgame/race_troll_toggled.jpg",710,410);
	env_title->addImage(IMAGE_PLAYER_4_HOG,"gui/outgame/race_hog_toggled.jpg",740,410);

	//Unselectable race images (for when a team is deactivated and no race can be selected)
	env_title->addImage(IMAGE_UNSELECTABLE_KOBOLD_P1,"gui/outgame/race_kobold_off.jpg",230,190);
	env_title->addImage(IMAGE_UNSELECTABLE_GNOLL_P1,"gui/outgame/race_gnoll_off.jpg",260,190);
	env_title->addImage(IMAGE_UNSELECTABLE_TROLL_P1,"gui/outgame/race_troll_off.jpg",290,190);
	env_title->addImage(IMAGE_UNSELECTABLE_HOG_P1,"gui/outgame/race_hog_off.jpg",320,190);

	env_title->addImage(IMAGE_UNSELECTABLE_KOBOLD_P2,"gui/outgame/race_kobold_off.jpg",650,190);
	env_title->addImage(IMAGE_UNSELECTABLE_GNOLL_P2,"gui/outgame/race_gnoll_off.jpg",680,190);
	env_title->addImage(IMAGE_UNSELECTABLE_TROLL_P2,"gui/outgame/race_troll_off.jpg",710,190);
	env_title->addImage(IMAGE_UNSELECTABLE_HOG_P2,"gui/outgame/race_hog_off.jpg",740,190);

	env_title->addImage(IMAGE_UNSELECTABLE_KOBOLD_P3,"gui/outgame/race_kobold_off.jpg",230,410);
	env_title->addImage(IMAGE_UNSELECTABLE_GNOLL_P3,"gui/outgame/race_gnoll_off.jpg",260,410);
	env_title->addImage(IMAGE_UNSELECTABLE_TROLL_P3,"gui/outgame/race_troll_off.jpg",290,410);
	env_title->addImage(IMAGE_UNSELECTABLE_HOG_P3,"gui/outgame/race_hog_off.jpg",320,410);

	env_title->addImage(IMAGE_UNSELECTABLE_KOBOLD_P4,"gui/outgame/race_kobold_off.jpg",650,410);
	env_title->addImage(IMAGE_UNSELECTABLE_GNOLL_P4,"gui/outgame/race_gnoll_off.jpg",680,410);
	env_title->addImage(IMAGE_UNSELECTABLE_TROLL_P4,"gui/outgame/race_troll_off.jpg",710,410);
	env_title->addImage(IMAGE_UNSELECTABLE_HOG_P4,"gui/outgame/race_hog_off.jpg",740,410);

	//Unselected race buttons (which allow the selection of a race)
	env_title->addButton(BUTTON_UNSELECTED_KOBOLD_P1,"gui/outgame/race_kobold.jpg","gui/outgame/race_kobold.jpg",230,190,29,26);
	env_title->addButton(BUTTON_UNSELECTED_GNOLL_P1,"gui/outgame/race_gnoll.jpg","gui/outgame/race_gnoll.jpg",260,190,29,26);
	env_title->addButton(BUTTON_UNSELECTED_TROLL_P1,"gui/outgame/race_troll.jpg","gui/outgame/race_troll.jpg",290,190,29,26);
	env_title->addButton(BUTTON_UNSELECTED_HOG_P1,"gui/outgame/race_hog.jpg","gui/outgame/race_hog.jpg",320,190,29,26);

	env_title->addButton(BUTTON_UNSELECTED_KOBOLD_P2,"gui/outgame/race_kobold.jpg","gui/outgame/race_kobold.jpg",650,190,29,26);
	env_title->addButton(BUTTON_UNSELECTED_GNOLL_P2,"gui/outgame/race_gnoll.jpg","gui/outgame/race_gnoll.jpg",680,190,29,26);
	env_title->addButton(BUTTON_UNSELECTED_TROLL_P2,"gui/outgame/race_troll.jpg","gui/outgame/race_troll.jpg",710,190,29,26);
	env_title->addButton(BUTTON_UNSELECTED_HOG_P2,"gui/outgame/race_hog.jpg","gui/outgame/race_hog.jpg",740,190,29,26);

	env_title->addButton(BUTTON_UNSELECTED_KOBOLD_P3,"gui/outgame/race_kobold.jpg","gui/outgame/race_kobold.jpg",230,410,29,26);
	env_title->addButton(BUTTON_UNSELECTED_GNOLL_P3,"gui/outgame/race_gnoll.jpg","gui/outgame/race_gnoll.jpg",260,410,29,26);
	env_title->addButton(BUTTON_UNSELECTED_TROLL_P3,"gui/outgame/race_troll.jpg","gui/outgame/race_troll.jpg",290,410,29,26);
	env_title->addButton(BUTTON_UNSELECTED_HOG_P3,"gui/outgame/race_hog.jpg","gui/outgame/race_hog.jpg",320,410,29,26);

	env_title->addButton(BUTTON_UNSELECTED_KOBOLD_P4,"gui/outgame/race_kobold.jpg","gui/outgame/race_kobold_toggled.jpg",650,410,29,26);
	env_title->addButton(BUTTON_UNSELECTED_GNOLL_P4,"gui/outgame/race_gnoll.jpg","gui/outgame/race_gnoll_toggled.jpg",680,410,29,26);
	env_title->addButton(BUTTON_UNSELECTED_TROLL_P4,"gui/outgame/race_troll.jpg","gui/outgame/race_troll_toggled.jpg",710,410,29,26);
	env_title->addButton(BUTTON_UNSELECTED_HOG_P4,"gui/outgame/race_hog.jpg","gui/outgame/race_hog_toggled.jpg",740,410,29,26);

	//Screen transition buttons
	env_title->addButton(BUTTON_CREDITS,"gui/outgame/button_credits.jpg","gui/outgame/button_credits.jpg",280,650,124,35);
	env_title->addButton(BUTTON_START_MATCH,"gui/outgame/button_start_match.jpg","gui/outgame/button_start_match.jpg",450,650,124,35);
	env_title->addButton(BUTTON_TUTORIAL,"gui/outgame/button_tutorial.jpg","gui/outgame/button_tutorial.jpg",620,650,124,35);

	//Disabled "Start Match" button
	env_title->addImage(IMAGE_START_MATCH_DISABLED,"gui/outgame/button_start_match_disabled.jpg",450,650);
}

void PrimeGUIManager::BuildGUICreditsScreen()
{
	//Backgrounds
	env_credits->addImage(BACKGROUND_CREDITS_SCREEN,"gui/outgame/background_credits.jpg",0,0);

	//Screen transition buttons
	env_credits->addButton(BUTTON_BACK_TO_TITLE_CREDITS,"gui/outgame/button_title.jpg","gui/outgame/button_title.jpg",450,650,124,35);
}

void PrimeGUIManager::BuildGUITutorialScreen()
{
	//Backgrounds
	env_tutorial->addImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_1,"gui/outgame/background_tutorial1.jpg",0,0);
	env_tutorial->addImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_2,"gui/outgame/background_tutorial2.jpg",0,0);
	env_tutorial->addImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_3,"gui/outgame/background_tutorial3.jpg",0,0);
	env_tutorial->addImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_4,"gui/outgame/background_tutorial4.jpg",0,0);
	env_tutorial->addImage(BACKGROUND_TUTORIAL_SCREEN_PAGE_5,"gui/outgame/background_tutorial5.jpg",0,0);

	//Browsing buttons
	env_tutorial->addButton(BUTTON_PREVIOUS,"gui/outgame/button_previous.jpg","gui/outgame/button_previous.jpg",750,650,90,35);
	env_tutorial->addButton(BUTTON_NEXT,"gui/outgame/button_next.jpg","gui/outgame/button_next.jpg",850,650,90,35);

	//Screen transition buttons
	env_tutorial->addButton(BUTTON_BACK_TO_TITLE_TUTORIAL,"gui/outgame/button_title.jpg","gui/outgame/button_title.jpg",100,650,124,35);
}

void PrimeGUIManager::BuildGUIMatchScreen()
{
	//Buttons
	env_match->addButton(BUTTON_END_TURN,"gui/ingame/button_end_turn.jpg","gui/ingame/button_end_turn.jpg",750,10,124,35);
	env_match->addButton(BUTTON_END_MATCH,"gui/ingame/button_end_match.jpg","gui/ingame/button_end_match.jpg",880,10,124,35);

	//Disabled buttons
	env_match->addImage(IMAGE_END_TURN_DISABLED,"gui/ingame/button_end_turn_disabled.jpg",750,10);
	env_match->addImage(IMAGE_END_MATCH_DISABLED,"gui/ingame/button_end_match_disabled.jpg",880,10);

	//Turn indicator
	env_match->addImage(INDICATOR_TURN_WIDGET,"gui/ingame/turn_widget.png",10,10);
	env_match->addImage(INDICATOR_TURN_PLAYER_1,"gui/ingame/team_player1.jpg",120,15);
	env_match->addImage(INDICATOR_TURN_PLAYER_2,"gui/ingame/team_player2.jpg",120,15);
	env_match->addImage(INDICATOR_TURN_PLAYER_3,"gui/ingame/team_player3.jpg",120,15);
	env_match->addImage(INDICATOR_TURN_PLAYER_4,"gui/ingame/team_player4.jpg",120,15);
	env_match->addLabel(LABEL_TURN_COUNT, "1", 80,20,100,30);

	SetTurnCount(false, 0); //Reset and hide turn count
	SetPlayerIndicator(false, 0); //Hide player indicators

	//Hide turn indicator widget and match buttons
	EnableEndTurnButton(false);
	EnableEndMatchButton(false);
	env_match->setImage(IMAGE_END_TURN_DISABLED, false);
	env_match->setImage(IMAGE_END_MATCH_DISABLED, false);
	env_match->setImage(INDICATOR_TURN_WIDGET, false);

	//Turn markers
	env_match->addImage(INDICATOR_TURN_MARKER_P1_1ST,"gui/ingame/turn_marker_player1.jpg",20,40);
	env_match->addImage(INDICATOR_TURN_MARKER_P1_2ND,"gui/ingame/turn_marker_player1.jpg",40,40);
	env_match->addImage(INDICATOR_TURN_MARKER_P1_3RD,"gui/ingame/turn_marker_player1.jpg",60,40);
	env_match->addImage(INDICATOR_TURN_MARKER_P1_4TH,"gui/ingame/turn_marker_player1.jpg",80,40);

	env_match->addImage(INDICATOR_TURN_MARKER_P2_1ST,"gui/ingame/turn_marker_player2.jpg",20,40);
	env_match->addImage(INDICATOR_TURN_MARKER_P2_2ND,"gui/ingame/turn_marker_player2.jpg",40,40);
	env_match->addImage(INDICATOR_TURN_MARKER_P2_3RD,"gui/ingame/turn_marker_player2.jpg",60,40);
	env_match->addImage(INDICATOR_TURN_MARKER_P2_4TH,"gui/ingame/turn_marker_player2.jpg",80,40);

	env_match->addImage(INDICATOR_TURN_MARKER_P3_1ST,"gui/ingame/turn_marker_player3.jpg",20,40);
	env_match->addImage(INDICATOR_TURN_MARKER_P3_2ND,"gui/ingame/turn_marker_player3.jpg",40,40);
	env_match->addImage(INDICATOR_TURN_MARKER_P3_3RD,"gui/ingame/turn_marker_player3.jpg",60,40);
	env_match->addImage(INDICATOR_TURN_MARKER_P3_4TH,"gui/ingame/turn_marker_player3.jpg",80,40);

	env_match->addImage(INDICATOR_TURN_MARKER_P4_1ST,"gui/ingame/turn_marker_player4.jpg",20,40);
	env_match->addImage(INDICATOR_TURN_MARKER_P4_2ND,"gui/ingame/turn_marker_player4.jpg",40,40);
	env_match->addImage(INDICATOR_TURN_MARKER_P4_3RD,"gui/ingame/turn_marker_player4.jpg",60,40);
	env_match->addImage(INDICATOR_TURN_MARKER_P4_4TH,"gui/ingame/turn_marker_player4.jpg",80,40);

	HideTurnMarkers(); //Hide all turn markers

	//Resource indicator widgets
	env_match->addImage(INDICATOR_RESOURCES_P1_1ST,"gui/ingame/resources_player1.jpg",140,700);
	env_match->addImage(INDICATOR_RESOURCES_P1_2ND,"gui/ingame/resources_player1.jpg",340,700);
	env_match->addImage(INDICATOR_RESOURCES_P1_3RD,"gui/ingame/resources_player1.jpg",540,700);
	env_match->addImage(INDICATOR_RESOURCES_P1_4TH,"gui/ingame/resources_player1.jpg",740,700);
	env_match->addImage(INDICATOR_RESOURCES_P1_1ST_ODD,"gui/ingame/resources_player1.jpg",240,700);
	env_match->addImage(INDICATOR_RESOURCES_P1_2ND_ODD,"gui/ingame/resources_player1.jpg",440,700);
	env_match->addImage(INDICATOR_RESOURCES_P1_3RD_ODD,"gui/ingame/resources_player1.jpg",640,700);

	env_match->addImage(INDICATOR_RESOURCES_P2_1ST,"gui/ingame/resources_player2.jpg",140,700);
	env_match->addImage(INDICATOR_RESOURCES_P2_2ND,"gui/ingame/resources_player2.jpg",340,700);
	env_match->addImage(INDICATOR_RESOURCES_P2_3RD,"gui/ingame/resources_player2.jpg",540,700);
	env_match->addImage(INDICATOR_RESOURCES_P2_4TH,"gui/ingame/resources_player2.jpg",740,700);
	env_match->addImage(INDICATOR_RESOURCES_P2_1ST_ODD,"gui/ingame/resources_player2.jpg",240,700);
	env_match->addImage(INDICATOR_RESOURCES_P2_2ND_ODD,"gui/ingame/resources_player2.jpg",440,700);
	env_match->addImage(INDICATOR_RESOURCES_P2_3RD_ODD,"gui/ingame/resources_player2.jpg",640,700);

	env_match->addImage(INDICATOR_RESOURCES_P3_1ST,"gui/ingame/resources_player3.jpg",140,700);
	env_match->addImage(INDICATOR_RESOURCES_P3_2ND,"gui/ingame/resources_player3.jpg",340,700);
	env_match->addImage(INDICATOR_RESOURCES_P3_3RD,"gui/ingame/resources_player3.jpg",540,700);
	env_match->addImage(INDICATOR_RESOURCES_P3_4TH,"gui/ingame/resources_player3.jpg",740,700);
	env_match->addImage(INDICATOR_RESOURCES_P3_1ST_ODD,"gui/ingame/resources_player3.jpg",240,700);
	env_match->addImage(INDICATOR_RESOURCES_P3_2ND_ODD,"gui/ingame/resources_player3.jpg",440,700);
	env_match->addImage(INDICATOR_RESOURCES_P3_3RD_ODD,"gui/ingame/resources_player3.jpg",640,700);

	env_match->addImage(INDICATOR_RESOURCES_P4_1ST,"gui/ingame/resources_player4.jpg",140,700);
	env_match->addImage(INDICATOR_RESOURCES_P4_2ND,"gui/ingame/resources_player4.jpg",340,700);
	env_match->addImage(INDICATOR_RESOURCES_P4_3RD,"gui/ingame/resources_player4.jpg",540,700);
	env_match->addImage(INDICATOR_RESOURCES_P4_4TH,"gui/ingame/resources_player4.jpg",740,700);
	env_match->addImage(INDICATOR_RESOURCES_P4_1ST_ODD,"gui/ingame/resources_player4.jpg",240,700);
	env_match->addImage(INDICATOR_RESOURCES_P4_2ND_ODD,"gui/ingame/resources_player4.jpg",440,700);
	env_match->addImage(INDICATOR_RESOURCES_P4_3RD_ODD,"gui/ingame/resources_player4.jpg",640,700);

	//Resource labels
	env_match->addLabel(LABEL_RESOURCES_1ST, "0", 180,710,240,730);
	env_match->addLabel(LABEL_RESOURCES_2ND, "0", 380,710,440,730);
	env_match->addLabel(LABEL_RESOURCES_3RD, "0", 580,710,640,730);
	env_match->addLabel(LABEL_RESOURCES_4TH, "0", 780,710,840,730);
	env_match->addLabel(LABEL_RESOURCES_1ST_ODD, "0", 280,710,340,730);
	env_match->addLabel(LABEL_RESOURCES_2ND_ODD, "0", 480,710,540,730);
	env_match->addLabel(LABEL_RESOURCES_3RD_ODD, "0", 680,710,740,730);

	HideResourceIndicators(); //Hide resource indicators

	//Generic messages
	env_match->addImage(MESSAGE_SORT,"gui/ingame/message_sorting_turn_order.jpg",380,330);
	env_match->addImage(MESSAGE_TURN,"gui/ingame/message_turn.jpg",380,360);
	env_match->addImage(MESSAGE_PLAYER_1,"gui/ingame/team_player1.jpg",465,320);
	env_match->addImage(MESSAGE_PLAYER_2,"gui/ingame/team_player2.jpg",465,320);
	env_match->addImage(MESSAGE_PLAYER_3,"gui/ingame/team_player3.jpg",465,320);
	env_match->addImage(MESSAGE_PLAYER_4,"gui/ingame/team_player4.jpg",465,320);

	SetGenericMessage(false, false, 0); //Hide generic messages

	//Victory messages
	env_match->addImage(MESSAGE_VICTORY_SINGLE,"gui/ingame/message_victory.jpg",380,360);
	env_match->addImage(MESSAGE_VICTORY_DOUBLE,"gui/ingame/message_victory.jpg",380,400);
	env_match->addImage(MESSAGE_VICTORY_TRIPLE,"gui/ingame/message_victory.jpg",380,440);
	env_match->addImage(MESSAGE_VICTORY_QUADRUPLE,"gui/ingame/message_victory.jpg",380,480);

	env_match->addImage(MESSAGE_VICTORY_P1_SINGLE,"gui/ingame/team_player1.jpg",465,320);
	env_match->addImage(MESSAGE_VICTORY_P1_DOUBLE_TOP,"gui/ingame/team_player1.jpg",465,300);
	env_match->addImage(MESSAGE_VICTORY_P1_TRIPLE_TOP,"gui/ingame/team_player1.jpg",465,270);
	env_match->addImage(MESSAGE_VICTORY_P1_QUADRUPLE_TOP,"gui/ingame/team_player1.jpg",465,240);

	env_match->addImage(MESSAGE_VICTORY_P2_SINGLE,"gui/ingame/team_player2.jpg",465,320);
	env_match->addImage(MESSAGE_VICTORY_P2_DOUBLE_TOP,"gui/ingame/team_player2.jpg",465,300);
	env_match->addImage(MESSAGE_VICTORY_P2_DOUBLE_BOTTOM,"gui/ingame/team_player2.jpg",465,350);
	env_match->addImage(MESSAGE_VICTORY_P2_TRIPLE_TOP,"gui/ingame/team_player2.jpg",465,270);
	env_match->addImage(MESSAGE_VICTORY_P2_TRIPLE_MIDDLE,"gui/ingame/team_player2.jpg",465,320);
	env_match->addImage(MESSAGE_VICTORY_P2_QUADRUPLE_MIDDLE_TOP,"gui/ingame/team_player2.jpg",465,300);

	env_match->addImage(MESSAGE_VICTORY_P3_SINGLE,"gui/ingame/team_player3.jpg",465,320);
	env_match->addImage(MESSAGE_VICTORY_P3_DOUBLE_TOP,"gui/ingame/team_player3.jpg",465,300);
	env_match->addImage(MESSAGE_VICTORY_P3_DOUBLE_BOTTOM,"gui/ingame/team_player3.jpg",465,350);
	env_match->addImage(MESSAGE_VICTORY_P3_TRIPLE_MIDDLE,"gui/ingame/team_player3.jpg",465,320);
	env_match->addImage(MESSAGE_VICTORY_P3_TRIPLE_BOTTOM,"gui/ingame/team_player3.jpg",465,370);
	env_match->addImage(MESSAGE_VICTORY_P3_QUADRUPLE_MIDDLE_BOTTOM,"gui/ingame/team_player3.jpg",465,360);

	env_match->addImage(MESSAGE_VICTORY_P4_SINGLE,"gui/ingame/team_player4.jpg",465,320);
	env_match->addImage(MESSAGE_VICTORY_P4_DOUBLE_BOTTOM,"gui/ingame/team_player4.jpg",465,350);
	env_match->addImage(MESSAGE_VICTORY_P4_TRIPLE_BOTTOM,"gui/ingame/team_player4.jpg",465,370);
	env_match->addImage(MESSAGE_VICTORY_P4_QUADRUPLE_BOTTOM,"gui/ingame/team_player4.jpg",465,420);

	HideVictoryMessage(); //Hide all victory messages
}

int PrimeGUIManager::ManageGUITitleScreen(PrimeTeam* p1, PrimeTeam* p2, PrimeTeam* p3, PrimeTeam* p4)
{
	int screenTransition = 0;

	//Verify team and race selection button presses

	VerifyTitlePlayerOnOffButtons(p1, p2, p3, p4);
	VerifyTitleRaceButtons(p1, p2, p3, p4);

	//Update team and race selection indicators and buttons

	ShowPlayerIndicators(p1, p2, p3, p4);
	ShowPlayerOnOffButtons(p1, p2, p3, p4);
	ShowRaces(p1, p2, p3, p4);

	//Return screen transition, if any transition button was pressed
	
	if (VerifyTitleStartMatchButton(p1, p2, p3, p4)) screenTransition = MATCH_TRANSITION;
	if (VerifyTitleTutorialButton()) screenTransition = TUTORIAL_TRANSITION;
	if (VerifyTitleCreditsButton()) screenTransition = CREDITS_TRANSITION;
	
	return screenTransition;
}

bool PrimeGUIManager::ManageGUITutorialScreen()
{
	//Browse pages when "Next" or "Previous" buttons are pressed
	if (VerifyTutorialNextButtonPressed()) { if (nextReleased) tutorialPage += 1; }
	if (VerifyTutorialPreviousButtonPressed()) { if (previousReleased) tutorialPage -= 1; }

	//Get page browsing buttons released state (not pressed)
	nextReleased = VerifyTutorialNextButtonReleased();
	previousReleased = VerifyTutorialPreviousButtonReleased();

	//Avoid pages going beyond tutorial limits
	if (tutorialPage < 1) tutorialPage = 1;
	if (tutorialPage > 5) tutorialPage = 5;

	//Draw tutorial
	FlipTutorialPages();

	//Return to title screen when "Back to Title" button is pressed
	if (VerifyTutorialBackToTitleButton()) return true;
	else return false;
}

bool PrimeGUIManager::ManageGUICreditsScreen()
{
	//Return to title screen when "Back to Title" button is pressed
	if (VerifyCreditsBackToTitleButton()) return true;
	else return false;
}

void PrimeGUIManager::ManageGUIMatchScreen(int turn, PrimePlayState* playState)
{
	//Victory message is hidden by default
	HideVictoryMessage();

	//If match has just begun...
	if (playState->phase == MATCH_START)
	{
		//Show "Sorting turn order" generic message
		if (playState->matchStart) SetGenericMessage(SORT_MESSAGE, false, 0);
	}

	//If match is running...
	else
	{
		//If there are no victors so far...
		if (playState->phase != MATCH_END)
		{
			//Do stuff at the end of one turn and the start of the next
			if (playState->phase == TURN_START || playState->phase == TURN_END)
			{
				//Disable match buttons
				EnableEndTurnButton(false);
				EnableEndMatchButton(false);

				if (playState->turnBeginPhase == NO_MESSAGE_AT_ONE
					|| playState->turnBeginPhase == NO_MESSAGE_AT_THREE)
				{
					//Enable turn indicator widget in case it was invisible
					env_match->setImage(INDICATOR_TURN_WIDGET, true);

					//Show no generic messages
					SetGenericMessage(false, false, 0);
				}

				else if (playState->turnBeginPhase == TURN_MESSAGE_AT_TWO)
				{
					//Show "Player X Turn" generic message
					SetGenericMessage(false, TURN_MESSAGE, playState->turnPlayer);
				}
			}

			//If this is not a transition phase...
			else
			{
				//If no signals have been sent to play state...
				if (!playState->signalEndMatch && !playState->signalEndTurn)
				{
					//Enable "End Match" button
					EnableEndMatchButton(true);

					//"End Turn" button is enabled only after ressurrection phase
					if (playState->phase != RESSURRECTION_PLACEMENT)
					{
						EnableEndTurnButton(true);
					}
				}

				//Otherwise, if a signal has been sent...
				else
				{
					//Disable both match buttons to avoid two
					//signals being sent in one turn.

					EnableEndTurnButton(false);
					EnableEndMatchButton(false);
				}
			}

			//Verify match button presses and signal play state accordingly
			if (VerifyMatchEndTurnButton()) playState->signalEndTurn = true;
			if (VerifyMatchEndMatchButton()) playState->signalEndMatch = true;

			//Update match GUI!
			//---------------------------------------

				//Update turn count
				SetTurnCount(true, turn);
	
				//Show player indicator according to turn
				SetPlayerIndicator(true, playState->turnPlayer);

				//Show turn markers in their correct order
				ShowTurnMarkers(playState);

				//Show resource indicators according to active players and play order
				ShowResourceIndicators(playState->playersActive, 
									   playState->player1, playState->player2, playState->player3, playState->player4);

			//---------------------------------------
		}

		//If someone has finally won the game...
		else if (playState->phase == MATCH_END)
		{
			//First step: hide the HUD!
			if (!playState->matchOver)
			{
				//Disable match buttons
				EnableEndTurnButton(false);
				EnableEndMatchButton(false);

				//Hide everything again
				env_match->setImage(IMAGE_END_TURN_DISABLED, false);
				env_match->setImage(IMAGE_END_MATCH_DISABLED, false);
				env_match->setImage(INDICATOR_TURN_WIDGET, false);

				HideResourceIndicators();
				HideTurnMarkers();

				SetTurnCount(false, 0); //Hide turn label
				SetPlayerIndicator(false, 0); //Hide player indicator
				SetGenericMessage(false, false, 0); //Hide generic messages
			}

			//Second step: show victory message!
			else if (playState->matchOver && !playState->signalEndMatch)
			{
				ShowVictoryMessage(playState);
			}
		}
	}
}