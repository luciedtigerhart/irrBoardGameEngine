#ifndef _PRIMEPLAYSTATE_H
#define _PRIMEPLAYSTATE_H

#include <iostream>
#include "IrrEngine.h"
#include "PrimeToken.h"

//Direction definitions
//----------------------------

	#define NORTH 1
	#define SOUTH 2
	#define WEST 3
	#define EAST 4

//Valid move definitions
//----------------------------

	#define TOKEN -2
	#define FREE -3

//Phase definitions
//----------------------------

	#define MATCH_START 1

		#define TURN_START 2
			#define RESSURRECTION_PLACEMENT 3
			#define PLAY_SELECTION 4
			#define ANIMATION_EXECUTION 5
		#define TURN_END 6

	#define MATCH_END 7

//----------------------------

using namespace IrrBoardGameEngine;

class PrimePlayState
{
private:
	//Position of tiles adjacent to selected token
	int iWest, jWest, iEast, jEast, iNorth, jNorth, iSouth, jSouth;
	int iNorthwest, jNorthwest, iNortheast, jNortheast;
	int iSouthwest, jSouthwest, iSoutheast, jSoutheast;

	//Input from engine
	IrrInput * input;

public:
	PrimePlayState();
	~PrimePlayState();

	//Team clones
	PrimeTeam player1;
	PrimeTeam player2;
	PrimeTeam player3;
	PrimeTeam player4;

	//Token lists
	std::list<IrrToken*>* tokensTeam1;
	std::list<IrrToken*>* tokensTeam2;
	std::list<IrrToken*>* tokensTeam3;
	std::list<IrrToken*>* tokensTeam4;
	std::list<IrrToken*>::iterator t;


	int turn; //Current match turn
	int turnPlayer; //Which player the current turn belongs to
	int playersActive; //Amount of active players in current match

	int phase; //Which phase the current turn is at (ressurrection, token selection, etc.)
	int movesFinished; //How many tokens have been moved in a turn

	//Token selected to move
	IrrToken* selectedToken;

	//Initialize this match's play state
	void Initialize(IrrInput* engineInput, int players,
					PrimeTeam p1, PrimeTeam p2, PrimeTeam p3, PrimeTeam p4,
					std::list<IrrToken*>* team1, std::list<IrrToken*>* team2,
					std::list<IrrToken*>* team3, std::list<IrrToken*>* team4);

	//Get tiles adjacent to selected token
	void GetAdjacentTiles();

	//Find out which player this turn belongs to
	void SetTurnPlayer(int turn);

	//Find all tokens in a line and set them to be pushed
	void SetPushLine(int direction);

	//Validate whether a move can be performed, setting the state of involved tiles and tokens
	bool PlayIsValid(int play, int dir, IrrBoard* board, int i, int j);

	bool GetDeadTokens(); //Find dead tokens in the current turn
	void ReviveDeadTokens(IrrBoard* board, int i, int j);

	void ManageRessurrection(IrrBoard* board, int i, int j); //Manage Ressurrection Placement phase
	void ManageTokenSelection(IrrBoard* board, int i, int j); //Manage token selection phase (Play Selection sub-phase 1)
	void ManageMoveSelection(IrrBoard* board, int i, int j); //Manage move selection phase (Play Selection sub-phase 2)

	void UpdateTurnPhases(IrrBoard* board); //Scan board, setting highlights and advancing phases
	void Update(IrrBoard* board, int turn); //Update play state
};

#endif