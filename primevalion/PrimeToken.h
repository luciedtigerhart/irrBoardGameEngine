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

	int race; //Race of this token
	int team; //Team of this token

	const char* pathOBJ; //Stores 3D model path
	const char* pathTEX; //Stores texture path

	//Token materials
	SMaterial matHighlight;
	SMaterial matNormal;

	void init(); //Initializes token
	void update(); //Updates this token's visuals
};

#endif