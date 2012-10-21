#ifndef _PRIMEPLAYSTATE_H
#define _PRIMEPLAYSTATE_H

#include <iostream>
#include "IrrEngine.h"
#include "PrimeToken.h"

//Play definitions
//----------------------------

	#define PLAY_MOVE 1
	#define PLAY_PUSH 2
	#define PLAY_ATTACK 3
	#define PLAY_RESSURECT 4

//Phase definitions
//----------------------------

	#define TURN_START 1
	#define RESSURRECTION_PLACEMENT 2
	#define TOKEN_SELECTION 3
	#define PLAY_SELECTION 4
	#define ANIM_EXECUTION 5

//----------------------------

using namespace IrrBoardGameEngine;

class PrimePlayState
{
private:
public:
	PrimePlayState();
	~PrimePlayState();

	int turn; //Current match turn
	int turnPlayer; //Which player the current turn belongs to
	int phase; //Which phase the current turn is at (ressurrection, token selection, etc.)

	//Find out which player this turn belongs to
	void SetTurnPlayer(int turn, int playersActive, PrimeTeam p1, PrimeTeam p2, PrimeTeam p3, PrimeTeam p4);

	//Scan board and set tile highlights accordingly to current turn phase
	void SetupTileHighlight(IrrBoard* board, PrimeTeam team);

	//Scan board looking for a tile whose token has index "tokenIndex", and highlight it accordingly to current turn phase
	void SetupTokenHighlight(IrrBoard* board, PrimeTeam team, int tokenIndex);

	bool PlayIsValid(int play); //Validate whether a move can be performed, setting the state of involved tiles and tokens
	void SetupPushLine(int direction); //Find all tokens in a line and set them to be pushed
};

#endif