#ifndef _PRIMETILE_H
#define _PRIMETILE_H

#include <iostream>
#include "IrrEngine.h"
#include "PrimeToken.h"
#include "PrimeTeam.h"

//Hightlight type definitions
//----------------------------

	#define NONE 0
	#define MOVE 1
	#define MOVE_HOVER 2
	#define RESSURRECT 7
	#define RESSURRECT_HOVER 8
	#define PUSH 3
	#define PUSH_HOVER 4
	#define ATTACK 5
	#define ATTACK_HOVER 6

//Tile type definitions
//----------------------------

	#define SAFE_ZONE_TEAM_1 5
	#define SAFE_ZONE_TEAM_2 3
	#define SAFE_ZONE_TEAM_3 2
	#define SAFE_ZONE_TEAM_4 4
	#define GRASS 0
	#define RESOURCE 7
	#define RUINS 1
	#define TRAP 6

//----------------------------

using namespace IrrBoardGameEngine;

class PrimeTile : public IrrTileBehavior
{
private:
	int raceP1, idxP1;
	int raceP2, idxP2;
	int raceP3, idxP3;
	int raceP4, idxP4;

public:
	PrimeTile(PrimeTeam p1, PrimeTeam p2, PrimeTeam p3, PrimeTeam p4);
	~PrimeTile();

	//Highlight effect plane
	ISceneNode* highlightPlane;

	//Ressurrection placement indicator
	IrrToken* ghost;

	//Highlight plane materials
	SMaterial matPlaneNormal;
	SMaterial matPlaneHover;

	void init(); //Initializes tile
	void update(); //Updates highlight when necessary

	void turnOnHighlight(int type); //Activates a type of highlight, or deactivate it with param "NONE"
	void addGhostBehavior(IrrTokenBehavior * behavior); //Activate ghost token
	void loadGhost(); //Load ghost token if this is a safe zone tile

	//Behavior get/set override

	void setInt(char const * key, int value);
	int getInt(char const * key);

	void setBool(char const * key, bool value);
	bool getBool(char const * key);
};

#endif