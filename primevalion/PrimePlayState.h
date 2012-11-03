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
	#define NORTHWEST 5
	#define NORTHEAST 6
	#define SOUTHWEST 7
	#define SOUTHEAST 8

//General phase definitions
//----------------------------

	#define MATCH_START 1

		#define TURN_START 2
			#define RESSURRECTION_PLACEMENT 3
			#define PLAY_SELECTION 4
			#define ANIMATION_EXECUTION 5
		#define TURN_END 6

	#define MATCH_END 7

//Turn begin phase definitions
//----------------------------

	#define NO_MESSAGE_AT_ONE 1
	#define TURN_MESSAGE_AT_TWO 2
	#define NO_MESSAGE_AT_THREE 3

//Other helpful definitions
//----------------------------

	#define TOKEN -2
	#define FREE -3

	#define CLICKED true
	#define ONLY_HIGHLIGHT false

	#define DEAD_TOKENS true
	#define FINISHED_TOKENS true
	#define ANIMATED_TOKENS true

	#define I_TILE true
	#define J_TILE false

//----------------------------

using namespace IrrBoardGameEngine;

class PrimePlayState
{
private:
	//Time attributes for GUI messages and manual animations
	float deltaTime;
	int now;
	int then;
	float wait;
	float sleep;
	bool awake;
	
	//Animation speed
	float animSpeed;
	
	//Animations to be executed
	bool animSimpleMove, animPushMove, animTrapDeath, animAttackDeath;

	//Destination tile position (translation animation)
	int iDest, jDest;

	//Position of tiles adjacent to selected token
	int iWest, jWest, iEast, jEast, iNorth, jNorth, iSouth, jSouth;
	int iNorthwest, jNorthwest, iNortheast, jNortheast;
	int iSouthwest, jSouthwest, iSoutheast, jSoutheast;

	//Auxiliary variables

	bool tokenRessurrected; //If "true", a token has been ressurrected
	bool resourcesVerified; //If "true", resource extraction has been verified
	bool resourcesExtracted; //If "true", then resources have been extracted
	int resourcesGoal; //Amount of resources needed to win the match

	//Ressurrection phase skipping (very special case, unlikely to happen!)

	int deadTokensNotRevived, safeZoneTilesMax;
	int safeZone1TilesOccupied, safeZone2TilesOccupied;
	int safeZone3TilesOccupied, safeZone4TilesOccupied;
	bool safeZone1Full, safeZone2Full, safeZone3Full, safeZone4Full;
	bool skipRessurrection;

	//Input from engine
	IrrInput * input;

	//Particle system
	IrrParticleSystem* particleSystem;
	IParticleSystemSceneNode* particles;

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

	bool signalBackToTitle; //If "true", match has finished completely and game should return to title screen
	bool signalEndTurn; //If "true", GUI has reported the "End Turn" button has been pressed
	bool signalEndMatch; //If "true", GUI has reported the "End Match" button has been pressed
	bool matchStart; //If "true", then "Sorting turn order" message is shown
	bool matchOver; //If "true", then victory messages are shown
	bool turnOver; //If "true", then current turn is over

	int turnBeginPhase; //1: A new turn has just begun, no messages are shown
						//2: "Player X Turn" message is being shown
						//3: Ressurrection phase about to start, no messages are shown

	int turn; //Current match turn
	int turnPlayer; //Which player the current turn belongs to
	int playersActive; //Amount of active players in current match
	int tokensActive; //Amount of tokens in each team
	int phase; //Which phase the current turn is at (ressurrection, token selection, etc.)

	//Token storages
	IrrToken* selectedToken;
	IrrToken* killedToken;

	//Initialize this match's play state
	void Initialize(IrrEngine* engine, IParticleSystemSceneNode* ps, int players, int tokens, int goal,
					PrimeTeam p1, PrimeTeam p2, PrimeTeam p3, PrimeTeam p4,
					std::list<IrrToken*>* team1, std::list<IrrToken*>* team2,
					std::list<IrrToken*>* team3, std::list<IrrToken*>* team4);

	//Update "Wait" mini-engine
	void Wait();

	//Activate wait and return "true" when done
	bool Wait(float seconds);

	//Find out which player this turn belongs to
	void SetTurnPlayer(int turn);

	//Find all tokens in a line and set them to be pushed
	void SetPushLine(bool clicked, int dir, IrrBoard* board, int iStart, int jStart);

	//Validate whether a move can be performed, setting the state of involved tiles and tokens
	bool PlayIsValid(int play, int dir, IrrBoard* board, int i, int j);

	//Translate token with every call and returns "true" when it reaches the destination
	bool TokenHasTranslated(IrrToken* token, float speed);

	//Snap pushed tokens to their new tile, in order contrary to the push direction,
	//and returns "true" when all of them have been successfully reallocated
	bool PushedTokensSnapped(IrrBoard* board);

	//Auxiliary method for the Hog race's special ability,
	//checks whether an enemy unit was killed with a move
	bool EnemyTokenKilled(IrrBoard* board);

	//Auxiliary method for the Troll race's special ability,
	//checks if there's a friendly Troll on an adjacent tile
	bool TrollBesideMe(IrrToken* token, IrrBoard* board);

	//Execute a token's animations
	void AnimateToken(IrrToken* token, IrrBoard* board, float speed);

	//Place a dead token on a safe zone tile
	void RessurrectToken(IrrToken* token, IrrBoard* board, int i, int j);

	//Check for ressurrection phase skipping condition
	void VerifySafeZoneOccupation(IrrBoard* board);

	//Check for tiles on the extraction point and
	//if any team has reached resource goal
	void VerifyResourceExtraction(IrrBoard* board);

	//Clear highlights off every tile and token
	void ClearHighlights(IrrBoard* board);

	//Count tokens and advance phases when conditions are met
	void SwapPhase(IrrBoard* board);

	//Advance phases according to token or tile which was clicked
	void SwapPhaseOnClick(IrrBoard* board, int i, int j);

	//Get tiles adjacent to selected token
	void GetAdjacentTiles();

	//Return the destination tile given a direction
	int GetDestinationTile(int dir, int i, int j, bool iTile);

	//Find tokens with certain attribute in the current turn
	int GetRemainingTokens(bool dead, bool finished, bool animated);

	//Update cooldown for all units
	void UpdateCooldown();

	//Set all tokens as finished, ending turn prematurely
	void FinishTokens();

	//Clear token action states at the end of a turn phase
	void ResetTokenActionStates();

	void ManageRaceAbilities(IrrToken* token, IrrBoard* board); //Activate or deactivate race abilities when conditions are met
	void ManageRessurrection(IrrBoard* board, int i, int j); //Manage Ressurrection Placement phase
	void ManageTokenSelection(IrrBoard* board, int i, int j); //Manage token selection phase (Play Selection sub-phase 1)
	void ManageMoveSelection(IrrBoard* board, int i, int j); //Manage move selection phase (Play Selection sub-phase 2)

	void UpdateTurnPhases(IrrBoard* board); //Scan board, setting highlights and advancing phases
	void Update(IrrBoard* board, int turn); //Update this match's play state
};

#endif