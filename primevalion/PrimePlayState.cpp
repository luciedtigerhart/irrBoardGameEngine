#include "PrimePlayState.h"

#define CLICKED true
#define DEAD_TOKENS true
#define FINISHED_TOKENS true
#define ANIMATED_TOKENS true
#define I_TILE true
#define J_TILE false
#define ONLY_HIGHLIGHT false

PrimePlayState::PrimePlayState() {};
PrimePlayState::~PrimePlayState() {};

void PrimePlayState::Initialize(IrrInput* engineInput, int players,
								PrimeTeam p1, PrimeTeam p2, PrimeTeam p3, PrimeTeam p4,
								std::list<IrrToken*>* team1, std::list<IrrToken*>* team2,
								std::list<IrrToken*>* team3, std::list<IrrToken*>* team4)
{
	//Get input from engine
	input = engineInput;

	//Initializa token lists

	tokensTeam1 = new std::list<IrrToken*>();
	tokensTeam2 = new std::list<IrrToken*>();
	tokensTeam3 = new std::list<IrrToken*>();
	tokensTeam4 = new std::list<IrrToken*>();

	//Clone token lists

	if (p1.isActive) { for (t = team1->begin(); t != team1->end(); t++) tokensTeam1->push_back((*t)); }
	if (p2.isActive) { for (t = team2->begin(); t != team2->end(); t++) tokensTeam2->push_back((*t)); }
	if (p3.isActive) { for (t = team3->begin(); t != team3->end(); t++) tokensTeam3->push_back((*t)); }
	if (p3.isActive) { for (t = team4->begin(); t != team4->end(); t++) tokensTeam4->push_back((*t)); }

	//Clone player teams

	playersActive = players;

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

	//Initialize match phase
	phase = MATCH_START;

	//Initialize selected token
	selectedToken = NULL;
}

void PrimePlayState::SetTurnPlayer(int turn)
{
	int counter = 0;

	//Iterate through turn count to find out if this
	//is the first, second, third or fourth player's turn...
	for (int iterator = 1; iterator <= turn; iterator++)
	{
		counter++;
		if (counter > playersActive) counter = 1;
	}

	//Set "turnPlayer" as the current player
	if (player1.assignedTurn == counter) turnPlayer = player1.idx;
	else if (player2.assignedTurn == counter) turnPlayer = player2.idx;
	else if (player3.assignedTurn == counter) turnPlayer = player3.idx;
	else if (player4.assignedTurn == counter) turnPlayer = player4.idx;
}

void PrimePlayState::SetPushLine(bool clicked, int dir, IrrBoard* board, int iStart, int jStart)
{
	bool breakScan = false;

	int iTile = -1;
	int jTile = -1;
	int iAdd = -1;
	int jAdd = -1;
	int iBreak = -1;
	int jBreak = -1;

	//Configure search based on push direction
	if (dir == WEST) { iBreak = -1; jBreak = 0; iAdd = 0; jAdd = -1; }
	else if (dir == EAST) { iBreak = -1; jBreak = 9; iAdd = 0; jAdd = 1; }
	else if (dir == NORTH) { iBreak = 0; jBreak = -1; iAdd = -1; jAdd = 0; }
	else if (dir == SOUTH) { iBreak = 9; jBreak = -1; iAdd = 1; jAdd = 0; }

	iTile = iStart;
	jTile = jStart;

	//Find tokens in a line, starting at token to be pushed
	while (!breakScan)
	{
		//cout<<"tile: "<<iTile<<", "<<jTile<<endl;

		//If a token has been found...
		if (board->board[iTile][jTile]->token != NULL)
		{
			//If mouse button has been clicked and push move confirmed...
			if (clicked)
			{
				//Mark this token for pushing
				board->board[iTile][jTile]->token->getBehavior(0)->setBool("isGonnaBePushed", true);
				board->board[iTile][jTile]->token->getBehavior(0)->setInt("moveDir", dir);

				//Startup this token's animation
				board->board[iTile][jTile]->token->getBehavior(0)->setBool("isAnimStarted", true);
			}

			//Otherwise, if mouse is just hovering a pushable token...
			else
			{
				//Highlight this token to show player which tokens will be pushed
				board->board[iTile][jTile]->token->isHighlighted = true;
				board->board[iTile][jTile]->token->highlight = PUSH_HOVER;
			}
		}

		//If a free tile has been found, break scan
		else if (board->board[iTile][jTile]->token == NULL) breakScan = true;

		//If an obstacle has been found, break scan
		else if (board->board[iTile][jTile]->inf == RUINS) breakScan = true;

		//If "iBreak" or "jBreak" has been achieved, it means the board's
		//border has been reached and the scan should be finished up

		if (iTile == iBreak || jTile == jBreak) breakScan = true;

		//Iterate scan
		iTile += iAdd;
		jTile += jAdd;
	}
}

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
		if (dir == WEST) { iBreak = -1; jBreak = 0; iAdd = 0; jAdd = -1; }
		else if (dir == EAST) { iBreak = -1; jBreak = 9; iAdd = 0; jAdd = 1; }
		else if (dir == NORTH) { iBreak = 0; jBreak = -1; iAdd = -1; jAdd = 0; }
		else if (dir == SOUTH) { iBreak = 9; jBreak = -1; iAdd = 1; jAdd = 0; }

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
}

bool PrimePlayState::TokenHasTranslated(IrrToken* token, Vector origin, Vector destination, float speed)
{
	bool destReached = false;
	vector3df newRelativePosition;

	//If destination hasn't been reached yet...
	if (token->node->getAbsolutePosition().Z > destination.z)
	{
		float step = ((destination.z - origin.z) / 100) * speed;

		newRelativePosition.X = token->node->getPosition().X;
		newRelativePosition.Y = token->node->getPosition().Y;
		newRelativePosition.Z = token->node->getPosition().Z + step;
			
		token->node->setPosition(newRelativePosition);
	}

	//Otherwise, if destination has been reached...
	else destReached = true;

	//Report whether destination is reached
	return destReached;
}

void PrimePlayState::RessurrectToken(IrrToken* token, IrrBoard* board, int i, int j)
{
	//If this token's team is the current playing team
	if (token->player == turnPlayer)
	{
		//If this token is dead and the highlighted safe zone tile is empty
		if (token->getBehavior(0)->getBool("isDead") && board->board[i][j]->token == NULL)
		{
			//Re-activate token
			token->setActive(true);
			token->getBehavior(0)->setBool("isDead", false);

			//Place token at the safe zone!
			//if (board->moveToken(token->parentNode->posi, token->parentNode->posj, i, j))
			if (board->addToken(i, j, token))
			{
				//Update token's parent
				token->parentNode = board->board[i][j];

				//Make sure the token cannot move this turn
				token->getBehavior(0)->setBool("isFinished", true);
			}
		}
	}
}

void PrimePlayState::ClearHighlights(IrrBoard* board)
{
	//Scan the whole board
	for (int i=0; i < board->tile_i; i++)
	{
		for (int j=0; j < board->tile_j; j++)
		{
			//Deactivate tile highlights
			board->board[i][j]->isHighlighted = false;
			board->board[i][j]->highlight = NONE;

			//Deactivate token highlights
			if (board->board[i][j]->token != NULL)
			{
				board->board[i][j]->token->isHighlighted = false;
				board->board[i][j]->token->highlight = NONE;
			}
		}
	}
}

void PrimePlayState::CountRemainingTokens()
{
	int remainingTokens = 0, finishedTokens = 0;

	//Find dead tokens and decide whether ressurrection should be performed
	if (phase == RESSURRECTION_PLACEMENT)
	{
		remainingTokens = GetRemainingTokens(DEAD_TOKENS, false, false);

		//If there are no dead tokens, go to next phase
		if (remainingTokens == 0)
		{
			//Don't forget to reset action states
			ResetTokenActionStates();

			phase = PLAY_SELECTION;
		}
	}

	//Find tokens which animation hasn't finished yet
	if (phase == ANIMATION_EXECUTION)
	{
		remainingTokens = GetRemainingTokens(false, false, ANIMATED_TOKENS);

		//If all tokens have finished their animations, go back to play selection
		if (remainingTokens == 0)
		{
			//Reset selected token
			selectedToken = NULL;

			//Don't forget to reset action states
			ResetTokenActionStates();

			phase = PLAY_SELECTION;
		}
	}

	//Find tokens which have moved and decide if turn is over
	if (phase == PLAY_SELECTION)
	{
		finishedTokens = GetRemainingTokens(false, FINISHED_TOKENS, false);

		//If all tokens are finished, go to next phase
		if (finishedTokens >= 3)
		{
			//Don't forget to reset action states
			ResetTokenActionStates();

			phase = TURN_END;
		}
	}
}

void PrimePlayState::GetAdjacentTiles()
{
	//Get adjacent tile positions
	iNorth = selectedToken->parentNode->posi - 1;
	jNorth = selectedToken->parentNode->posj ;

	iSouth = selectedToken->parentNode->posi + 1;
	jSouth = selectedToken->parentNode->posj;

	iWest = selectedToken->parentNode->posi;
	jWest = selectedToken->parentNode->posj - 1;

	iEast = selectedToken->parentNode->posi;
	jEast = selectedToken->parentNode->posj + 1;

	//Get diagonal tile positions
	iNorthwest = selectedToken->parentNode->posi - 1;
	jNorthwest = selectedToken->parentNode->posj - 1;

	iNortheast = selectedToken->parentNode->posi - 1;
	jNortheast = selectedToken->parentNode->posj + 1;

	iSouthwest = selectedToken->parentNode->posi + 1;
	jSouthwest = selectedToken->parentNode->posj - 1;

	iSoutheast = selectedToken->parentNode->posi + 1;
	jSoutheast = selectedToken->parentNode->posj + 1;
}

int PrimePlayState::GetDestinationTile(int dir, int i, int j, bool iTile)
{
	int dest = -1;

	//If "iTile" is true, get the destination "i" tile (Row)
	if (iTile)
	{
		if (dir == NORTH || dir == NORTHEAST || dir == NORTHWEST) dest = i - 1;
		else if (dir == SOUTH || dir == SOUTHEAST || dir == SOUTHWEST) dest = i + 1;
		else if (dir == EAST || dir == WEST) dest = i;
	}

	//Otherwise, get the destination "j" tile (Column)
	else
	{
		if (dir == NORTH || dir == SOUTH) dest = j;
		else if (dir == EAST || dir == NORTHEAST || dir == SOUTHEAST) dest = j + 1;
		else if (dir == WEST || dir == NORTHWEST || dir == SOUTHWEST) dest = j - 1;
	}

	//Return destination
	return dest;
}

int PrimePlayState::GetRemainingTokens(bool dead, bool finished, bool animated)
{
	int remainingTokens = 0;

	//Look for tokens which animation hasn't finished
	if (animated)
	{
		//If "isAnimClosed" is false, then the token's animation hasn't been terminated by play state

		for (t = tokensTeam1->begin(); t != tokensTeam1->end(); t++)
		{
			if ((*t)->getBehavior(0)->getBool("isAnimStarted") && !(*t)->getBehavior(0)->getBool("isAnimClosed"))
				remainingTokens++;
		}
		for (t = tokensTeam2->begin(); t != tokensTeam2->end(); t++)
		{
			if ((*t)->getBehavior(0)->getBool("isAnimStarted") && !(*t)->getBehavior(0)->getBool("isAnimClosed"))
				remainingTokens++;
		}
		for (t = tokensTeam3->begin(); t != tokensTeam3->end(); t++)
		{
			if ((*t)->getBehavior(0)->getBool("isAnimStarted") && !(*t)->getBehavior(0)->getBool("isAnimClosed"))
				remainingTokens++;
		}
		for (t = tokensTeam4->begin(); t != tokensTeam4->end(); t++)
		{
			if ((*t)->getBehavior(0)->getBool("isAnimStarted") && !(*t)->getBehavior(0)->getBool("isAnimClosed"))
				remainingTokens++;
		}
	}

	//Otherwise, search for dead or finished tokens
	else
	{
		//Find out which player this turn belongs to,
		//and if that player has any dead tokens

		if (player1.isActive && turnPlayer == player1.idx)
		{
			//Search team 1's tokens
			for (t = tokensTeam1->begin(); t != tokensTeam1->end(); t++)
			{
				//Look for dead tokens or tokens which have already moved
				if (dead) { if ((*t)->getBehavior(0)->getBool("isDead")) remainingTokens++; }
				else if (finished) { if ((*t)->getBehavior(0)->getBool("isFinished")) remainingTokens++; }
			}
		}

		else if (player2.isActive && turnPlayer == player2.idx)
		{
			//Search for dead tokens among team 2's tokens
			for (t = tokensTeam2->begin(); t != tokensTeam2->end(); t++)
			{
				//Look for dead tokens or tokens which have already moved
				if (dead) { if ((*t)->getBehavior(0)->getBool("isDead")) remainingTokens++; }
				else if (finished) { if ((*t)->getBehavior(0)->getBool("isFinished")) remainingTokens++; }
			}
		}

		else if (player3.isActive && turnPlayer == player3.idx)
		{
			//Search for dead tokens among team 3's tokens
			for (t = tokensTeam3->begin(); t != tokensTeam3->end(); t++)
			{
				//Look for dead tokens or tokens which have already moved
				if (dead) { if ((*t)->getBehavior(0)->getBool("isDead")) remainingTokens++; }
				else if (finished) { if ((*t)->getBehavior(0)->getBool("isFinished")) remainingTokens++; }
			}
		}

		else if (player4.isActive && turnPlayer == player4.idx)
		{
			//Search for dead tokens among team 4's tokens
			for (t = tokensTeam4->begin(); t != tokensTeam4->end(); t++)
			{
				//Look for dead tokens or tokens which have already moved
				if (dead) { if ((*t)->getBehavior(0)->getBool("isDead")) remainingTokens++; }
				else if (finished) { if ((*t)->getBehavior(0)->getBool("isFinished")) remainingTokens++; }
			}
		}
	}

	//FOR TESTS
	//--------------------
	//remainingTokens = 1;

	//Return amout of dead or finished tokens
	return remainingTokens;
}

void PrimePlayState::ResetTokenActionStates()
{
	//Reset action states for all tokens of all teams
	/*
	for (t = tokensTeam1->begin(); t != tokensTeam1->end(); t++) (*t)->ResetActionStates();
	for (t = tokensTeam2->begin(); t != tokensTeam2->end(); t++) (*t)->ResetActionStates();
	for (t = tokensTeam3->begin(); t != tokensTeam3->end(); t++) (*t)->ResetActionStates();
	for (t = tokensTeam4->begin(); t != tokensTeam4->end(); t++) (*t)->ResetActionStates();
	*/
}

void PrimePlayState::ManageRessurrection(IrrBoard* board, int i, int j)
{
	bool tileMarked = false;
	int iTile = -1;
	int jTile = -1;

	if (turnPlayer == player1.idx)
	{
		//If this tile is this team's safe zone, and there's no token on it...
		if (board->board[i][j]->inf == SAFE_ZONE_TEAM_1 && board->board[i][j]->token == NULL)
		{
			//Mark this tile's position for highlighting
			iTile = i; jTile = j; tileMarked = true;
		}
	}

	else if (turnPlayer == player2.idx)
	{
		//If this tile is this team's safe zone, and there's no token on it...
		if (board->board[i][j]->inf == SAFE_ZONE_TEAM_2 && board->board[i][j]->token == NULL)
		{
			//Mark this tile's position for highlighting
			iTile = i; jTile = j; tileMarked = true;
		}
	}

	else if (turnPlayer == player3.idx)
	{
		//If this tile is this team's safe zone, and there's no token on it...
		if (board->board[i][j]->inf == SAFE_ZONE_TEAM_3 && board->board[i][j]->token == NULL)
		{
			//Mark this tile's position for highlighting
			iTile = i; jTile = j; tileMarked = true;
		}
	}

	else if (turnPlayer == player4.idx)
	{
		//If this tile is this team's safe zone, and there's no token on it...
		if (board->board[i][j]->inf == SAFE_ZONE_TEAM_4 && board->board[i][j]->token == NULL)
		{
			//Mark this tile's position for highlighting
			iTile = i; jTile = j; tileMarked = true;
		}
	}

	//If a tile has been marked for highlighting...
	if (tileMarked)
	{
		//Highlight the tile
		board->board[iTile][jTile]->isHighlighted = true;

		if (board->board[iTile][jTile]->isMouseHover)
			board->board[iTile][jTile]->highlight = RESSURRECT_HOVER;

		else board->board[iTile][jTile]->highlight = RESSURRECT;
	}
}

void PrimePlayState::ManageTokenSelection(IrrBoard* board, int i, int j)
{
	//If the tile at (i,j) has a token
	if (board->board[i][j]->token != NULL)
	{
		//If the token belongs to the current player
		if (board->board[i][j]->token->player == turnPlayer)
		{
			//If this token isn't selected, neither dead and hasn't moved yet...
			if (!board->board[i][j]->token->getBehavior(0)->getBool("isSelected")
				&& !board->board[i][j]->token->getBehavior(0)->getBool("isDead")
				&& !board->board[i][j]->token->getBehavior(0)->getBool("isFinished"))
			{
				//Highlight tile
				board->board[i][j]->isHighlighted = true;

				if (board->board[i][j]->isMouseHover || board->board[i][j]->token->isMouseHover)
					board->board[i][j]->highlight = MOVE_HOVER;

				else board->board[i][j]->highlight = MOVE;

				//Check if token isn't already highlighted
				//by something else (like a Push move)
				if (!board->board[i][j]->token->isHighlighted)
				{
					//Highlight token
					board->board[i][j]->token->isHighlighted = true;
					board->board[i][j]->token->highlight = MOVE_HOVER;
				}
			}
		}
	}
}

void PrimePlayState::ManageMoveSelection(IrrBoard* board, int i, int j)
{
	int dir = -1;

	//Grab adjacent directions
	GetAdjacentTiles();

	//If this is not a trap or obstacle tile...
	if (board->board[i][j]->inf != TRAP && board->board[i][j]->inf != RUINS)
	{
		//Find out this tile's direction relative to selected token
		if (i == iNorth && j == jNorth) dir = NORTH;
		else if (i == iSouth && j == jSouth) dir = SOUTH;
		else if (i == iWest && j == jWest) dir = WEST;
		else if (i == iEast && j == jEast) dir = EAST;
		else if (i == iNorthwest && j == jNorthwest) dir = NORTHWEST;
		else if (i == iNortheast && j == jNortheast) dir = NORTHEAST;
		else if (i == iSouthwest && j == jSouthwest) dir = SOUTHWEST;
		else if (i == iSoutheast && j == jSoutheast) dir = SOUTHEAST;

		//If this is the North, South, West or East tile...
		if (dir == NORTH || dir == SOUTH || dir == WEST || dir == EAST)
		{
			//If there's NOT a token on this tile...
			if (board->board[i][j]->token == NULL)
			{
				//Highlight tile for Movement
				board->board[i][j]->isHighlighted = true;
						
				if (board->board[i][j]->isMouseHover)
					board->board[i][j]->highlight = MOVE_HOVER;

				else board->board[i][j]->highlight = MOVE;

				//Set move direction for selected token
				selectedToken->getBehavior(0)->setInt("moveDir", dir);
			}
			
			//Else, if there's a token on this tile...
			else if (board->board[i][j]->token != NULL)
			{
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

						//Highlight other tokens in the Push line
						SetPushLine(ONLY_HIGHLIGHT, dir,board,i,j);

						//Set move direction for selected token
						selectedToken->getBehavior(0)->setInt("moveDir", dir);
					}
					
					else if (!board->board[i][j]->isMouseHover && !board->board[i][j]->token->isMouseHover)
					{
						board->board[i][j]->highlight = PUSH;
					}
				}
			}
		}
					
		//If this is the Northeast, Northwest, Southeast or Southwest tile...
		else if (dir == NORTHEAST || dir == NORTHWEST || dir == SOUTHEAST || dir == SOUTHWEST)
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

						//Set move direction for selected token
						selectedToken->getBehavior(0)->setInt("moveDir", dir);
					}
					
					else if (!board->board[i][j]->isMouseHover && !board->board[i][j]->token->isMouseHover)
					{
						board->board[i][j]->highlight = ATTACK;
					}
				}
			}
		}
	}
}

void PrimePlayState::UpdateTurnPhases(IrrBoard* board)
{
	bool tileSelected = false;
	bool tokenSelected = false;
	bool mouseClickedOnHighlight = false;

	//FOR TEST PURPOSES
	//------------------
	if (input->getMouseState().leftButtonDown)
	{
		phase = RESSURRECTION_PLACEMENT;
		
		if (!test3)
		{
			for (t = tokensTeam1->begin(); t != tokensTeam1->end(); t++)
			{
				//Kill token!
				(*t)->getBehavior(0)->setBool("isDead", true);
			}

			for (t = tokensTeam2->begin(); t != tokensTeam2->end(); t++)
			{
				//Kill token!
				(*t)->getBehavior(0)->setBool("isDead", true);
			}

			test3 = true;
		}
		
	}

	//Advance phases when conditions are met
	CountRemainingTokens();

	//By default, tiles and tokens are not highlighted
	ClearHighlights(board);

	//Scan the whole board
	for (int i=0; i < board->tile_i; i++)
	{
		for (int j=0; j < board->tile_j; j++)
		{
			//if (board->board[i][j]->isMouseHover) cout<<i<<", "<<j<<endl;

			//No token or tile is selected by default
			tileSelected = false;
			tokenSelected = false;

			//If a token has been selected...
			if (selectedToken != NULL)
			{
				//...But its animation hasn't begun...
				if (!selectedToken->getBehavior(0)->getBool("isAnimStarted"))
				{
					//...Reset its move direction.
					selectedToken->getBehavior(0)->setInt("moveDir", -1);
				}
			}

			//Highlight tiles and tokens according to phase


			//-------------------------------------------
			//-------- RESSURRECTION PLACEMENT ----------
			//-------------------------------------------


			if (phase == RESSURRECTION_PLACEMENT)
			{
				ManageRessurrection(board,i,j);
			}


			//-------------------------------------------
			//------------ PLAY SELECTION ---------------
			//-------------------------------------------


			else if (phase == PLAY_SELECTION)
			{
				ManageTokenSelection(board,i,j);

				if (selectedToken != NULL)
				{
					ManageMoveSelection(board,i,j);
				}
			}


			//-------------------------------------------
			//---------- INPUT VERIFICATION -------------
			//-------------------------------------------

			//Check for mouse position over a tile which can be interacted with
			if (board->board[i][j]->isMouseHover && board->board[i][j]->isHighlighted)
			{
				tileSelected = true;
			}
			
			//Check for mouse position over a token which can be interacted with
			if (board->board[i][j]->token != NULL)
			{
				if (board->board[i][j]->token->isMouseHover && board->board[i][j]->token->isHighlighted)
				{
					tokenSelected = true;
				}
			}

			//If mouse button is pressed...
			if (input->getMouseState().leftButtonDown)
			{
				//If mouse cursor is above a highlighted tile or token...
				if (tileSelected || tokenSelected)
				{
					//Mouse has been clicked atop a highlighted object
					mouseClickedOnHighlight = true;

					//cout<<"Clicked on highlight"<<endl;

					if (phase == PLAY_SELECTION)
					{
						//If mouse is hovering an empty tile...
						if (board->board[i][j]->token == NULL)
						{
							//...And a token has already been selected...
							if (selectedToken != NULL)
							{
								/*
								//...Mark selected token for movement.
								selectedToken->getBehavior(0)->setBool("isGonnaMove", true);

								//Startup animation for selected token
								selectedToken->getBehavior(0)->setBool("isAnimStarted", true);

								//Execute move (start animations)
								phase = ANIMATION_EXECUTION;
								*/
							}
						}

						//Otherwise, if mouse is above an occupied tile...
						else if (board->board[i][j]->token != NULL)
						{
							//If a token hasn't been selected yet
							if (selectedToken == NULL)
							{
								//Select the hovered token
								selectedToken = board->getToken(i,j);
								board->board[i][j]->token->getBehavior(0)->setBool("isSelected", true);
							}

							//Otherwise, if a token has already been selected...
							else if (selectedToken != NULL)
							{
								//If mouse is above a token that's highlighted for pushing...
								if (board->board[i][j]->token->highlight == PUSH_HOVER)
								{
									/*
									//Mark this token and the tokens behind it for pushing
									SetPushLine(CLICKED, selectedToken->getBehavior(0)->getInt("moveDir"), board, i, j);
									
									//Mark selected token for movement
									selectedToken->getBehavior(0)->setBool("isGonnaMove", true);

									//Startup animation for selected token
									selectedToken->getBehavior(0)->setBool("isAnimStarted", true);

									//Execute move (start animations)
									phase = ANIMATION_EXECUTION;
									*/
								}

								//Otherwise...
								else
								{
									//...If mouse is over an allied token, which is not the selected token...
									if (board->board[i][j]->token->player == turnPlayer)
									{
										//Unselect previous token
										selectedToken->getBehavior(0)->setBool("isSelected", false);

										//Select new token
										selectedToken = board->getToken(i,j);
										board->board[i][j]->token->getBehavior(0)->setBool("isSelected", true);
									}
									
									//...If mouse is over an enemy token...
									else
									{
										/*
										//Mark enemy as attack target
										board->board[i][j]->token->getBehavior(0)->setBool("isTargeted", true);

										//Mark selected token for movement
										selectedToken->getBehavior(0)->setBool("isGonnaMove", true);

										//Startup animation for enemy and selected token
										board->board[i][j]->token->getBehavior(0)->setBool("isAnimStarted", true);
										selectedToken->getBehavior(0)->setBool("isAnimStarted", true);

										//Execute move (start animations)
										phase = ANIMATION_EXECUTION;
										*/
									}
								}
							}
						}
					}

					else if (phase == RESSURRECTION_PLACEMENT)
					{
						//Iterate through all players' token lists, reviving dead tokens
						
						for (t = tokensTeam1->begin(); t != tokensTeam1->end(); t++) RessurrectToken((*t), board, i, j);
						for (t = tokensTeam2->begin(); t != tokensTeam2->end(); t++) RessurrectToken((*t), board, i, j);
						for (t = tokensTeam3->begin(); t != tokensTeam3->end(); t++) RessurrectToken((*t), board, i, j);
						for (t = tokensTeam4->begin(); t != tokensTeam4->end(); t++) RessurrectToken((*t), board, i, j);
					}
				}
			}
		}
	}


	//-------------------------------------------
	//--------- ANIMATION EXECUTION -------------
	//-------------------------------------------

	//Set animation speed
	animSpeed = 0.5f;

	//-------------------------------------
	//--------- OLD MOVEMENT TEST ---------
	//-------------------------------------
	
	/*
	int moveDir = NORTH;

	t = tokensTeam1->begin();

	if (!test)
	{
		iDest = GetDestinationTile(moveDir, (*t)->parentNode->posi, (*t)->parentNode->posj, true);
		jDest = GetDestinationTile(moveDir, (*t)->parentNode->posi, (*t)->parentNode->posj, false);

		//Destination tile position
		board->board[iDest][jDest]->getPosition(destPosition);

		//Token's current position
		originPosition.x = (*t)->node->getAbsolutePosition().X;
		originPosition.y = (*t)->node->getAbsolutePosition().Y;
		originPosition.z = (*t)->node->getAbsolutePosition().Z;

		test = true;
	}
	*/

	//-------------------------------------

	//if (phase == ANIMATION_EXECUTION)
	if (phase == PLAY_SELECTION)
	{
		//-------------------------------------
		//--------- OLD MOVEMENT TEST ---------
		//-------------------------------------

		/*
		if (moveDir == NORTH)
		{
			vector3df newRelativePosition;

			if ((*t)->node->getAbsolutePosition().X < destPosition.x)
			{
				float step = ((destPosition.x - originPosition.x) / 100) * animSpeed;

				newRelativePosition.X = (*t)->node->getPosition().X + step;
				newRelativePosition.Y = (*t)->node->getPosition().Y;
				newRelativePosition.Z = (*t)->node->getPosition().Z;
			
				(*t)->node->setPosition(newRelativePosition);

				//cout<<destPosition.x<<", "<<destPosition.y<<", "<<destPosition.z<<endl;
				//cout<<newRelativePosition.X<<", "<<newRelativePosition.Y<<", "<<newRelativePosition.Z<<endl;
			}

			else if (!test2)
			{
				//Reset relative position
				(*t)->node->setPosition(vector3df(0,0,0));

				//Snap token to new position
				test2 = board->moveToken((*t)->parentNode->posi, (*t)->parentNode->posj, iDest, jDest);

				(*t)->parentNode = board->board[iDest][jDest];
			}
		}
		*/

		//-------------------------------------

		/*
		//Iterate through all players' token lists

		for (t = tokensTeam1->begin(); t != tokensTeam1->end(); t++)
		{
			//If "isGonnaMove" is true, then this is the selected token
			if ((*t)->getBehavior(0)->getBool("isGonnaMove"))
			{
				//If this token has been marked for animation, but hasn't started running it yet...
				if ((*t)->getBehavior(0)->getBool("isAnimStarted") && !(*t)->getBehavior(0)->getBool("isAnimRunning"))
				{
					//Get destination tile positions
					iDest = GetDestinationTile((*t)->getBehavior(0)->getInt("moveDir"), (*t)->parentNode->posi, (*t)->parentNode->posj, I_TILE);
					jDest = GetDestinationTile((*t)->getBehavior(0)->getInt("moveDir"), (*t)->parentNode->posi, (*t)->parentNode->posj, J_TILE);
					
					//Pass destination tile positions to token
					(*t)->getBehavior(0)->setInt("iDest", iDest);
					(*t)->getBehavior(0)->setInt("jDest", jDest);
					
					//Pass destination and origin coordinates to token
					//board->board[iDest][jDest]->getPosition((*t)->destPosition);
					//(*t)->originPosition.x = (*t)->node->getAbsolutePosition().X;
					//(*t)->originPosition.y = (*t)->node->getAbsolutePosition().Y;
					//(*t)->originPosition.z = (*t)->node->getAbsolutePosition().Z;

					//Start animation!
					(*t)->getBehavior(0)->setBool("isAnimRunning", true);
				}
				
				//If this token's animation is currently running...
				else if (*t)->getBehavior(0)->getBool("isAnimStarted") && (*t)->getBehavior(0)->getBool("isAnimRunning"))
				{
					//Translate
					//...
				}

				//If this token's animation is over...
				else if ((*t)->getBehavior(0)->getBool("isAnimStarted") && (*t)->getBehavior(0)->getBool("isAnimFinished"))
				{
					//Reset relative position
					(*t)->node->setPosition(vector3df(0,0,0));

					//If snap to new position has been successful...
					if (board->moveToken((*t)->parentNode->posi, (*t)->parentNode->posj,
										 (*t)->getBehavior(0)->getInt("iDest"), (*t)->getBehavior(0)->getInt("jDest"))
					{
						//Update parent
						//(*t)->parentNode = board->board[(*t)->getBehavior(0)->getInt("iDest")][(*t)->getBehavior(0)->getInt("jDest")];
						
						//Terminate animations
						(*t)->getBehavior(0)->setBool("isAnimClosed", true);
					}
				}
			}	
		}
		*/

	}


	//-------------------------------------------
	//-------------- MATCH END ------------------
	//-------------------------------------------


	if (phase == MATCH_END)
	{
		for (t = tokensTeam1->begin(); t != tokensTeam1->end(); t++) { if (!(*t)->isActive()) (*t)->node->drop(); }
		for (t = tokensTeam1->begin(); t != tokensTeam2->end(); t++) { if (!(*t)->isActive()) (*t)->node->drop(); }
		for (t = tokensTeam1->begin(); t != tokensTeam3->end(); t++) { if (!(*t)->isActive()) (*t)->node->drop(); }
		for (t = tokensTeam1->begin(); t != tokensTeam4->end(); t++) { if (!(*t)->isActive()) (*t)->node->drop(); }
	}


	//-------------------------------------------
	//--- VERIFICATION FOR TOKEN DESELECTION ----
	//-------------------------------------------


	if (input->getMouseState().leftButtonDown)
	{
		//If mouse has been clicked somewhere without interaction...
		if (!mouseClickedOnHighlight)
		{
			//If a token has already been selected...
			if (phase == PLAY_SELECTION && selectedToken != NULL)
			{
				//If neither selected token nor its tile are below mouse
				if (!selectedToken->isMouseHover && !selectedToken->parentNode->isMouseHover)
				{
					//Unselect token!
					selectedToken->getBehavior(0)->setBool("isSelected", false);
					selectedToken = NULL;
				}
			}
		}
	}
};

void PrimePlayState::Update(IrrBoard* board, int turn)
{
	SetTurnPlayer(turn);
	UpdateTurnPhases(board);
};