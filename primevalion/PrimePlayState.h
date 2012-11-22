#ifndef _PRIMEPLAYSTATE_H
#define _PRIMEPLAYSTATE_H

#include <iostream>
#include "PrimeToken.h"

//Audio definitions
//----------------------------

	#define BGM_OUTGAME 0
	#define BGM_MATCH 1
	#define BGM_VICTORY 2

	#define SFX_BUTTON_LIGHT 0
	#define SFX_BUTTON_HEAVY 1
	#define SFX_TOKEN_SELECT_LIGHT 2
	#define SFX_TOKEN_SELECT_HEAVY 3
	#define SFX_TOKEN_DRAG 4
	#define SFX_TOKEN_FIT 5

	#define SFX_ABILITY 6
	#define SFX_EXTRACTION 7

	#define SFX_DIE_KOBOLD 8
	#define SFX_DIE_GNOLL 9
	#define SFX_DIE_TROLL 10
	#define SFX_DIE_HOG 11

	#define SFX_TRAP_KOBOLD 12
	#define SFX_TRAP_GNOLL 13
	#define SFX_TRAP_TROLL 14
	#define SFX_TRAP_HOG 15

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

//Particle system definitions
//----------------------------

	#define BLOOD 123
	#define ABILITY 456
	#define RESOURCES_NW 789
	#define RESOURCES_NE 790
	#define RESOURCES_SW 791
	#define RESOURCES_SE 792

//Camera movement definitions
//----------------------------

	#define W 87
	#define A 65
	#define S 83
	#define D 68
	#define F 70
	#define R 82
	#define Q 81
	#define E 69
	#define ARROW_LEFT 37
	#define ARROW_RIGHT 39
	#define ARROW_UP 38
	#define ARROW_DOWN 40
	#define PAGE_UP 33
	#define PAGE_DOWN 34

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
	
	//Animation variables
	float animSpeed, fallCounter, moveCounter;
	int tokensPushed;
	
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

	//Particle systems
	IrrParticleSystem* bloodParticles;
	IrrParticleSystem* abilityParticles;
	IrrParticleSystem* resourceParticlesNW;
	IrrParticleSystem* resourceParticlesNE;
	IrrParticleSystem* resourceParticlesSW;
	IrrParticleSystem* resourceParticlesSE;

	//Particle materials
	SMaterial blood, ability, resources;

	//Particle emission rates
	int bloodMin, bloodMax;
	int abilityMin, abilityMax;
	int resourceMin, resourceMax;

	//Particle initialization
	bool particlesOK;

	//Camera and crosshair
	ICameraSceneNode* activeCamera;
	ISceneNode* billboardCameraCrosshair;
	bool crosshairActive, middleMousePressed;

	//Audio lists
	std::vector<IrrGameObject*>* BGM;
	std::vector<IrrGameObject*>* SFX;

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
	bool signalVictoryBGM; //If "true", victory BGM must be played as match ends
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
	void Initialize(IrrEngine* engine, int players, int tokens, int goal,
					IrrParticleSystem* b, IrrParticleSystem* a,
					IrrParticleSystem* rnw, IrrParticleSystem* rne,
					IrrParticleSystem* rsw, IrrParticleSystem* rse,
					PrimeTeam p1, PrimeTeam p2, PrimeTeam p3, PrimeTeam p4,
					std::list<IrrToken*>* team1, std::list<IrrToken*>* team2,
					std::list<IrrToken*>* team3, std::list<IrrToken*>* team4,
					std::vector<IrrGameObject*>* music, std::vector<IrrGameObject*>* sound,
					ICameraSceneNode* camera);

	//Update "Wait" mini-engine
	void Wait();

	//Activate wait and return "true" when done
	bool Wait(float seconds);

	//Initialize particle effects
	void InitParticles(IrrBoard* board);

	//Create resource extraction particle emitters
	void CreateResourceEmitters(void);

	//Start a particle system's emission somewhere
	void StartParticles(int particleSystemID, Vector* position);

	//Stop a particle system's emission
	void StopParticles(int particleSystemID);

	//Update camera crosshair position
	void SetCrosshairPosition(void);

	//Find out which player this turn belongs to
	void SetTurnPlayer(int turn);

	//Find all tokens in a line and set them to be pushed
	int SetPushLine(bool clicked, int dir, IrrBoard* board, int iStart, int jStart);

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

	//Create resource extraction effects, perform extraction itself
	//and find out if any team has reached resource goal
	void VerifyResourceExtraction(IrrBoard* board, bool effectVerification);

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