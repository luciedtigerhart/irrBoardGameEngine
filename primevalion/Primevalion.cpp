#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <string>
#include <iostream>

#include "IrrEngine.h"
#include "PrimeGameStateManager.h"

using namespace IrrBoardGameEngine;

PrimeGameStateManager Primevalion;

int main() {

	//Run game!
	Primevalion.loop();

	return 0;
}
