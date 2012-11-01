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
	// General token states

	bool isGhost; //Whether this token is just a ressurrection indicator
	bool isDead; //Whether this token has been killed
	bool isFinished; //Whether this token has already moved
	bool isExtracting; //Whether this token is on an extraction tile
	bool isAbilityActive; //Whether this token's race ability is active

	// Turn action states

	bool isSelected; //Whether this token has been selected for an action
	bool isTargeted; //Whether this token has been targeted for an attack
	bool isGonnaMove; //Whether this token will move to an empty tile
	bool isGonnaBePushed; //Whether this token will be pushed with the next move
	bool isGonnaBeTrapped; //Whether this token will fall onto a trap when pushed

	bool isAnimStarted; //This token has started an animation this turn
	bool isAnimRunning; //One of this token's animations is running
	bool isAnimFinished; //One of this token's animations is finished
	bool isAnimClosed; //All of this token's animations are done for the turn

	// Other attributes

	bool orphan; //If this token has been unattached from its parent
	int race; //Race of this token
	int team; //Team of this token
	int moveDir; //Direction this tile is moving or being pushed to

	// Variables used during translation animation

	float deathCounter; //Used during trap death animation
	float deltaTime; //Also used in trap death animation
	int now, then; //...Same thing.

	int iDest, jDest; //'i' and 'j' positions of destination tile
	Vector destPosition; //World coordinates of destination
	Vector originPosition; //World coordinates of this token before moving

	//3D model and texture path storages

	const char* pathOBJ; //OBJ file path
	const char* pathTEX; //Normal texture (colored texture) path
	const char* pathTEXHL; //Highlight texture (gray texture) path
	const char* pathBBEXT; //Extraction billboard texture
	const char* pathBBICO; //Ability icon billboard texture

	// Token materials

	SMaterial matHighlight;
	SMaterial matNormal;

	// Resource extraction and ability icon billboards

	ISceneNode* billboardExtraction;
	ISceneNode* billboardAbility;

public:
	PrimeToken(PrimeTeam myTeam); //Loads mesh and texture

	void init(); //Initializes token
	void update(); //Updates this token's visuals
	void reset(); //Reset attributes

	void PaintVanilla(); //Color token with original color

	//Behavior get/set override

	void setInt(char const * key, int value);
	int getInt(char const * key);

	void setFloat(char const * key, float value);
	float getFloat(char const * key);

	void setBool(char const * key, bool value);
	bool getBool(char const * key);

	void setVector(char const * key, Vector value);
	Vector getVector(char const * key);
};

#endif