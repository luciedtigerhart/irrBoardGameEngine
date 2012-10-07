#include <iostream>

#include "IrrEngine.h"

using namespace IrrBoardGameEngine;

class primeTeam
{
private:
public:
	primeTeam();
	~primeTeam();

	bool isAI; //Whether this team is AI-controlled
	bool isActive; //Whether this team will participate in a match

	int idx; //Index of this team

	int assignedRace; //Race chosen by this team
	int assignedTurn; //Turn assigned to this team in this match
	int primevalium; //Amount of resources collected by this team
};

primeTeam::primeTeam() {};
primeTeam::~primeTeam() {};