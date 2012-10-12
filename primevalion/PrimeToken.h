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

class PrimeToken : public IrrToken
{
private:
public:
	PrimeToken();
	~PrimeToken();

	bool isDead; //Whether this token has been killed
	bool isFinished; //Whether this token has already moved
	bool isHighlighted; //Whether this token must be highlighted
	int highlight; //Type of highlight (selection, pushing, attack, etc.)
	int race; //Race of this token

	void init(IrrEngine* engine, IrrScene* scene, PrimeTeam team); //Initializes token's mesh and texture
	void update(); //Updates this token's visuals
};

#endif