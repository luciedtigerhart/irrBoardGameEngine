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

	int phase; //Which phase the current turn is at (ressurrection, token selection, etc.)

	//Scan board and set tile highlights accordingly to current turn phase
	void setupTileHighlight(IrrBoard* board, PrimeTeam team);

	//Scan board looking for a tile whose token has index "tokenIndex", and highlight it accordingly to current turn phase
	void setupTokenHighlight(IrrBoard* board, PrimeTeam team, int tokenIndex);

	bool playIsValid(int play); //Validate whether a move can be performed, setting the state of involved tiles and tokens
	void setupPushLine(int direction); //Find all tokens in a line and set them to be pushed
};

#endif