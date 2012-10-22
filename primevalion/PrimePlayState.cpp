#include "PrimePlayState.h"

PrimePlayState::PrimePlayState() {};
PrimePlayState::~PrimePlayState() {};

void PrimePlayState::Initialize(int players, PrimeTeam p1, PrimeTeam p2, PrimeTeam p3, PrimeTeam p4)
{
	playersActive = players;

	//Clone players

	//Player 1...
	player1.idx = p1.idx;
	player1.isAI = p1.isAI;
	player1.isActive = p1.isActive;
	player1.isVictorious = p1.isVictorious;
	player1.assignedRace = p1.assignedRace;
	player1.assignedTurn = p1.assignedTurn;
	player1.primevalium = p1.primevalium;

	//Player 2...
	player2.idx = p2.idx;
	player2.isAI = p2.isAI;
	player2.isActive = p2.isActive;
	player2.isVictorious = p2.isVictorious;
	player2.assignedRace = p2.assignedRace;
	player2.assignedTurn = p2.assignedTurn;
	player2.primevalium = p2.primevalium;

	//Player 3...
	player3.idx = p3.idx;
	player3.isAI = p3.isAI;
	player3.isActive = p3.isActive;
	player3.isVictorious = p3.isVictorious;
	player3.assignedRace = p3.assignedRace;
	player3.assignedTurn = p3.assignedTurn;
	player3.primevalium = p3.primevalium;

	//Player 4...
	player4.idx = p4.idx;
	player4.isAI = p4.isAI;
	player4.isActive = p4.isActive;
	player4.isVictorious = p4.isVictorious;
	player4.assignedRace = p4.assignedRace;
	player4.assignedTurn = p4.assignedTurn;
	player4.primevalium = p4.primevalium;
}

void PrimePlayState::SetTurnPlayer(int turn)
{
	int counter = 0;

	//Iterate through turn count to find out which
	//if this is the first, second, third or fourth player's turn...
	for (int iterator = 1; iterator <= turn; iterator++)
	{
		counter++;
		if (counter > playersActive) counter = 1;
	}

	if (player1.assignedTurn == counter) turnPlayer = player1.idx;
	else if (player2.assignedTurn == counter) turnPlayer = player2.idx;
	else if (player3.assignedTurn == counter) turnPlayer = player3.idx;
	else if (player4.assignedTurn == counter) turnPlayer = player4.idx;
}

void PrimePlayState::SetupTileHighlight(IrrBoard* board)
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
				//if (turnPlayer == player1.idx)
				//{
					if (board->board[i][j]->inf == SAFE_ZONE_TEAM_1)
					{
						//board->board[i][j]->isHighlighted = true;
						//board->board[i][j]->highlight = RESSURRECT;
					}
				//}
			}

			else if (phase == TOKEN_SELECTION)
			{
				//if (turnPlayer == player1.idx)
				//{
					if (board->board[i][j]->inf == GRASS)
					{
						board->board[i][j]->isHighlighted = true;
						board->board[i][j]->highlight = MOVE;
					}
				//}
			}
		}
	}
};

void PrimePlayState::SetupTokenHighlight(IrrBoard* board) {};

bool PrimePlayState::PlayIsValid(int play) {};

void PrimePlayState::SetupPushLine(int direction) {};

void PrimePlayState::Update(IrrBoard* board, int turn)
{
	SetTurnPlayer(turn);
	SetupTileHighlight(board);
};