#include "PrimeAIArchitecture.h"

PrimeAgent::PrimeAgent() {};
PrimeAgent::~PrimeAgent() { delete csv; };

void PrimeAgent::Startup(std::string logFile)
{
	//Initialize logger
	csv = new Logger(logFile);
}

void PrimeAgent::GetCondition(std::string* str, IrrToken* token, IrrBoard* board, int i, int j)
{
	str->clear(); //Clear previous attribution

	//Areas beyond the border of the board are in the "out zone"
	if (i <= -1 || i >= 10 || j <= -1 || j >= 10) { str->assign("out_zone"); }
	else
	{
		//Ruin or trap tiles
		if (board->board[i][j]->inf == RUINS) str->assign("obstacle");
		if (board->board[i][j]->inf == TRAP) str->assign("trap");
		
		//Grass or safe zone tiles
		if (board->board[i][j]->inf == GRASS
			|| board->board[i][j]->inf == SAFE_ZONE_TEAM_1 || board->board[i][j]->inf == SAFE_ZONE_TEAM_2
			|| board->board[i][j]->inf == SAFE_ZONE_TEAM_3 || board->board[i][j]->inf == SAFE_ZONE_TEAM_4)
		{
			//Empty tile
			if (board->board[i][j]->token == NULL) str->assign("free");

			//Occupied tile
			else if (board->board[i][j]->token != NULL)
			{
				//Allied token
				if (board->board[i][j]->token->player == token->player) str->assign("ally");
				
				//Enemy token
				else if (board->board[i][j]->token->player != token->player) str->assign("enemy");
			}
		}

		//Resource extraction tiles
		if (board->board[i][j]->inf == RESOURCE)
		{
			//Empty tile
			if (board->board[i][j]->token == NULL) str->assign("free_r");

			//Occupied tile
			else if (board->board[i][j]->token != NULL)
			{
				//Allied token
				if (board->board[i][j]->token->player == token->player) str->assign("ally_r");
				
				//Enemy token
				else if (board->board[i][j]->token->player != token->player) str->assign("enemy_r");
			}
		}
	}
}

void PrimeAgent::Sense(IrrToken* token, IrrBoard* board)
{
	//Get central position
	int i = token->parentNode->posi;
	int j = token->parentNode->posj;

	//Get each surrounding position's condition

	GetCondition(&N1, token, board, i - 1, j); //North
	GetCondition(&N2, token, board, i - 2, j); //Further north
	GetCondition(&S1, token, board, i + 1, j); //South
	GetCondition(&S2, token, board, i + 2, j); //Further south
	GetCondition(&W1, token, board, i, j - 1); //West
	GetCondition(&W2, token, board, i, j - 2); //Further west
	GetCondition(&E1, token, board, i, j + 1); //East
	GetCondition(&E2, token, board, i, j + 2); //Further east
	GetCondition(&NW, token, board, i - 1, j - 1); //Northwest
	GetCondition(&NE, token, board, i - 1, j + 1); //Northeast
	GetCondition(&SW, token, board, i + 1, j - 1); //Southwest
	GetCondition(&SE, token, board, i + 1, j + 1); //Southeast
}

bool PrimeAgent::RunFSM(IrrToken* token, IrrBoard* board, bool stand)
{
	bool moved = false;

	//Sense token's surroundings
	Sense(token, board);

	//Clear last move
	move.clear();
	move = "";

	//Set token's action according to a Finite State Machine (states and conditions)

	//***********************************************************************************
	
	if (E2 == "ally" && move == "")
	{
	    if (NW == "free" && move == "")
		{
	        if (S1 == "out_zone" && move == "") move = "MOVE_N";
	        if (S1 == "free" && move == "") move = "MOVE_E";
	        if (S1 == "enemy" && move == "") move = "MOVE_N";
		}
	    if (NW == "out_zone" && move == "")
		{
	        if (W2 == "ally" && move == "") move = "MOVE_S";
	        if (W2 == "free" && move == "") move = "MOVE_E";
	        if (W2 == "out_zone" && move == "") move = "MOVE_E";
		}
	    if (NW == "trap" && move == "") move = "MOVE_W";
	    if (NW == "enemy_r" && move == "")
		{
	        if (W1 == "free_r" && move == "") move = "ATK_NW";
			if (W1 == "enemy_r" && move == "")
			{
				if (W2 == "enemy_r" && move == "") move = "MOVE_W";
				if (W2 == "free_r" && move == "") move = "MOVE_W";
				if (W2 == "trap" && move == "") move = "MOVE_W";
			}
	        if (W1 == "ally_r" && move == "") move = "ATK_NW";
		}
	    if (NW == "free_r" && move == "")
		{
	        if (N1 == "trap" && move == "") move = "MOVE_W";
	        if (N1 == "enemy_r" && move == "")
			{
	            if (W1 == "free_r" && move == "") move = "MOVE_N";
	            if (W1 == "enemy_r" && move == "") move = "MOVE_W";
			}
		}
	    if (NW == "enemy" && move == "")
		{
	        if (NE == "free_r" && move == "") move = "MOVE_N";
	        if (NE == "enemy_r" && move == "") move = "ATK_NE";
		}
		if (NW == "ally_r" && move == "")
		{
			if (N1 == "trap" && move == "")
			{
				if (W1 == "free_r" && move == "") move = "MOVE_W";
				else if (move == "")
				{
					if (W2 == "free_r" && move == "") move = "MOVE_W";
					if (W2 == "enemy_r" && move == "") move = "MOVE_W";
				}
			}
			if (W1 == "trap" && move == "")
			{
				if (N1 == "free" && move == "") move = "MOVE_N";
				if (N1 == "enemy" && move == "") move = "MOVE_N";
			}
			if (S1 == "trap" && move == "")
			{
				if (SW == "enemy" && move == "") move = "ATK_SW";
				if (W1 == "enemy_r" && move == "") move = "MOVE_W";
				if (W1 == "free_r" && move == "") move = "MOVE_W";
				if (N1 == "enemy_r" && move == "") move = "MOVE_N";
				if (N1 == "free_r" && move == "") move = "MOVE_N";
			}
		}
	}
	if (E2 == "free" && move == "")
	{
	    if (SW == "out_zone" && move == "")
		{
	        if (W2 == "ally" && move == "") move = "MOVE_W";
	        if (W2 == "obstacle" && move == "") move = "MOVE_E";
	        if (W2 == "free" && move == "")
			{
	            if (E1 == "free" && move == "")
				{
	                if (N1 == "free" && move == "")
					{
						if (W1 == "free" && move == "")
						{
							if (board->board[token->parentNode->posi - 4][token->parentNode->posj]->inf == RESOURCE)
							{
								if (move == "") move = "MOVE_N";
							}
							else if (move == "") move = "MOVE_W";
						}
	                    if (W1 == "ally" && move == "") move = "MOVE_N";
					}
	                if (N1 == "ally" && move == "") move = "MOVE_N";
				}
	            if (E1 == "ally" && move == "") move = "MOVE_N";
			}
	        if (W2 == "out_zone" && move == "")
			{
	            if (N2 == "free" && move == "")
				{
	                if (S1 == "free" && move == "")
					{
	                    if (E1 == "free" && move == "")
						{
							if (N1 == "free" && move == "")
							{
								if (board->board[token->parentNode->posi][token->parentNode->posj + 4]->inf == RESOURCE)
								{
									if (move == "") move = "MOVE_E";
								}
								else if (move == "") move = "MOVE_N";
							}
	                        if (N1 == "ally" && move == "") move = "MOVE_E";
						}
	                    if (E1 == "ally" && move == "") move = "MOVE_E";
					}
	                if (S1 == "ally" && move == "") move = "MOVE_E";
				}
	            if (N2 == "ally" && move == "") move = "MOVE_E";
	            if (N2 == "obstacle" && move == "") move = "MOVE_S";
			}
		}
	    if (SW == "free" && move == "")
		{
	        if (N2 == "free" && move == "")
			{
	            if (NW == "free" && move == "")
				{
	                if (W2 == "free" && move == "") move = "MOVE_N";
	                if (W2 == "trap" && move == "") move = "MOVE_E";
	                if (W2 == "out_zone" && move == "") move = "MOVE_E";
				}
	            if (NW == "trap" && move == "") move = "MOVE_W";
	            if (NW == "enemy_r" && move == "") move = "ATK_NW";
	            if (NW == "free_r" && move == "")
				{
	                if (W1 == "free_r" && move == "") move = "MOVE_N";
	                if (W1 == "enemy_r" && move == "") move = "MOVE_W";
				}
			}
	        if (N2 == "trap" && move == "")
			{
	            if (N1 == "free" && move == "")
				{
	                if (S2 == "out_zone" && move == "") move = "MOVE_W";
	                if (S2 == "free" && move == "") move = "MOVE_S";
				}
	            if (N1 == "free_r" && move == "")
				{
					if (NE == "free_r" && move == "")
					{
						if (E1 == "free_r" && move == "") move = "MOVE_E";
						if (E1 == "enemy_r" && move == "") move = "MOVE_E";
						if (move == "") move = "MOVE_N";
					}
	                if (NE == "enemy_r" && move == "") move = "ATK_NE";
					if (NE == "ally_r" && move == "")
					{
						if (E1 == "enemy_r" && move == "") move = "MOVE_E";
						if (E1 == "free_r" && move == "") move = "MOVE_E";
						if (move == "") move = "MOVE_N";
					}
				}
	            if (N1 == "enemy_r" && move == "") move = "MOVE_N";
	            if (N1 == "ally_r" && move == "") move = "MOVE_S";
			}
	        if (N2 == "out_zone" && move == "")
			{
	            if (S2 == "free" && move == "")
				{
	                if (NE == "free" && move == "") move = "MOVE_S";
	                if (NE == "out_zone" && move == "")
					{
	                    if (W1 == "free" && move == "")
						{
	                        if (S1 == "free" && move == "")
							{
								if (E1 == "free" && move == "")
								{
									if (board->board[token->parentNode->posi + 4][token->parentNode->posj]->inf == RESOURCE)
									{
										if (move == "") move = "MOVE_S";
									}
									else if (move == "") move = "MOVE_E";
								}
	                            if (E1 == "ally" && move == "") move = "MOVE_S";
							}
	                        if (S1 == "ally" && move == "") move = "MOVE_S";
						}
	                    if (W1 == "ally" && move == "") move = "MOVE_S";
					}
				}
	            if (S2 == "trap" && move == "") move = "MOVE_E";
	            if (S2 == "ally" && move == "") move = "MOVE_S";
	            if (S2 == "enemy" && move == "") move = "MOVE_S";
			}
	        if (N2 == "ally" && move == "") move = "MOVE_N";
	        if (N2 == "free_r" && move == "")
			{
	            if (NE == "free_r" && move == "") move = "MOVE_N";
	            if (NE == "trap" && move == "") move = "MOVE_N";
	            if (NE == "enemy_r" && move == "") move = "ATK_NE";
	            if (NE == "ally_r" && move == "") move = "MOVE_N";
			}
			if (N2 == "enemy_r" && move == "")
			{
	            if (NE == "free_r" && move == "") move = "MOVE_N";
	            if (NE == "trap" && move == "") move = "MOVE_N";
	            if (NE == "enemy_r" && move == "")
				{
	                if (N1 == "free_r" && move == "") move = "ATK_NE";
	                if (N1 == "enemy_r" && move == "") move = "MOVE_N";
				}
	            if (NE == "ally_r" && move == "") move = "MOVE_N";
			}
	        if (N2 == "enemy" && move == "")
			{
	            if (NW == "free" && move == "") move = "MOVE_N";
	            if (NW == "enemy_r" && move == "") move = "ATK_NW";
				if (NW == "free_r" && move == "")
				{
					if (N1 == "free_r" && move == "") move = "MOVE_N";
					if (N1 == "enemy_r" && move == "") move = "MOVE_N";
					if (W1 == "enemy_r" && move == "") move = "MOVE_W";
				}
			}
	        if (N2 == "ally_r" && move == "")
			{
	            if (NE == "free_r" && move == "") move = "MOVE_N";
	            if (NE == "trap" && move == "") move = "MOVE_N";
	            if (NE == "enemy_r" && move == "") move = "ATK_NE";
			}
		}
	    if (SW == "ally" && move == "")
		{
	        if (N2 == "free" && move == "")
			{
	            if (N1 == "free" && move == "") move = "MOVE_E";
	            if (N1 == "enemy_r" && move == "") move = "ATK_NW";
			}
	        if (N2 == "trap" && move == "")
			{
	            if (S2 == "out_zone" && move == "") move = "MOVE_W";
	            if (S2 == "free" && move == "") move = "MOVE_S";
			}
		}
	    if (SW == "free_r" && move == "")
		{
	        if (E1 == "free" && move == "") move = "MOVE_S";
	        if (E1 == "trap" && move == "")
			{
				if (S1 == "free_r" && move == "")
				{
					if (W1 == "free_r" && move == "") move = "MOVE_W";
					if (W1 == "enemy_r" && move == "") move = "MOVE_W";
					if (move == "") move = "MOVE_S";
				}
	            if (S1 == "enemy_r" && move == "") move = "MOVE_S";
	            if (S1 == "ally_r" && move == "") move = "MOVE_W";
			}
		}
	    if (SW == "trap" && move == "")
		{
	        if (NW == "enemy_r" && move == "")
			{
	            if (W2 == "enemy_r" && move == "")
				{
	                if (W1 == "free_r" && move == "") move = "ATK_NW";
	                if (W1 == "enemy_r" && move == "") move = "MOVE_W";
	                if (W1 == "ally_r" && move == "") move = "MOVE_W";
				}
	            if (W2 == "free_r" && move == "") move = "ATK_NW";
			}
	        if (NW == "free_r" && move == "") move = "MOVE_W";
	        if (NW == "ally_r" && move == "") move = "MOVE_W";
		}
	    if (SW == "enemy_r" && move == "")
		{
	        if (S1 == "free_r" && move == "") move = "ATK_SW";
	        if (S1 == "enemy_r" && move == "")
			{
	            if (S2 == "trap" && move == "") move = "MOVE_S";
	            if (S2 == "free_r" && move == "") move = "ATK_SW";
	            if (S2 == "enemy_r" && move == "") move = "MOVE_S";
			}
			if (S1 == "ally_r" && move == "")
			{
				if (E1 == "trap" && move == "") move = "ATK_SW";
				if (W1 == "trap" && move == "") move = "ATK_SW";
				if (W1 == "enemy_r" && move == "") move = "MOVE_W";
				if (W1 == "free_r" && move == "") move = "MOVE_W";
				if (move == "") move = "MOVE_S";
			}
		}
	    if (SW == "ally_r" && move == "")
		{
	        if (S2 == "trap" && move == "") move = "ATK_SE";
	        if (S2 == "enemy_r" && move == "") move = "MOVE_S";
		}
	    if (SW == "enemy" && move == "")
		{
	        if (W1 == "free_r" && move == "")
			{
	            if (NW == "enemy_r" && move == "") move = "ATK_NW";
	            if (NW == "free_r" && move == "") move = "MOVE_N";
			}
	        if (W1 == "enemy_r" && move == "") move = "MOVE_W";
	        if (W1 == "ally_r" && move == "") move = "MOVE_N";
		}
	}
	if (E2 == "obstacle" && move == "") move = "MOVE_W";
	if (E2 == "out_zone" && move == "")
	{
	    if (S2 == "free" && move == "")
		{
	        if (SW == "free" && move == "")
			{
	            if (SE == "out_zone" && move == "")
				{
	                if (N1 == "free" && move == "")
					{
	                    if (W1 == "free" && move == "")
						{
							if (S1 == "free" && move == "")
							{
								if (N2 == "obstacle" && move == "") move = "MOVE_S";
								if (N2 == "free" && move == "")
								{
									if (board->board[token->parentNode->posi][token->parentNode->posj - 4]->inf == RESOURCE)
									{
										if (move == "") move = "MOVE_W";
									}
									else if (move == "") move = "MOVE_S";
								}
							}
							if (S1 == "ally" && move == "") move = "MOVE_W";
						}
	                    if (W1 == "ally" && move == "") move = "MOVE_W";
					}
	                if (N1 == "ally" && move == "") move = "MOVE_W";
				}
				if (SE == "free" && move == "")
				{
					if (NW == "trap" && move == "") move = "MOVE_S";
					if (W1 == "trap" && move == "") move = "MOVE_S";
					if (W2 == "trap" && move == "")
					{
						if (W1 == "enemy" && move == "") move = "MOVE_W";
						if (W1 == "free" && move == "") move = "MOVE_W";
						if (W1 == "ally" && move == "")
						{
							if (S1 == "free" && move == "") move = "MOVE_S";
							if (S1 == "enemy" && move == "") move = "MOVE_S";
						}
					}
					if (move == "") move = "MOVE_W";
				}
	            if (SE == "ally" && move == "") move = "MOVE_S";
			}
	        if (SW == "ally" && move == "") move = "MOVE_S";
		}
		if (S2 == "ally" && move == "")
		{
			if (W2 == "trap" && move == "")
			{
				if (W1 == "free" && move == "") move = "MOVE_W";
				if (W1 == "enemy" && move == "") move = "MOVE_W";
				if (S1 == "free" && move == "") move = "MOVE_S";
				if (S1 == "enemy" && move == "") move = "MOVE_S";
			}

			if (W1 == "trap" && move == "")
			{
				if (SE == "obstacle" && move == "") move = "MOVE_N";
				if (SE != "obstacle" && move == "")
				{
					if (S1 == "free" && move == "") move = "MOVE_S";
					if (S1 == "enemy" && move == "") move = "MOVE_S";
				}
			}

			if (board->board[token->parentNode->posi][token->parentNode->posj - 4]->inf == RESOURCE)
			{
				if (move == "") move = "MOVE_W";
			}
			else if (move == "")
			{
				if (NW == "trap" && move == "") move = "MOVE_S";
				if (SW == "trap" && move == "") move = "MOVE_N";
			}
		}
	    if (S2 == "obstacle" && move == "") move = "MOVE_N";
	}
	if (E2 == "trap" && move == "")
	{
	    if (SW == "out_zone" && move == "") move = "MOVE_N";
	    if (SW == "free" && move == "")
		{
	        if (N1 == "free" && move == "") move = "MOVE_N";
	        if (N1 == "trap" && move == "") move = "MOVE_W";
		}
	    if (SW == "ally" && move == "") move = "MOVE_N";
	    if (SW == "trap" && move == "")
		{
	        if (E1 == "free" && move == "") move = "MOVE_S";
	        if (E1 == "free_r" && move == "")
			{
	            if (SE == "enemy_r" && move == "") move = "ATK_SE";
	            if (SE == "free_r" && move == "")
				{
	                if (S1 == "enemy_r" && move == "") move = "MOVE_S";
	                if (S1 == "ally_r" && move == "") move = "MOVE_E";
				}
				if (SE == "ally_r" && move == "")
				{
					if (NE == "enemy" && move == "") move = "ATK_NE";
					if (S1 == "enemy_r" && move == "") move = "MOVE_S";
					if (S1 == "free_r" && move == "") move = "MOVE_S";
					if (move == "") move = "MOVE_E";
				}
			}
	        if (E1 == "enemy_r" && move == "") move = "MOVE_E";
		}
	}
	if (E2 == "enemy_r" && move == "")
	{
	    if (SE == "free" && move == "") move = "MOVE_N";
	    if (SE == "trap" && move == "") move = "MOVE_E";
	    if (SE == "enemy_r" && move == "")
		{
	        if (E1 == "free_r" && move == "") move = "ATK_SE";
			if (E1 == "enemy_r" && move == "")
			{
				if (W1 == "ally" && move == "") move = "MOVE_E";
				if (W1 == "enemy" && move == "") move = "MOVE_E";
				if (W1 == "free" && move == "") move = "ATK_SE";
			}
	        if (E1 == "ally_r" && move == "") move = "MOVE_E";
		}
	    if (SE == "free_r" && move == "") move = "MOVE_E";
	    if (SE == "ally_r" && move == "") move = "MOVE_E";
	}
	if (E2 == "free_r" && move == "")
	{
	    if (SE == "free" && move == "") move = "MOVE_N";
	    if (SE == "trap" && move == "") move = "MOVE_E";
	    if (SE == "enemy_r" && move == "") move = "ATK_SE";
	    if (SE == "free_r" && move == "") move = "MOVE_E";
	    if (SE == "ally_r" && move == "") move = "MOVE_E";
	}
	if (E2 == "enemy" && move == "")
	{
	    if (NE == "free" && move == "")
		{
	        if (NW == "free" && move == "") move = "MOVE_E";
	        if (NW == "trap" && move == "") move = "MOVE_W";
	        if (NW == "enemy_r" && move == "") move = "ATK_NW";
	        if (NW == "free_r" && move == "") move = "MOVE_W";
	        if (NW == "ally_r" && move == "") move = "MOVE_W";
		}
	    if (NE == "free_r" && move == "")
		{
	        if (N1 == "free_r" && move == "") move = "MOVE_E";
	        if (N1 == "enemy_r" && move == "") move = "MOVE_N";
		}
	    if (NE == "trap" && move == "")
		{
	        if (NW == "enemy_r" && move == "") move = "ATK_NW";
			if (NW == "free_r" && move == "")
			{
				if (W1 == "free_r" && move == "") move = "MOVE_W";
				if (W1 == "enemy_r" && move == "") move = "MOVE_W";
				if (N1 == "free_r" && move == "") move = "MOVE_N";
				if (N1 == "enemy_r" && move == "") move = "MOVE_N";
			}
		}
	    if (NE == "enemy_r" && move == "")
		{
	        if (N1 == "free_r" && move == "") move = "ATK_NE";
	        if (N1 == "enemy_r" && move == "") move = "MOVE_N";
		}
	}
	if (E2 == "ally_r" && move == "")
	{
		if (E1 == "free" && move == "") move = "MOVE_E";
		if (E1 == "trap" && move == "")
		{
			if (N1 == "free" && move == "") move = "MOVE_E";
			if (N1 == "enemy" && move == "") move = "MOVE_E";
			if (NE == "enemy" && move == "") move = "ATK_NE";
		}
		if (SE == "trap" && move == "")
		{
			if (E1 == "enemy" && move == "") move = "MOVE_E";
			if (E1 == "ally" && move == "") move = "MOVE_E";
		}
		if (S1 == "trap" && move == "")
		{
			if (E1 == "free_r" && move == "") move = "MOVE_E";
			if (SE == "enemy_r" && move == "") move = "ATK_SE";
		}
	}
	
	//If none of the above conditions were met, make token
	//stand still (but only when "stand" param is true)

	if (stand && move == "") move = "STAND";

	//***********************************************************************************


	//Check if there was a movement in the end
	if (move != "") moved = true;

	return moved;
}

void PrimeAgent::SetAction(int action)
{
	move.clear(); //Clear previous action

	//Set new action

	if (action == STAND) move = "STAND";
	else if (action == MOVE_N) move = "MOVE_N";
	else if (action == MOVE_S) move = "MOVE_S";
	else if (action == MOVE_W) move = "MOVE_W";
	else if (action == MOVE_E) move = "MOVE_E";
	else if (action == ATK_NW) move = "ATK_NW";
	else if (action == ATK_NE) move = "ATK_NE";
	else if (action == ATK_SW) move = "ATK_SW";
	else if (action == ATK_SE) move = "ATK_SE";
}

void PrimeAgent::Log(void)
{
	//Add a new case to log
	csv->addCase(N1,N2,S1,S2,W1,W2,E1,E2,NW,NE,SW,SE,move);

	//Update log
	csv->write();
}