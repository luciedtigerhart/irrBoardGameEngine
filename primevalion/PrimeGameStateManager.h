#ifndef _PRIMEGAMESTATEMANAGER_H
#define _PRIMEGAMESTATEMANAGER_H

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "PrimePlayState.h"
#include "PrimeGUIManager.h"

using namespace IrrBoardGameEngine;

class PrimeGameStateManager
{
private:
	//Engine
	IrrEngine* engine;

	//Scenes
	IrrScene* loader;
	IrrScene* title;
	IrrScene* credits;
	IrrScene* tutorial;
	IrrScene* match;

	//Game board and camera
	IrrBoard* board;
	IrrGameObject* camera;

	//Lights
	ILightSceneNode* light;

	//Particle systems
	IrrParticleSystem* bloodParticles;
	IrrParticleSystem* abilityParticles;
	IrrParticleSystem* resourceParticlesNW;
	IrrParticleSystem* resourceParticlesNE;
	IrrParticleSystem* resourceParticlesSW;
	IrrParticleSystem* resourceParticlesSE;

	//GUI Manager
	PrimeGUIManager guimgr;
	bool loadComplete;
	int transition, fade, fTimeOutGame, fTimeInGame;

	//Audio
	std::vector<IrrGameObject*> BGM;
	std::vector<IrrGameObject*> SFX;

	//Play State
	PrimePlayState playState;

	//Players
	PrimeTeam player1;
	PrimeTeam player2;
	PrimeTeam player3;
	PrimeTeam player4;

	std::list<IrrToken*>* tokensTeam1;
	std::list<IrrToken*>* tokensTeam2;
	std::list<IrrToken*>* tokensTeam3;
	std::list<IrrToken*>* tokensTeam4;

	//Game flow data

	int turn; //Match turn counter
	int gameGoal; //Amount of resources needed to win
	int playersActive; //How many players are playing
	int tokensActive; //How many tokens each player controls

	//Initialize game
	void Init();

	//Method to set up a match
	void SetupMatch();

		//Sub-methods which compose "SetupMatch()"
		void ResetPlayers();
		void CreateParticles();
		void CreateBoard();
		void LoadTiles();
		void LoadTokens();
		void LoadAudio();
		void SortTurnOrder();

	//Scene management methods
	void ManageLoadingScreen();
	void ManageTitleScreen();
	void ManageTutorialScreen();
	void ManageCreditsScreen();
	void ManageMatch();

public:
	PrimeGameStateManager();
	~PrimeGameStateManager();

	void loop(); //Runs game
	void Update(); //Update game states
};

#endif