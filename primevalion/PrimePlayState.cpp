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

void PrimePlayState::GetAdjacentTiles()
{
	//Get adjacent tile positions
	iNorth = selectedToken->parentNode->posi;
	jNorth = selectedToken->parentNode->posj - 1;

	iSouth = selectedToken->parentNode->posi;
	jSouth = selectedToken->parentNode->posj + 1;

	iWest = selectedToken->parentNode->posi - 1;
	jWest = selectedToken->parentNode->posj;

	iEast = selectedToken->parentNode->posi + 1;
	jEast = selectedToken->parentNode->posj;

	//Get diagonal tile positions
	iNorthwest = selectedToken->parentNode->posi - 1;
	jNorthwest = selectedToken->parentNode->posj - 1;

	iNortheast = selectedToken->parentNode->posi + 1;
	jNortheast = selectedToken->parentNode->posj - 1;

	iSouthwest = selectedToken->parentNode->posi - 1;
	jSouthwest = selectedToken->parentNode->posj + 1;

	iSoutheast = selectedToken->parentNode->posi + 1;
	jSoutheast = selectedToken->parentNode->posj + 1;
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

void PrimePlayState::SetPushLine(int direction) {};

bool PrimePlayState::PlayIsValid(int play, int dir, IrrBoard* board, int i, int j)
{
	bool isValid = false;
	bool breakScan = false;

	int iTile = -1;
	int jTile = -1;
	int iAdd = -1;
	int jAdd = -1;
	int iBreak = -1;
	int jBreak = -1;

	int lastTileFound = 0;
	int tilesChecked = 0;
	int freeTiles = 0;

	//Validate Push move
	if (play == PUSH)
	{
		//Configure search based on push direction

		/*
		//Non-Mirrored
		if (dir == NORTH) { iBreak = 0; jBreak = -1; iAdd = -1; jAdd = 0; }
		else if (dir == SOUTH) { iBreak = 9; jBreak = -1; iAdd = 1; jAdd = 0; }
		else if (dir == WEST) { iBreak = -1; jBreak = 0; iAdd = 0; jAdd = -1; }
		else if (dir == EAST) { iBreak = -1; jBreak = 9; iAdd = 0; jAdd = 1; }
		*/

		//Mirrored
		if (dir == WEST) { iBreak = 0; jBreak = -1; iAdd = -1; jAdd = 0; }
		else if (dir == EAST) { iBreak = 9; jBreak = -1; iAdd = 1; jAdd = 0; }
		else if (dir == NORTH) { iBreak = -1; jBreak = 0; iAdd = 0; jAdd = -1; }
		else if (dir == SOUTH) { iBreak = -1; jBreak = 9; iAdd = 0; jAdd = 1; }

		iTile = i;
		jTile = j;

		//Find obstacles and tokens in a line, starting at token to be pushed
		while (!breakScan)
		{
			//cout<<"tile: "<<iTile<<", "<<jTile;

			//If an obstacle has been found...
			if (board->board[iTile][jTile]->inf == RUINS)
			{
				//If last tile found was a token...
				if (lastTileFound == TOKEN)
				{
					//If so far, only tokens have been found...
					if (freeTiles == 0)
					{
						//Cannot push line of tokens past obstacles
						isValid = false;

						//Break "while" loop
						breakScan = true;
					}

					//Else, if free tiles have been found...
					else if (freeTiles > 0)
					{
						//If at least 1 free tile has been found
						//between tokens, then they can be pushed
						isValid = true;

						//Break "while" loop
						breakScan = true;
					}
				}

				//Else, if last tile found was a
				//free tile (trap or grass)...
				else if (lastTileFound == FREE)
				{
					//If at least 1 free tile has been found
					//between tokens, then they can be pushed
					isValid = true;

					//Break "while" loop
					breakScan = true;
				}

				lastTileFound = RUINS;
			}

			//If a free tile has been found...
			else if (board->board[iTile][jTile]->token == NULL)
			{
				lastTileFound = FREE;
				freeTiles++;
			}

			//If a token has been found...
			else if (board->board[iTile][jTile]->token != NULL)
			{
				lastTileFound = TOKEN;
			}

			//If "iBreak" or "jBreak" has been achieved, it means the board's
			//border has been reached and the scan should be finished up
			if (iTile == iBreak || jTile == jBreak)
			{
				//If only tokens have been found...
				if (freeTiles == 0)
				{
					//Cannot push line of tokens past border
					isValid = false;
				}

				//Else, if free tiles have been found...
				else if (freeTiles > 0)
				{
					//If at least 1 free tile has been found
					//between tokens, then they can be pushed
					isValid = true;
				}

				//Break "while" loop
				breakScan = true;
			}

			//Iterate scan
			iTile += iAdd;
			jTile += jAdd;

			//cout<<" - last: "<<lastTileFound<<endl;
		}
	}

	//Validate Attack move
	else if (play == ATTACK)
	{
		//If trying to attack someone from the same team...
		if (board->board[i][j]->token->player == turnPlayer)
		{
			//Invalid move!
			isValid = false;
		}

		//If trying to attack someone in a safe zone...
		else if (board->board[i][j]->token->parentNode->inf == SAFE_ZONE_TEAM_1
				 || board->board[i][j]->token->parentNode->inf == SAFE_ZONE_TEAM_2
				 || board->board[i][j]->token->parentNode->inf == SAFE_ZONE_TEAM_3
				 || board->board[i][j]->token->parentNode->inf == SAFE_ZONE_TEAM_4)
		{
			//Invalid move!
			isValid = false;
		}

		//Otherwise, its a valid attack move!
		else isValid = true;
	}

	//Return validation result
	return isValid;
};

void PrimePlayState::ManageTokenSelection(IrrBoard* board, int i, int j)
{
	//If the tile at (i,j) has a token
	if (board->board[i][j]->token != NULL)
	{
		//If the token belongs to the current player
		if (board->board[i][j]->token->player == turnPlayer)
		{
			//If this token isn't selected, neither dead and hasn't moved yet...
			//if (!board->board[i][j]->token->isSelected
			//	&& !board->board[i][j]->token->isDead
			//	&& !board->board[i][j]->token->isFinished)
			//{
				//Highlight tile
				board->board[i][j]->isHighlighted = true;
				board->board[i][j]->highlight = MOVE_HOVER;

				//Highlight token
				board->board[i][j]->token->isHighlighted = true;
				board->board[i][j]->token->highlight = MOVE_HOVER;
			//}
		}
	}
}

void PrimePlayState::ManageMoveSelection(IrrBoard* board, int i, int j)
{
	int dir;

	// Highlight tiles adjacent to selected token
	//-------------------------------------------

	GetAdjacentTiles();

	//If this is not a trap or obstacle tile...
	if (board->board[i][j]->inf != TRAP && board->board[i][j]->inf != RUINS)
	{
		//If this is the North, South, West or East tile...
		if ((i == iNorth && j == jNorth) || (i == iSouth && j == jSouth)
			|| (i == iWest && j == jWest) || (i == iEast && j == jEast))
		{
			//If there's NOT a token on this tile...
			if (board->board[i][j]->token == NULL)
			{
				//Highlight tile for Movement
				board->board[i][j]->isHighlighted = true;
						
				if (board->board[i][j]->isMouseHover)
					board->board[i][j]->highlight = MOVE_HOVER;

				else board->board[i][j]->highlight = MOVE;
			}

			//Else, if there's a token on this tile...
			else
			{
				//Find out this tile's direction relative to selected token
				if (i == iNorth && j == jNorth) dir = NORTH;
				else if (i == iSouth && j == jSouth) dir = SOUTH;
				else if (i == iWest && j == jWest) dir = WEST;
				else if (i == iEast && j == jEast) dir = EAST;

				//cout<<"dir: "<<dir<<endl;

				//If its a valid Push move...
				if (PlayIsValid(PUSH,dir,board,i,j))
				{
					//Highlight tile for Push
					board->board[i][j]->isHighlighted = true;

					if (board->board[i][j]->isMouseHover || board->board[i][j]->token->isMouseHover)
					{
						board->board[i][j]->highlight = PUSH_HOVER;

						//Highlight token for Push
						board->board[i][j]->token->isHighlighted = true;
						board->board[i][j]->token->highlight = PUSH_HOVER;
					}
					else if (!board->board[i][j]->isMouseHover && !board->board[i][j]->token->isMouseHover)
					{
						board->board[i][j]->highlight = PUSH;
					}
				}
			}
		}
					
		//If this is the Northeast, Northwest, Southeast or Southwest tile...
		else if ((i == iNorthwest && j == jNorthwest) || (i == iNortheast && j == jNortheast)
				|| (i == iSouthwest && j == jSouthwest) || (i == iSoutheast && j == jSoutheast))
		{
			//If there's a token on this tile...
			if (board->board[i][j]->token != NULL)
			{
				//If its a valid Attack move...
				if (PlayIsValid(ATTACK,0,board,i,j))
				{
					//Highlight tile for Attack
					board->board[i][j]->isHighlighted = true;

					if (board->board[i][j]->isMouseHover || board->board[i][j]->token->isMouseHover)
					{
						board->board[i][j]->highlight = ATTACK_HOVER;

						//Highlight token for Attack
						board->board[i][j]->token->isHighlighted = true;
						board->board[i][j]->token->highlight = ATTACK_HOVER;
					}
					else if (!board->board[i][j]->isMouseHover && !board->board[i][j]->token->isMouseHover)
					{
						board->board[i][j]->highlight = ATTACK;
					}
				}
			}
		}
	}

	//-------------------------------------------
}

void PrimePlayState::UpdateTurnPhases(IrrBoard* board)
{
	//Scan the whole board
	for (int i=0; i < board->tile_i; i++)
	{
		for (int j=0; j < board->tile_j; j++)
		{
			//Tile highlights are deactivated by default
			board->board[i][j]->isHighlighted = false;
			board->board[i][j]->highlight = NONE;

			//Token highlights as well
			if (board->board[i][j]->token != NULL)
			{
				board->board[i][j]->token->isHighlighted = false;
				board->board[i][j]->token->highlight = NONE;
			}

			//FOR TEST PURPOSES
			//------------------
			phase = PLAY_SELECTION;

			//Highlight tiles and tokens according to phase


			//-------------------------------------------
			//-------- RESSURRECTION PLACEMENT ----------
			//-------------------------------------------


			if (phase == RESSURRECTION_PLACEMENT)
			{
				if (turnPlayer == player1.idx)
				{
					if (board->board[i][j]->inf == SAFE_ZONE_TEAM_1)
					{
						//board->board[i][j]->isHighlighted = true;
						//board->board[i][j]->highlight = RESSURRECT;
					}
				}
			}


			//-------------------------------------------
			//------------ PLAY SELECTION ---------------
			//-------------------------------------------


			else if (phase == PLAY_SELECTION)
			{
				selectedToken = board->getToken(7,9);

				ManageTokenSelection(board,i,j);

				if (selectedToken != NULL)
				{
					ManageMoveSelection(board,i,j);
				}
			}


			//-------------------------------------------
			//--------- ANIMATION EXECUTION -------------
			//-------------------------------------------


			else if (phase == ANIMATION_EXECUTION)
			{
				//Play animation
				//...

				//A token has been moved
				movesFinished++;
				selectedToken = NULL;
			}
		}
	}

	//If all of this team's tokens are done...
	if (movesFinished >= 3)
	{
		//Skip to end of turn
		phase = TURN_END;
		movesFinished = 0;
	}
};

void PrimePlayState::Update(IrrBoard* board, int turn)
{
	SetTurnPlayer(turn);
	UpdateTurnPhases(board);
};