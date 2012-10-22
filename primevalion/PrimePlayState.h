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

	#define MATCH_START 1
	#define TURN_START 2
	#define RESSURRECTION_PLACEMENT 3
	#define TOKEN_SELECTION 4
	#define PLAY_SELECTION 5
	#define ANIMATION_EXECUTION 6
	#define TURN_END 7
	#define MATCH_END 8

//----------------------------

using namespace IrrBoardGameEngine;

class PrimePlayState
{
private:
public:
	PrimePlayState();
	~PrimePlayState();

	//Team clones
	PrimeTeam player1;
	PrimeTeam player2;
	PrimeTeam player3;
	PrimeTeam player4;

	int turn; //Current match turn
	int turnPlayer; //Which player the current turn belongs to
	int playersActive; //Amount of active players in current match
	int phase; //Which phase the current turn is at (ressurrection, token selection, etc.)

	//Initialize this match's play state
	void Initialize(int players, PrimeTeam p1, PrimeTeam p2, PrimeTeam p3, PrimeTeam p4);

	//Find out which player this turn belongs to
	void SetTurnPlayer(int turn);

	//Scan board and set tile highlights accordingly to current turn phase
	void SetupTileHighlight(IrrBoard* board);

	//Scan board and set token highlights accordingly to current turn phase
	void SetupTokenHighlight(IrrBoard* board);

	bool PlayIsValid(int play); //Validate whether a move can be performed, setting the state of involved tiles and tokens
	void SetupPushLine(int direction); //Find all tokens in a line and set them to be pushed

	void Update(IrrBoard* board, int turn); //Update play state
};

#endif