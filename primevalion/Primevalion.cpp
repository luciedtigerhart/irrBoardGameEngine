#include <string>
#include <iostream>

#include "IrrEngine.h"
#include "PrimeGameStateManager.h"

using namespace IrrBoardGameEngine;

PrimeGameStateManager Primevalion;

//Game update method
void game() { Primevalion.Update(); }

int main() {

	//Run game!
	Primevalion.loop(game);

	return 0;
}
