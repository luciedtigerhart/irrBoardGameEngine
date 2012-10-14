#ifndef _PRIMETOKENMANAGER_H
#define _PRIMETOKENMANAGER_H

#include <iostream>
#include "PrimePlayState.h"

using namespace std;

class PrimeTokenManager
{
private:
public:
	PrimeTokenManager();
	~PrimeTokenManager();

	void updateTokens(IrrBoard* board);
};

#endif