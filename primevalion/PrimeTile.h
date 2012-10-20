#ifndef _PRIMETILE_H
#define _PRIMETILE_H

#include <iostream>
#include "IrrEngine.h"

//Hightlight type definitions
//----------------------------

	#define NONE 0
	#define MOVE 1
	#define MOVE_HOVER 2
	#define RESSURRECT 1
	#define RESSURRECT_HOVER 2
	#define PUSH 3
	#define PUSH_HOVER 4
	#define ATTACK 5
	#define ATTACK_HOVER 6

//Tile type definitions
//----------------------------

	#define SAFE_ZONE_TEAM_1 1
	#define SAFE_ZONE_TEAM_2 2
	#define SAFE_ZONE_TEAM_3 3
	#define SAFE_ZONE_TEAM_4 4
	#define GRASS 5
	#define RESOURCE 6
	#define RUINS 7
	#define TRAP 8

//----------------------------

using namespace IrrBoardGameEngine;

class PrimeTile : public IrrTileBehavior
{
private:
public:
	PrimeTile();
	~PrimeTile();

	bool isHighlighted; //Whether this tile must be highlighted
	int highlight; //Type of highlight (movement, pushing, attack, etc.)

	//Highlight nodes, become visible or invisible depending on type of highlight
	IrrGameObject* highlightMove;
	IrrGameObject* highlightMoveHover;
	IrrGameObject* highlightPush;
	IrrGameObject* highlightPushHover;
	IrrGameObject* highlightAttack;
	IrrGameObject* highlightAttackHover;

	void init(); //Initializes tile
	void update(); //Updates highlight when necessary

	void turnOffHighlightsExcept(int exception); //Deactivate all highlights, except for "exception"
};

#endif