#ifndef _PRIMETEAM_H
#define _PRIMETEAM_H

#include <iostream>

using namespace std;

class PrimeTeam
{
private:
public:
	PrimeTeam();
	~PrimeTeam();

	bool isAI; //Whether this team is AI-controlled
	bool isActive; //Whether this team will participate in a match
	bool isVictorious; //Whether this team has won the match

	int idx; //Index of this team

	int assignedRace; //Race chosen by this team
	int assignedTurn; //Turn assigned to this team in this match
	int primevalium; //Amount of resources collected by this team
};

#endif