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

	bool isDead; //Whether this token has been killed
	bool isFinished; //Whether this token has already moved
	bool isAbilityActive; //Whether this token's race ability is active

	bool isSelected; //Whether this token has been selected by a player
	bool isTargeted; //Whether this token has been targeted by a player
	bool isGonnaBePushed; //Whether this tile will be pushed with the next move

	bool isAnimRunning; //One of this token's animations is running
	bool isAnimFinished; //All of this token's animations are finished

	int race; //Race of this token
	int team; //Team of this token
	int moveDir; //Direction this tile is moving to
	int pushDir; //Direction this tile is being pushed in

	const char* pathOBJ; //Stores 3D model path
	const char* pathTEX; //Stores texture path
	const char* pathTEXHL; //Stores highlight texture path

	//Token materials
	SMaterial matHighlight;
	SMaterial matNormal;

	void init(); //Initializes token
	void update(); //Updates this token's visuals

	void PaintVanilla(); //Color token with original color
};

#endif