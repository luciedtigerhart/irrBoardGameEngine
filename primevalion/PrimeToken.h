#ifndef _PRIMETOKEN_H
#define _PRIMETOKEN_H

#include <iostream>
#include "IrrEngine.h"
#include "PrimeTile.h"
#include "PrimeTeam.h"

//Race definitions
//----------------------------

	#define KOBOLD 1
	#define GNOLL 2
	#define TROLL 3
	#define HOG 4

//----------------------------

using namespace IrrBoardGameEngine;

class PrimeToken : public IrrTokenBehavior
{
private:
public:
	PrimeToken(PrimeTeam myTeam); //Loads mesh and texture

	// General token states

	bool isGhost; //Whether this token is just a ressurrection indicator
	bool isDead; //Whether this token has been killed
	bool isFinished; //Whether this token has already moved
	bool isAbilityActive; //Whether this token's race ability is active

	// Turn action states

	bool isSelected; //Whether this token has been selected for an action
	bool isTargeted; //Whether this token has been targeted for an attack
	bool isGonnaMove; //Whether this token will move to an empty tile
	bool isGonnaBePushed; //Whether this token will be pushed with the next move

	bool isAnimStarted; //This token has started an animation this turn
	bool isAnimRunning; //One of this token's animations is running
	bool isAnimFinished; //One of this token's animations is finished
	bool isAnimClosed; //All of this token's animations are done for the turn

	// Other attributes

	int race; //Race of this token
	int team; //Team of this token
	int moveDir; //Direction this tile is moving or being pushed to

	//Variables used during translation animation
	int iDest, jDest;
	Vector destPosition, originPosition;

	const char* pathOBJ; //Stores 3D model path
	const char* pathTEX; //Stores texture path
	const char* pathTEXHL; //Stores highlight texture path

	// Token materials

	SMaterial matHighlight;
	SMaterial matNormal;

	void init(); //Initializes token
	void update(); //Updates this token's visuals

	void PaintVanilla(); //Color token with original color
	void ResetActionStates(); //Reset token's turn action states
};

#endif