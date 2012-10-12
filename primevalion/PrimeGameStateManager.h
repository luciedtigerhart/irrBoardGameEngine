#ifndef _PRIMEGAMESTATEMANAGER_H
#define _PRIMEGAMESTATEMANAGER_H

#include <iostream>
#include "PrimeTileManager.h"
#include "PrimeTokenManager.h"

using namespace std;

class PrimeGameStateManager
{
private:
public:
	PrimeGameStateManager();
	~PrimeGameStateManager();

	//Players
	PrimeTeam player1;
	PrimeTeam player2;
	PrimeTeam player3;
	PrimeTeam player4;
};

#endif