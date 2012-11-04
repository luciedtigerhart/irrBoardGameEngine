#include <string>
#include <iostream>

#include "IrrEngine.h"
#include "PrimeGameStateManager.h"

using namespace IrrBoardGameEngine;

PrimeGameStateManager Primevalion;

void loop()
{
	Primevalion.Update();
}

int main() {

	//Run game!
	//Primevalion.loop(loop);
	Primevalion.loop();

	return 0;
}
