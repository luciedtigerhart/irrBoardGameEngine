#include "PrimePlayState.h"

PrimePlayState::PrimePlayState() {};
PrimePlayState::~PrimePlayState() {};

void PrimePlayState::SetTurnPlayer(int turn, int playersActive, PrimeTeam p1, PrimeTeam p2, PrimeTeam p3, PrimeTeam p4)
{
	int counter = 0;

	//Iterate through turn count to find out which
	//if this is the first, second, third or fourth player's turn...
	for (int iterator = 1; iterator <= turn; iterator++)
	{
		counter++;
		if (counter > playersActive) counter = 1;
	}

	if (p1.assignedTurn == counter) turnPlayer = p1.idx;
	else if (p2.assignedTurn == counter) turnPlayer = p2.idx;
	else if (p3.assignedTurn == counter) turnPlayer = p3.idx;
	else if (p4.assignedTurn == counter) turnPlayer = p4.idx;
}

void PrimePlayState::SetupTileHighlight(IrrBoard* board, PrimeTeam team)
{
	//Scan the whole board
	for (int i=0; i < board->tile_i; i++)
	{
		for (int j=0; j < board->tile_j; j++)
		{
			phase = TOKEN_SELECTION;

			//Highlight tiles according to phase

			if (phase == RESSURRECTION_PLACEMENT)
			{
				if (team.idx == 1)
				{
					if (board->board[i][j]->inf == SAFE_ZONE_TEAM_1)
					{
						//board->board[i][j]->isHighlighted = true;
						//board->board[i][j]->highlight = RESSURRECT;
					}
				}
			}

			else if (phase == TOKEN_SELECTION)
			{
				if (team.idx == 1)
				{
					if (board->board[i][j]->inf == GRASS)
					{
						board->board[i][j]->isHighlighted = true;
						board->board[i][j]->highlight = MOVE;
					}
				}
			}
		}
	}
};

void PrimePlayState::SetupTokenHighlight(IrrBoard* board, PrimeTeam team, int tokenIndex) {};
bool PrimePlayState::PlayIsValid(int play) {};
void PrimePlayState::SetupPushLine(int direction) {};