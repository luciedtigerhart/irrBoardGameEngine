#include "PrimeGameStateManager.h"

PrimeGameStateManager::PrimeGameStateManager()
{
	//Initialize players

	player1.idx = 1;
	player2.idx = 2;
	player3.idx = 3;
	player4.idx = 4;

	player1.isActive = player2.isActive = player3.isActive = player4.isActive = true;
	player1.isAI = player2.isAI = player3.isAI = player4.isAI = false;
	player1.assignedTurn = player2.assignedTurn = player3.assignedTurn = player4.assignedTurn = -1;
	player1.assignedRace = player2.assignedRace = player3.assignedRace = player4.assignedRace = KOBOLD;
	player1.primevalium = player2.primevalium = player3.primevalium = player4.primevalium = 0;
};

PrimeGameStateManager::~PrimeGameStateManager() {};