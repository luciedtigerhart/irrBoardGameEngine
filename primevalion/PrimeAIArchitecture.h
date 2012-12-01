#ifndef _PRIMEAIARCHITECTURE_H
#define _PRIMEAIARCHITECTURE_H

#include <iostream>
#include "IrrEngine.h"
#include "PrimeToken.h"
#include "Logger.h"

//Action definitions
//----------------------------

	#define STAND 0
	#define MOVE_N 1
	#define MOVE_S 2
	#define MOVE_W 3
	#define MOVE_E 4
	#define ATK_NW 5
	#define ATK_NE 6
	#define ATK_SW 7
	#define ATK_SE 8

	#define NO_DEFAULT false
	#define STAND_AS_DEFAULT true

//----------------------------

using namespace IrrBoardGameEngine;

class PrimeAgent
{
private:
	//Main logger
	Logger* csv;

	//Conditions
	std::string N1, N2, S1, S2, W1, W2, E1, E2, NW, NE, SW, SE;

public:
	PrimeAgent();
	~PrimeAgent();

	//Action (public for convenience)
	std::string move;

	//Initialization method
	void Startup(std::string logFile);

	//Sensor method: get the condition of a tile (empty, ally, enemy, trap or obstacle)
	void GetCondition(std::string* str, IrrToken* token, IrrBoard* board, int i, int j);

	//Sensor method: get state of surrounding tiles
	void Sense(IrrToken* token, IrrBoard* board);

	//Controller method: set a token's action based on its surroundings' state (Finite State Machine)
	bool RunFSM(IrrToken* token, IrrBoard* board, bool stand);

	//Learning method: set action performed in current conditions
	void SetAction(int action);

	//Learning method: write new case for Decision Tree
	void Log(void);
};

#endif