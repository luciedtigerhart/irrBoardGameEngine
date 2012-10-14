#include "PrimePlayState.h"

PrimePlayState::PrimePlayState() {};
PrimePlayState::~PrimePlayState() {};

void PrimePlayState::setupTileHighlight(IrrBoard* board, PrimeTeam team)
{
	//Scan the whole board
	for (int i=0; i < board->tile_i; i++)
	{
		for (int j=0; j < board->tile_j; j++)
		{
			//Highlight tiles according to phase

			if (phase == RESSURRECTION_PLACEMENT)
			{
				if (team.idx == 1)
				{
					if (board->board[i][j]->idx == SAFE_ZONE_TEAM_1)
					{
						//board->board[i][j]->isHighlighted = true;
					}
				}
			}

			else if (phase == TOKEN_SELECTION)
			{
			}
		}
	}
}

bool PrimePlayState::playIsValid(int play)
{
}

void PrimePlayState::setupPushLine(int direction)
{
}