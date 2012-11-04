#include "PrimePlayState.h"

PrimePlayState::PrimePlayState() {};
PrimePlayState::~PrimePlayState() {};

void PrimePlayState::Initialize(IrrEngine* engine, IParticleSystemSceneNode* ps, int players, int tokens, int goal,
								PrimeTeam p1, PrimeTeam p2, PrimeTeam p3, PrimeTeam p4,
								std::list<IrrToken*>* team1, std::list<IrrToken*>* team2,
								std::list<IrrToken*>* team3, std::list<IrrToken*>* team4)
{
	//Get input from engine
	input = engine->getInput();

	// TEMPORARY
	//-----------------------------------------------------------

		//Get particle system from game state manager
		particles = ps;

		//Create blood particles
		IParticleEmitter* particleEmitter = particles->createBoxEmitter(aabbox3d<f32>(-0.5f,-0.5f,-0.5f,0.5f,0.5f,0.5f), // emitter size
													vector3df(0.0f,0.04f,0.0f),   // direction and PARTICLE TRANSLATION SPEED
													20,50,                        // emit rate
													SColor(0,255,255,255),       // darkest color
													SColor(0,255,255,255),       // brightest color
													2000,3000,					// min and max age
													10,							  //angle
													dimension2df(0.2f,0.2f),      // min size
													dimension2df(0.7f,0.7f));     // max size

		particles->setEmitter(particleEmitter);

		particles->getMaterial(0).Lighting = false;
		particles->getMaterial(0).ZWriteEnable = false;
		particles->getMaterial(0).setTexture(0, IrrEngine::getInstance()->getDriver()->getTexture("billboard/particle/particle_blood02.png"));
		particles->getMaterial(0).MaterialType = EMT_TRANSPARENT_VERTEX_ALPHA;

		IParticleAffector* rotator = particles->createRotationAffector(vector3df(0.0f,-200.0f,0.0f));
		IParticleAffector* puller = particles->createGravityAffector(vector3df(0.0f,-0.1f,0.0f));
		IParticleAffector* fader = particles->createFadeOutParticleAffector(SColor(0,0,0,0), 4000); //HIGHER the value, SOONER they fade

		//particles->addAffector(rotator);
		particles->addAffector(puller);
		particles->addAffector(fader);

		rotator->drop();
		puller->drop();
		fader->drop();

		particleEmitter->drop();

		particles->setVisible(false);

	//-----------------------------------------------------------

	//Initializa token lists

	tokensTeam1 = new std::list<IrrToken*>();
	tokensTeam2 = new std::list<IrrToken*>();
	tokensTeam3 = new std::list<IrrToken*>();
	tokensTeam4 = new std::list<IrrToken*>();

	//Clone token lists

	tokensActive = tokens;

	if (p1.isActive) { for (t = team1->begin(); t != team1->end(); t++) tokensTeam1->push_back((*t)); }
	if (p2.isActive) { for (t = team2->begin(); t != team2->end(); t++) tokensTeam2->push_back((*t)); }
	if (p3.isActive) { for (t = team3->begin(); t != team3->end(); t++) tokensTeam3->push_back((*t)); }
	if (p4.isActive) { for (t = team4->begin(); t != team4->end(); t++) tokensTeam4->push_back((*t)); }

	//Clone player teams

	playersActive = players;

	//Player 1...
	player1.idx = p1.idx;
	player1.isAI = p1.isAI;
	player1.isActive = p1.isActive;
	player1.isVictorious = p1.isVictorious;
	player1.assignedRace = p1.assignedRace;
	player1.assignedTurn = p1.assignedTurn;
	player1.primevalium = p1.primevalium;

	//Player 2...
	player2.idx = p2.idx;
	player2.isAI = p2.isAI;
	player2.isActive = p2.isActive;
	player2.isVictorious = p2.isVictorious;
	player2.assignedRace = p2.assignedRace;
	player2.assignedTurn = p2.assignedTurn;
	player2.primevalium = p2.primevalium;

	//Player 3...
	player3.idx = p3.idx;
	player3.isAI = p3.isAI;
	player3.isActive = p3.isActive;
	player3.isVictorious = p3.isVictorious;
	player3.assignedRace = p3.assignedRace;
	player3.assignedTurn = p3.assignedTurn;
	player3.primevalium = p3.primevalium;

	//Player 4...
	player4.idx = p4.idx;
	player4.isAI = p4.isAI;
	player4.isActive = p4.isActive;
	player4.isVictorious = p4.isVictorious;
	player4.assignedRace = p4.assignedRace;
	player4.assignedTurn = p4.assignedTurn;
	player4.primevalium = p4.primevalium;

	//Initialize signals
	signalEndTurn = signalEndMatch = signalBackToTitle = false;

	//Initialize match phase
	phase = MATCH_START;
	matchStart = matchOver = false;
	turnBeginPhase = 0;

	//Initialize goal
	resourcesGoal = goal;

	//Initialize auxiliary variables
	tokenRessurrected = false;
	resourcesVerified = false;
	resourcesExtracted = false;

	//Initialize selected token
	selectedToken = NULL;

	//Initialize "Wait" mini-engine
	wait = 0.0f;
	sleep = 0.0f;
	awake = false;
	then = IrrEngine::getInstance()->getDevice()->getTimer()->getTime();

	//Initialize ressurrection skipping variables
	skipRessurrection = false;
	deadTokensNotRevived = 0;
	safeZoneTilesMax = 0;
	safeZone1TilesOccupied = safeZone2TilesOccupied = 0;
	safeZone3TilesOccupied = safeZone4TilesOccupied = 0;
	safeZone1Full = safeZone2Full = safeZone3Full = safeZone4Full = false;
}

void PrimePlayState::Wait()
{
	//----------------------
	// "Wait" mini-engine:
	//----------------------

	//Calculate frame-independent time
	now = IrrEngine::getInstance()->getDevice()->getTimer()->getTime();
	deltaTime = (float)(now - then) / 1000.f;
	then = now;

	//If just woke up...
	if (awake)
	{
		//Go back to sleep!
		awake = false;
	}

	//If sleep has been set...
	else if (sleep > 0.0f)
	{
		//Update wait
		wait += 1.0f * deltaTime;

		//When wait surpasses sleep time (in seconds)...
		if (wait > sleep)
		{
			//...Reset wait and sleep.
			sleep = wait = 0.0f;

			//Wake up!
			awake = true;
		}
	}
}

bool PrimePlayState::Wait(float seconds)
{
	bool isAwake = false;

	//Wait for "seconds" amount of time
	if (!sleep && !awake) sleep = seconds;

	else if (awake)
	{
		//Finally woke up, wait is over
		isAwake = true;
	}

	return isAwake;
}

void PrimePlayState::SetTurnPlayer(int turn)
{
	int counter = 0;

	//Iterate through turn count to find out if this
	//is the first, second, third or fourth player's turn...
	for (int iterator = 1; iterator <= turn; iterator++)
	{
		counter++;
		if (counter > playersActive) counter = 1;
	}

	//Set "turnPlayer" as the current player
	if (player1.assignedTurn == counter) turnPlayer = player1.idx;
	else if (player2.assignedTurn == counter) turnPlayer = player2.idx;
	else if (player3.assignedTurn == counter) turnPlayer = player3.idx;
	else if (player4.assignedTurn == counter) turnPlayer = player4.idx;
}

void PrimePlayState::SetPushLine(bool clicked, int dir, IrrBoard* board, int iStart, int jStart)
{
	bool breakScan = false;

	int iTile = -1;
	int jTile = -1;
	int iAdd = -1;
	int jAdd = -1;
	int iBreak = -1;
	int jBreak = -1;

	//Configure search based on push direction
	if (dir == WEST) { iBreak = -1; jBreak = 0; iAdd = 0; jAdd = -1; }
	else if (dir == EAST) { iBreak = -1; jBreak = 9; iAdd = 0; jAdd = 1; }
	else if (dir == NORTH) { iBreak = 0; jBreak = -1; iAdd = -1; jAdd = 0; }
	else if (dir == SOUTH) { iBreak = 9; jBreak = -1; iAdd = 1; jAdd = 0; }

	iTile = iStart;
	jTile = jStart;

	//Find tokens in a line, starting at token to be pushed
	while (!breakScan)
	{
		//If a token has been found...
		if (board->board[iTile][jTile]->token != NULL)
		{
			//If mouse button has been clicked and push move confirmed...
			if (clicked)
			{
				//Mark this token for pushing
				board->board[iTile][jTile]->token->getBehavior(0)->setBool("isGonnaBePushed", true);
				board->board[iTile][jTile]->token->getBehavior(0)->setInt("moveDir", dir);

				//Startup this token's animation
				board->board[iTile][jTile]->token->getBehavior(0)->setBool("isAnimStarted", true);
			}

			//Otherwise, if mouse is just hovering a pushable token...
			else
			{
				//Highlight this token to show player which tokens will be pushed
				board->board[iTile][jTile]->token->isHighlighted = true;
				board->board[iTile][jTile]->token->highlight = PUSH_HOVER;
			}
		}

		//If a free tile has been found, break scan
		else if (board->board[iTile][jTile]->token == NULL) breakScan = true;

		//If an obstacle has been found, break scan
		else if (board->board[iTile][jTile]->inf == RUINS) breakScan = true;

		//If "iBreak" or "jBreak" has been achieved, it means the board's
		//border has been reached and the scan should be finished up

		if (iTile == iBreak || jTile == jBreak) breakScan = true;

		//Iterate scan
		iTile += iAdd;
		jTile += jAdd;
	}
}

bool PrimePlayState::PlayIsValid(int play, int dir, IrrBoard* board, int i, int j)
{
	bool isValid = false;
	bool breakScan = false;

	int iTile = -1;
	int jTile = -1;
	int iAdd = -1;
	int jAdd = -1;
	int iBreak = -1;
	int jBreak = -1;

	int lastTileFound = 0;
	int tilesChecked = 0;
	int freeTiles = 0;
	int heavyTokens = 0;

	//Validate Push move
	if (play == PUSH)
	{
		//Configure search based on push direction
		if (dir == WEST) { iBreak = -1; jBreak = 0; iAdd = 0; jAdd = -1; }
		else if (dir == EAST) { iBreak = -1; jBreak = 9; iAdd = 0; jAdd = 1; }
		else if (dir == NORTH) { iBreak = 0; jBreak = -1; iAdd = -1; jAdd = 0; }
		else if (dir == SOUTH) { iBreak = 9; jBreak = -1; iAdd = 1; jAdd = 0; }

		iTile = i;
		jTile = j;

		//Find obstacles and tokens in a line, starting at token to be pushed
		while (!breakScan)
		{
			//If an obstacle has been found...
			if (board->board[iTile][jTile]->inf == RUINS)
			{
				//If last tile found was a token...
				if (lastTileFound == TOKEN)
				{
					//If so far, only tokens have been found...
					if (freeTiles == 0)
					{
						//Cannot push line of tokens past obstacles
						isValid = false;

						//Break "while" loop
						breakScan = true;
					}

					//Else, if free tiles have been found...
					else if (freeTiles > 0)
					{
						//If at least 1 free tile has been found
						//between tokens, then they can be pushed
						isValid = true;

						//Break "while" loop
						breakScan = true;
					}
				}

				//Else, if last tile found was a
				//free tile (trap or grass)...
				else if (lastTileFound == FREE)
				{
					//If at least 1 free tile has been found
					//between tokens, then they can be pushed
					isValid = true;

					//Break "while" loop
					breakScan = true;
				}

				lastTileFound = RUINS;
			}

			//If a free tile has been found...
			else if (board->board[iTile][jTile]->token == NULL)
			{
				lastTileFound = FREE;
				freeTiles++;

				//Free tiles inbetween heavy tokens enable pushing
				if (heavyTokens > 0) --heavyTokens;
			}

			//If a token has been found...
			else if (board->board[iTile][jTile]->token != NULL)
			{
				lastTileFound = TOKEN;

				//If this token is a Troll with its ability activated,
				//and its not in the current player's team...
				if (board->board[iTile][jTile]->token->getBehavior(0)->getInt("race") == TROLL
					&& board->board[iTile][jTile]->token->getBehavior(0)->getBool("isAbilityActive")
					&& board->board[iTile][jTile]->token->player != turnPlayer)
				{
					heavyTokens++;

					//If more than one of these have been found in a line...
					if (heavyTokens >= 2)
					{
						//Cannot push 2 or more aligned Trolls
						isValid = false;

						//Break "while" loop
						breakScan = true;
					}
				}
			}

			//If "iBreak" or "jBreak" has been achieved, it means the board's
			//border has been reached and the scan should be finished up
			if (iTile == iBreak || jTile == jBreak)
			{
				//If only tokens have been found...
				if (freeTiles == 0)
				{
					//Cannot push line of tokens past border
					isValid = false;
				}

				//Else, if free tiles have been found
				//and no heavy tokens disallow movement...
				else if (freeTiles > 0 && heavyTokens < 2)
				{
					//If at least 1 free tile has been found
					//between tokens, then they can be pushed
					isValid = true;
				}

				//Break "while" loop
				breakScan = true;
			}

			//Iterate scan
			iTile += iAdd;
			jTile += jAdd;
		}
	}

	//Validate Attack move
	else if (play == ATTACK)
	{
		//If trying to attack someone from the same team...
		if (board->board[i][j]->token->player == turnPlayer)
		{
			//Invalid move!
			isValid = false;
		}

		//If trying to attack someone in a safe zone...
		else if (board->board[i][j]->token->parentNode->inf == SAFE_ZONE_TEAM_1
				 || board->board[i][j]->token->parentNode->inf == SAFE_ZONE_TEAM_2
				 || board->board[i][j]->token->parentNode->inf == SAFE_ZONE_TEAM_3
				 || board->board[i][j]->token->parentNode->inf == SAFE_ZONE_TEAM_4)
		{
			//Invalid move!
			isValid = false;
		}

		//Otherwise, its a valid attack move!
		else isValid = true;
	}

	//Return validation result
	return isValid;
}

bool PrimePlayState::TokenHasTranslated(IrrToken* token, float speed)
{
	bool destReached = false;
	vector3df newRelativePosition;

	float okDiff = 0.02f * speed; //Acceptable difference in distance between token and destination
	float xDiff, yDiff, zDiff;
	float xStep, yStep, zStep;

	//Get token's translation vectors
	Vector origin, destination;

	origin.x = token->getBehavior(0)->getFloat("originPosition.x");
	origin.y = token->getBehavior(0)->getFloat("originPosition.y");
	origin.z = token->getBehavior(0)->getFloat("originPosition.z");

	destination.x = token->getBehavior(0)->getFloat("destPosition.x");
	destination.y = token->getBehavior(0)->getFloat("destPosition.y");
	destination.z = token->getBehavior(0)->getFloat("destPosition.z");

	//Get current distance between token and destination
	xDiff = destination.x - token->node->getAbsolutePosition().X;
	yDiff = destination.y - token->node->getAbsolutePosition().Y;
	zDiff = destination.z - token->node->getAbsolutePosition().Z;

	//Decreases speed the closer token gets to destination (trap fall only)
	speed -= abs((destination.y - origin.y) - yDiff);
	if (speed < 0.05f) speed = 0.05f; //Minimum speed

	//If distance between token and destination is still higher than "okDiff"...
	if (abs(xDiff) > okDiff || abs(yDiff) > okDiff || abs(zDiff) > okDiff)
	{
		//...Then destination hasn't been reached.

		//Calculate next step offset
		xStep = ((destination.x - origin.x) / 100) * speed;
		yStep = ((destination.y - origin.y) / 100) * speed;
		zStep = ((destination.z - origin.z) / 100) * speed;

		//Calculate new position
		newRelativePosition.X = token->node->getPosition().X + xStep;
		newRelativePosition.Y = token->node->getPosition().Y + yStep;
		newRelativePosition.Z = token->node->getPosition().Z + zStep;
		
		//Move token closer to destination
		token->node->setPosition(newRelativePosition);
	}

	//Otherwise, if token is close enough to destination...
	else
	{
		//...Consider destination as reached.
		destReached = true;
	}

	//Report whether destination is reached
	return destReached;
}

void PrimePlayState::AnimateToken(IrrToken* token, IrrBoard* board, float speed)
{
	//Pass animation states to another variable (decreases size of "if" statements below)
	bool animStarted = token->getBehavior(0)->getBool("isAnimStarted");
	bool animRunning = token->getBehavior(0)->getBool("isAnimRunning");
	bool animFinished = token->getBehavior(0)->getBool("isAnimFinished");

	//! IMPORTANT !
	//---------------
	//Animations happen in a specific order: 1st, attack death animation (tiles which
	//were attacked diagonally). 2nd, simple movement animation (a token moves to an
	//empty tile) and/or push movement animations (tokens get pushed by the selected token).
	//3rd and last, trap death animation (token falls on a trap after being pushed).
	//This order must always be respected, and an animation must never start before all
	//animations that precede it are finished.

	//----------------------------------------
	// 1st Priority: ATTACK DEATH ANIMATION
	//----------------------------------------

	//If "isTargeted" is true, then this token is suffering an attack
	//coming from a diagonal tile, where there's certainly an enemy token.

	if (token->getBehavior(0)->getBool("isTargeted"))
	{
		animAttackDeath = true;

		//If this token has been marked for animation, but hasn't started running it yet...
		if (animStarted && !animRunning && !animFinished)
		{
			//Disable any active abilities
			token->getBehavior(0)->setBool("isAbilityActive", false);

			//Start animation!
			token->getBehavior(0)->setBool("isAnimRunning", true);

			particles->setPosition(vector3df(token->node->getAbsolutePosition().X,
											 token->node->getAbsolutePosition().Y + 2.5f,
											 token->node->getAbsolutePosition().Z));

			particles->setVisible(true);
		}

		//If this token's animation is currently running...
		else if (animStarted && animRunning && !animFinished)
		{
			// TEMPORARY ANIMATION
			//-----------------------

				if (Wait(1.0f))
				{
					token->getBehavior(0)->setBool("isAnimRunning", false);
					token->getBehavior(0)->setBool("isAnimFinished", true);
				}

			//-----------------------
		}

		//If this token's animation is over...
		else if (animStarted && !animRunning && animFinished)
		{
			//Terminate this token's animations
			token->getBehavior(0)->setBool("isAnimClosed", true);

			//Disable future moves for this token, in this turn
			token->getBehavior(0)->setBool("isFinished", true);

			//Kill token!
			token->getBehavior(0)->setBool("isDead", true);

			//Set this token as the "killed token"
			killedToken = token;

			particles->setVisible(false);
		}

		//If animation is done, inform the other tokens
		if (token->getBehavior(0)->getBool("isAnimClosed")) animAttackDeath = false;
	}

	//----------------------------------------
	// 2nd Priority: MOVE/PUSH ANIMATION
	//----------------------------------------

	//If "isGonnaMove" is true, then this is the selected token.
	//If "isGonnaBePushed" is true, then this token will be pushed by selected token.
	//Either way, this token must be moved, but will only do so after all attack
	//death animations are finished.
	
	else if (!animAttackDeath && !token->getBehavior(0)->getBool("isAnimClosed") &&
			(token->getBehavior(0)->getBool("isGonnaMove") || token->getBehavior(0)->getBool("isGonnaBePushed")))
	{
		//cout<<animAttackDeath<<endl;

		if (token->getBehavior(0)->getBool("isGonnaMove")) animSimpleMove = true;
		if (token->getBehavior(0)->getBool("isGonnaBePushed")) animPushMove = true;

		//If this token has been marked for animation, but hasn't started running it yet...
		if (animStarted && !animRunning && !animFinished)
		{
			//Get destination tile positions
			iDest = GetDestinationTile(token->getBehavior(0)->getInt("moveDir"), token->parentNode->posi, token->parentNode->posj, I_TILE);
			jDest = GetDestinationTile(token->getBehavior(0)->getInt("moveDir"), token->parentNode->posi, token->parentNode->posj, J_TILE);
					
			//Pass destination tile positions to token
			token->getBehavior(0)->setInt("iDest", iDest);
			token->getBehavior(0)->setInt("jDest", jDest);
					
			//Pass destination coordinates to token
			token->getBehavior(0)->setFloat("destPosition.x", board->board[iDest][jDest]->node->getPosition().X);
			token->getBehavior(0)->setFloat("destPosition.y", board->board[iDest][jDest]->node->getPosition().Y);
			token->getBehavior(0)->setFloat("destPosition.z", board->board[iDest][jDest]->node->getPosition().Z);

			//Pass origin coordinates to token
			token->getBehavior(0)->setFloat("originPosition.x", token->node->getAbsolutePosition().X);
			token->getBehavior(0)->setFloat("originPosition.y", token->node->getAbsolutePosition().Y);
			token->getBehavior(0)->setFloat("originPosition.z", token->node->getAbsolutePosition().Z);

			//If this token is being pushed, and its final destination is a trap...
			if (token->getBehavior(0)->getBool("isGonnaBePushed"))
			{
				if (board->board[iDest][jDest]->inf == TRAP)
				{
					//Mark this token for the trap death animation
					token->getBehavior(0)->setBool("isGonnaBeTrapped", true);
				}
			}

			//Start animation!
			token->getBehavior(0)->setBool("isAnimRunning", true);
		}
				
		//If this token's animation is currently running...
		else if (animStarted && animRunning && !animFinished)
		{
			//Translate token, and when destination has been reached...
			if (TokenHasTranslated(token, speed))
			{
				//Finish up animation
				token->getBehavior(0)->setBool("isAnimRunning", false);
				token->getBehavior(0)->setBool("isAnimFinished", true);
			}
		}

		//If this is the selected token and the move animation is over...
		else if (animStarted && !animRunning && animFinished
				 && token->getBehavior(0)->getBool("isGonnaMove"))
		{
			//...And all pushed tokens have already moved...
			if (PushedTokensSnapped(board))
			{
				//Reset relative position
				token->node->setPosition(vector3df(0,0,0));

				//If snap to new position has been successful...
				if (board->moveToken(token->parentNode->posi, token->parentNode->posj,
									 token->getBehavior(0)->getInt("iDest"), token->getBehavior(0)->getInt("jDest")))
				{
					//Terminate move animation
					token->getBehavior(0)->setBool("isAnimClosed", true);

					//Inform other tokens that the selected token's movement has ended
					animSimpleMove = false;
				}
			}
		}
	}

	//----------------------------------------
	// 3rd Priority: TRAP DEATH ANIMATION
	//----------------------------------------

	//If "isGonnaBeTrapped" is true, then this token will suffer a bloody death in a trap,
	//but only after all attack death animations and movement animations are finished.

	else if (!animAttackDeath && !animSimpleMove && !animPushMove &&
			 token->getBehavior(0)->getBool("isGonnaBeTrapped"))
	{
		animTrapDeath = true;

		//If this token has been marked for animation, but hasn't started running it yet...
		if (animStarted && !animRunning && !animFinished)
		{
			//Get tile height
			int trapHeight = board->tile_height;

			//Pass destination coordinates to token (deeper into the trap hole)
			token->getBehavior(0)->setFloat("destPosition.x", token->node->getAbsolutePosition().X);
			token->getBehavior(0)->setFloat("destPosition.y", token->node->getAbsolutePosition().Y - trapHeight);
			token->getBehavior(0)->setFloat("destPosition.z", token->node->getAbsolutePosition().Z);

			//Pass origin coordinates to token (current position)
			token->getBehavior(0)->setFloat("originPosition.x", token->node->getAbsolutePosition().X);
			token->getBehavior(0)->setFloat("originPosition.y", token->node->getAbsolutePosition().Y);
			token->getBehavior(0)->setFloat("originPosition.z", token->node->getAbsolutePosition().Z);

			//Disable any active abilities
			token->getBehavior(0)->setBool("isAbilityActive", false);

			//Start animation!
			token->getBehavior(0)->setBool("isAnimRunning", true);

			particles->setPosition(vector3df(token->node->getAbsolutePosition().X,
											 token->node->getAbsolutePosition().Y + 2.5f,
											 token->node->getAbsolutePosition().Z));

			particles->setVisible(true);
		}

		//If this token's animation is currently running...
		else if (animStarted && animRunning && !animFinished)
		{
			//Translate token, and when destination has been reached...
			if (TokenHasTranslated(token, speed * 1.5f))
			{
				//Finish up animation
				token->getBehavior(0)->setBool("isAnimRunning", false);
				token->getBehavior(0)->setBool("isAnimFinished", true);
			}
		}

		//If this token's animation is over...
		else if (animStarted && !animRunning && animFinished)
		{
			//Terminate this token's animations
			token->getBehavior(0)->setBool("isAnimClosed", true);

			//Disable future moves for this token, in this turn
			token->getBehavior(0)->setBool("isFinished", true);

			//Kill token!
			token->getBehavior(0)->setBool("isDead", true);

			//Set this token as the "killed token"
			killedToken = token;

			particles->setVisible(false);
		}

		//If animation is done, inform the other tokens
		if (token->getBehavior(0)->getBool("isAnimClosed")) animTrapDeath = false;
	}
}

bool PrimePlayState::PushedTokensSnapped(IrrBoard* board)
{
	IrrToken* tempToken;
	
	bool everyTokenSnapped = false;
	bool breakScan = false;

	int foundTokens = 0, snappedTokens = 0;

	int iStart = -1;
	int jStart = -1;
	int iTile = -1;
	int jTile = -1;
	int iAdd = -1;
	int jAdd = -1;
	int iBreak = -1;
	int jBreak = -1;

	int dir = selectedToken->getBehavior(0)->getInt("moveDir");

	//If this is not a diagonal direction (which would mean this is an attack, not a push move)...
	if (dir != NORTHWEST && dir != NORTHEAST && dir != SOUTHWEST && dir != SOUTHEAST)
	{
		//Configure search for a direction contrary to push direction, so tiles
		//farthest to the selected token are moved first

		if (dir == WEST) { iStart = selectedToken->parentNode->posi; jStart = 0;
						   iBreak = -1; jBreak = selectedToken->parentNode->posj; iAdd = 0; jAdd = 1; }
		else if (dir == EAST) { iStart = selectedToken->parentNode->posi; jStart = 9;
								iBreak = -1; jBreak = selectedToken->parentNode->posj; iAdd = 0; jAdd = -1; }
		else if (dir == NORTH) { iStart = 0; jStart = selectedToken->parentNode->posj;
								 iBreak = selectedToken->parentNode->posi; jBreak = -1; iAdd = 1; jAdd = 0; }
		else if (dir == SOUTH) { iStart = 9; jStart = selectedToken->parentNode->posj;
								 iBreak = selectedToken->parentNode->posi; jBreak = -1; iAdd = -1; jAdd = 0; }

		iTile = iStart;
		jTile = jStart;

		//Find pushed tokens in a line, starting at opposite board border
		while (!breakScan)
		{
			//If a token has been found...
			if (board->board[iTile][jTile]->token != NULL)
			{
				//If this token has just been pushed and its animations haven't been terminated yet...
				if (board->board[iTile][jTile]->token->getBehavior(0)->getBool("isGonnaBePushed")
					&& !board->board[iTile][jTile]->token->getBehavior(0)->getBool("isAnimClosed"))
				{
					//A pushed token has been found
					foundTokens++;

					//If this token's translation animation has finished...
					if (board->board[iTile][jTile]->token->getBehavior(0)->getBool("isAnimFinished"))
					{
						tempToken = board->board[iTile][jTile]->token;

						//Reset relative position
						tempToken->node->setPosition(vector3df(0,0,0));

						//If snap to new position has been successful...
						if (board->moveToken(tempToken->parentNode->posi, tempToken->parentNode->posj,
											 tempToken->getBehavior(0)->getInt("iDest"), tempToken->getBehavior(0)->getInt("jDest")))
						{
							//A pushed token has been snapped
							snappedTokens++;
				
							//If this token is marked for a painful trap death animation...
							if (tempToken->getBehavior(0)->getBool("isGonnaBeTrapped"))
							{
								//Unmark push animation (it should be finished by now)
								tempToken->getBehavior(0)->setBool("isGonnaBePushed", false);

								//Reset a couple animation states
								tempToken->getBehavior(0)->setBool("isAnimRunning", false);
								tempToken->getBehavior(0)->setBool("isAnimFinished", false);
							}

							//Otherwise, if this token is still safe after being pushed
							else
							{
								//Terminate all animations
								tempToken->getBehavior(0)->setBool("isAnimClosed", true);
							}

							//Inform other tokens this one's push animation is over
							animPushMove = false;
						}
					}
				}
			}

			//If "iBreak" or "jBreak" has been achieved, it means the selected
			//token has been reached and the scan should be finished up

			if (iTile == iBreak || jTile == jBreak) breakScan = true;

			//Iterate scan
			iTile += iAdd;
			jTile += jAdd;
		}
	}

	//If all found tokens have been snapped, everything's good
	if (foundTokens == snappedTokens) everyTokenSnapped = true;

	return everyTokenSnapped;
}

bool PrimePlayState::EnemyTokenKilled(IrrBoard* board)
{
	bool enemyWillDie = false;

	//If a token was killed by an Attack or died by falling into a trap
	if (killedToken != NULL)
	{
		//Only tokens of enemy teams are valid (killing allies doesn't count)
		if (killedToken->player != turnPlayer) enemyWillDie = true;
	}

	return enemyWillDie;
}

bool PrimePlayState::TrollBesideMe(IrrToken* token, IrrBoard* board)
{
	bool trollBesideMe = false;

	//Grab adjacent tile positions
	int up[2] = { token->parentNode->posi - 1, token->parentNode->posj };
	int down[2] = { token->parentNode->posi + 1, token->parentNode->posj };
	int left[2] = { token->parentNode->posi, token->parentNode->posj - 1 };
	int right[2] = { token->parentNode->posi, token->parentNode->posj + 1 };

	//Checking if adjacent tiles are valid and if there's a token on them

	if (up[0] > -1 && up[0] < 10 && up[1] > -1 && up[1] < 10)
	{
		if (board->board[up[0]][up[1]]->token != NULL)
		{
			//If adjacent token is a Troll from the same team, which is not dying...
			if (board->board[up[0]][up[1]]->token->getBehavior(0)->getInt("race") == TROLL
				&& !board->board[up[0]][up[1]]->token->getBehavior(0)->getBool("isGonnaBeTrapped")
				&& !board->board[up[0]][up[1]]->token->getBehavior(0)->getBool("isTargeted")
				&& board->board[up[0]][up[1]]->token->player == token->player)
			{
				trollBesideMe = true;
			}
		}
	}

	if (down[0] > -1 && down[0] < 10 && down[1] > -1 && down[1] < 10)
	{
		if (board->board[down[0]][down[1]]->token != NULL)
		{
			//If adjacent token is a Troll from the same team, which is not dying...
			if (board->board[down[0]][down[1]]->token->getBehavior(0)->getInt("race") == TROLL
				&& !board->board[down[0]][down[1]]->token->getBehavior(0)->getBool("isGonnaBeTrapped")
				&& !board->board[down[0]][down[1]]->token->getBehavior(0)->getBool("isTargeted")
				&& board->board[down[0]][down[1]]->token->player == token->player)
			{
				trollBesideMe = true;
			}
		}
	}

	if (left[0] > -1 && left[0] < 10 && left[1] > -1 && left[1] < 10)
	{
		if (board->board[left[0]][left[1]]->token != NULL)
		{
			//If adjacent token is a Troll from the same team, which is not dying...
			if (board->board[left[0]][left[1]]->token->getBehavior(0)->getInt("race") == TROLL
				&& !board->board[left[0]][left[1]]->token->getBehavior(0)->getBool("isGonnaBeTrapped")
				&& !board->board[left[0]][left[1]]->token->getBehavior(0)->getBool("isTargeted")
				&& board->board[left[0]][left[1]]->token->player == token->player)
			{
				trollBesideMe = true;
			}
		}
	}

	if (right[0] > -1 && right[0] < 10 && right[1] > -1 && right[1] < 10)
	{
		if (board->board[right[0]][right[1]]->token != NULL)
		{
			//If adjacent token is a Troll from the same team, which is not dying...
			if (board->board[right[0]][right[1]]->token->getBehavior(0)->getInt("race") == TROLL
				&& !board->board[right[0]][right[1]]->token->getBehavior(0)->getBool("isGonnaBeTrapped")
				&& !board->board[right[0]][right[1]]->token->getBehavior(0)->getBool("isTargeted")
				&& board->board[right[0]][right[1]]->token->player == token->player)
			{
				trollBesideMe = true;
			}
		}
	}

	//Return whether there's a big, scary Troll beside me
	return trollBesideMe;
}

void PrimePlayState::RessurrectToken(IrrToken* token, IrrBoard* board, int i, int j)
{
	//If this token's team is the current playing team
	if (token->player == turnPlayer)
	{
		//If this token is dead and the highlighted safe zone tile is empty
		if (token->getBehavior(0)->getBool("isDead") && board->board[i][j]->token == NULL)
		{
			//Re-activate token
			token->setActive(true);
			token->getBehavior(0)->setBool("isDead", false);

			//Place token at the safe zone!
			if (board->addToken(i, j, token))
			{
				//Make sure the token cannot move this turn
				token->getBehavior(0)->setBool("isFinished", true);
			}

			//Disable highlight on safe zone tiles momentarily
			tokenRessurrected = true;
		}
	}
}

void PrimePlayState::VerifySafeZoneOccupation(IrrBoard* board)
{
	int totalSafeZone1Tiles = 0;

	//Clear ressurrection skipping variables
	safeZone1TilesOccupied = safeZone2TilesOccupied = 0;
	safeZone3TilesOccupied = safeZone4TilesOccupied = 0;
	safeZone1Full = safeZone2Full = safeZone3Full = safeZone4Full = false;
	skipRessurrection = false;

	//Scan the whole board
	for (int i=0; i < board->tile_i; i++)
	{
		for (int j=0; j < board->tile_j; j++)
		{
			//Count occupied tiles in all safe zones

			if (board->board[i][j]->inf == SAFE_ZONE_TEAM_1 && board->board[i][j]->token != NULL) { safeZone1TilesOccupied++; }
			else if (board->board[i][j]->inf == SAFE_ZONE_TEAM_2 && board->board[i][j]->token != NULL) { safeZone2TilesOccupied++; }
			else if (board->board[i][j]->inf == SAFE_ZONE_TEAM_3 && board->board[i][j]->token != NULL) { safeZone3TilesOccupied++; }
			else if (board->board[i][j]->inf == SAFE_ZONE_TEAM_4 && board->board[i][j]->token != NULL) { safeZone4TilesOccupied++; }

			//If total amount of safe zone tiles hasn't been calculated yet...
			if (safeZoneTilesMax == 0)
			{
				//Count team 1's safe zone tiles
				if (board->board[i][j]->inf == SAFE_ZONE_TEAM_1) totalSafeZone1Tiles++;
			}
		}
	}

	//Determine total amount of safe zone tiles from team 1's tiles
	if (safeZoneTilesMax == 0) safeZoneTilesMax = totalSafeZone1Tiles;

	//If all safe zone tiles of a team are occupied, mark that safe zone as full

	if (safeZone1TilesOccupied >= safeZoneTilesMax) safeZone1Full = true;
	if (safeZone2TilesOccupied >= safeZoneTilesMax) safeZone2Full = true;
	if (safeZone3TilesOccupied >= safeZoneTilesMax) safeZone3Full = true;
	if (safeZone4TilesOccupied >= safeZoneTilesMax) safeZone4Full = true;

	//If all safe zone tiles of the current player are occupied...
	if ((turnPlayer == player1.idx && safeZone1Full) || (turnPlayer == player2.idx && safeZone2Full)
		|| (turnPlayer == player3.idx && safeZone3Full) || (turnPlayer == player4.idx && safeZone4Full))
	{
		//This player is unable to ressurrect dead tokens
		skipRessurrection = true;
	}
}

void PrimePlayState::VerifyResourceExtraction(IrrBoard* board)
{
	//Scan the whole board
	for (int i=0; i < board->tile_i; i++)
	{
		for (int j=0; j < board->tile_j; j++)
		{
			//If a resource tile has a token on it...
			if (board->board[i][j]->inf == RESOURCE && board->board[i][j]->token != NULL)
			{
				//Activate this token's extraction state
				board->board[i][j]->token->getBehavior(0)->setBool("isExtracting", true);

				//Add Primevalium to this token's team

				if (board->board[i][j]->token->player == player1.idx)
				{
					player1.primevalium += 100;
					if (player1.assignedRace == KOBOLD) player1.primevalium += 60;
				}

				else if (board->board[i][j]->token->player == player2.idx)
				{
					player2.primevalium += 100;
					if (player2.assignedRace == KOBOLD) player2.primevalium += 60;
				}

				else if (board->board[i][j]->token->player == player3.idx)
				{
					player3.primevalium += 100;
					if (player3.assignedRace == KOBOLD) player3.primevalium += 60;
				}

				else if (board->board[i][j]->token->player == player4.idx)
				{
					player4.primevalium += 100;
					if (player4.assignedRace == KOBOLD) player4.primevalium += 60;
				}

				resourcesExtracted = true;
			}
		}
	}

	//If a player has reached the goal, set it as victorious

	if (player1.primevalium >= resourcesGoal) player1.isVictorious = true;
	if (player2.primevalium >= resourcesGoal) player2.isVictorious = true;
	if (player3.primevalium >= resourcesGoal) player3.isVictorious = true;
	if (player4.primevalium >= resourcesGoal) player4.isVictorious = true;
}

void PrimePlayState::ClearHighlights(IrrBoard* board)
{
	//Scan the whole board
	for (int i=0; i < board->tile_i; i++)
	{
		for (int j=0; j < board->tile_j; j++)
		{
			//Deactivate tile highlights
			board->board[i][j]->isHighlighted = false;
			board->board[i][j]->highlight = NONE;

			//Deactivate token highlights
			if (board->board[i][j]->token != NULL)
			{
				board->board[i][j]->token->isHighlighted = false;
				board->board[i][j]->token->highlight = NONE;
			}
		}
	}
}

void PrimePlayState::SwapPhase(IrrBoard* board)
{
	int remainingTokens = 0, finishedTokens = 0;

	//Begin the battle
	if (phase == MATCH_START)
	{
		//Start match for real only after 2 seconds,
		//during which "Sorting turn order" message is shown.

		if (!matchStart && Wait(0.5f)) matchStart = true;

		else if (matchStart && Wait(2.0f))
		{
			phase = TURN_START;
			matchStart = false;
		}
	}

	//Show new turn messages and begin turn
	else if (phase == TURN_START)
	{
		//Turn has begun!
		if (turnBeginPhase == 0)
		{
			turnOver = false;
			turnBeginPhase = NO_MESSAGE_AT_ONE;
		}

		//...Actually, it only really begins after 3 seconds,
		//during which the "Player X Turn" message is shown.
		
		else if (turnBeginPhase == NO_MESSAGE_AT_ONE && Wait(0.5f)) turnBeginPhase = TURN_MESSAGE_AT_TWO;
		else if (turnBeginPhase == TURN_MESSAGE_AT_TWO && Wait(2.5f)) turnBeginPhase = NO_MESSAGE_AT_THREE;
		else if (turnBeginPhase == NO_MESSAGE_AT_THREE && Wait(0.5f))
		{
			//Decrement ability cooldown for all units
			UpdateCooldown();

			//First step of a new turn is to ressurrect dead tokens
			phase = RESSURRECTION_PLACEMENT;

			turnBeginPhase = 0;
		}
	}

	//Find dead tokens and decide whether ressurrection should be performed
	if (phase == RESSURRECTION_PLACEMENT)
	{
		remainingTokens = GetRemainingTokens(DEAD_TOKENS, false, false);

		//Check if there's at least 1 free safe zone tile
		VerifySafeZoneOccupation(board);

		//Force ressurrection skipping if "End Match" button is pressed
		if (signalEndMatch) skipRessurrection = true;

		//If there are no dead tokens or ressurrection can't be performed
		//because all safe zone tiles are occupied, go to next phase
		if (!tokenRessurrected && (remainingTokens == 0 || skipRessurrection))
		{
			//Store how many dead tokens could not be revived, in case of skipping
			if (skipRessurrection)	
			{
				deadTokensNotRevived = remainingTokens;
				skipRessurrection = false;
			}

			//Don't forget to reset action states
			ResetTokenActionStates();

			phase = PLAY_SELECTION;
		}
	}

	//Find tokens which have moved and decide if turn is over
	else if (phase == PLAY_SELECTION)
	{
		//If player has pressed the "End Turn" button...
		if (signalEndTurn || signalEndMatch)
		{
			//Set all of current player's tokens as finished
			FinishTokens();
		}

		//Count finished tokens
		finishedTokens = GetRemainingTokens(false, FINISHED_TOKENS, false);

		//If all tokens are finished, go to next phase
		if (finishedTokens >= (tokensActive - deadTokensNotRevived))
		{
			//Wait for half a second
			if (Wait(0.4f))
			{
				//Reset signal
				signalEndTurn = false;

				//Don't forget to reset action states
				ResetTokenActionStates();

				//Enable movement for all alive tokens in the next turn

				for (t = tokensTeam1->begin(); t != tokensTeam1->end(); t++) (*t)->getBehavior(0)->setBool("isFinished", false);
				for (t = tokensTeam2->begin(); t != tokensTeam2->end(); t++) (*t)->getBehavior(0)->setBool("isFinished", false);
				for (t = tokensTeam3->begin(); t != tokensTeam3->end(); t++) (*t)->getBehavior(0)->setBool("isFinished", false);
				for (t = tokensTeam4->begin(); t != tokensTeam4->end(); t++) (*t)->getBehavior(0)->setBool("isFinished", false);

				//Dead tokens will stay dead
				deadTokensNotRevived = 0;

				//Time for resource extraction!
				phase = TURN_END;
			}
		}
	}

	//Find tokens which animation hasn't finished yet
	else if (phase == ANIMATION_EXECUTION)
	{
		remainingTokens = GetRemainingTokens(false, false, ANIMATED_TOKENS);

		//If all tokens have finished their animations, go back to play selection
		if (remainingTokens == 0)
		{
			//Disable future moves for selected token, in this turn
			if (selectedToken->getBehavior(0)->getBool("isSelected"))
			{
				selectedToken->getBehavior(0)->setBool("isFinished", true);
				selectedToken->getBehavior(0)->setBool("isSelected", false);
			}

			if (Wait(0.3f))
			{
				//Reset selected token and killed token
				selectedToken = NULL;
				killedToken = NULL;

				//Don't forget to reset action states
				ResetTokenActionStates();

				phase = PLAY_SELECTION;
			}
		}
	}

	//Extract resources and check for a victory condition
	else if (phase == TURN_END)
	{
		//If "End Match" button has been pressed...
		if (signalEndMatch)
		{
			//Advance straight to match end
			phase = MATCH_END;
		}

		//Otherwise...
		else
		{
			if (!resourcesVerified && Wait(0.8f))
			{
				//Perform resource extraction
				VerifyResourceExtraction(board);

				resourcesVerified = true;
			}

			else if (resourcesVerified && (!resourcesExtracted || (resourcesExtracted && Wait(2.0f))))
			{
				//Reset extraction state for all tokens

				for (t = tokensTeam1->begin(); t != tokensTeam1->end(); t++) (*t)->getBehavior(0)->setBool("isExtracting", false);
				for (t = tokensTeam2->begin(); t != tokensTeam2->end(); t++) (*t)->getBehavior(0)->setBool("isExtracting", false);
				for (t = tokensTeam3->begin(); t != tokensTeam3->end(); t++) (*t)->getBehavior(0)->setBool("isExtracting", false);
				for (t = tokensTeam4->begin(); t != tokensTeam4->end(); t++) (*t)->getBehavior(0)->setBool("isExtracting", false);

				//Check for victory condition
				if (player1.isVictorious || player2.isVictorious || player3.isVictorious || player4.isVictorious)
				{
					//End match if there's one or more victors
					phase = MATCH_END;
				}

				//If no victors so far, go on with game...
				else
				{
					//Current turn is over!
					turnOver = true;

					//Advance to next turn
					phase = TURN_START;
				}

				//Reset auxiliary variables
				resourcesVerified = false;
				resourcesExtracted = false;
			}
		}
	}

	//Show victory messages and finish up match
	else if (phase == MATCH_END)
	{
		//Wait until victory song is over,
		//meanwhile displaying victory message.

		if (!matchOver && Wait(1.0f)) matchOver = true;

		//Once victory song has finished...
		else if (matchOver && !signalBackToTitle && ((signalEndMatch && Wait(0.1f)) || (!signalEndMatch && Wait(7.0f))))
		{
			//Drop tokens which were dead by the end of match (still floating in limbo)

			for (t = tokensTeam1->begin(); t != tokensTeam1->end(); t++) { if (!(*t)->isActive()) (*t)->node->drop(); }
			for (t = tokensTeam2->begin(); t != tokensTeam2->end(); t++) { if (!(*t)->isActive()) (*t)->node->drop(); }
			for (t = tokensTeam3->begin(); t != tokensTeam3->end(); t++) { if (!(*t)->isActive()) (*t)->node->drop(); }
			for (t = tokensTeam4->begin(); t != tokensTeam4->end(); t++) { if (!(*t)->isActive()) (*t)->node->drop(); }

			//Reset signal
			signalEndMatch = false;

			//Inform game state manager the match is over
			signalBackToTitle = true;

			//IrrEngine::getInstance()->getDevice()->closeDevice(); //Exit application
		}
	}
}

void PrimePlayState::SwapPhaseOnClick(IrrBoard* board, int i, int j)
{
	//Verify which is the clicked token/tile's type of highlight
	//(MOVE, MOVE_HOVER, PUSH_HOVER, etc.) and act accordingly!

	//If the current phase involves selecting and moving tokens...
	if (phase == PLAY_SELECTION)
	{
		//If mouse is hovering an empty tile...
		if (board->board[i][j]->token == NULL)
		{
			//...And a token has already been selected...
			if (selectedToken != NULL)
			{
				//...Mark selected token for movement.
				selectedToken->getBehavior(0)->setBool("isGonnaMove", true);

				//Startup animation for selected token
				selectedToken->getBehavior(0)->setBool("isAnimStarted", true);

				//Execute move (start animations)
				phase = ANIMATION_EXECUTION;
			}
		}

		//Otherwise, if mouse is above an occupied tile...
		else if (board->board[i][j]->token != NULL)
		{
			//If a token hasn't been selected yet
			if (selectedToken == NULL)
			{
				//Select the hovered token
				selectedToken = board->getToken(i,j);
				board->board[i][j]->token->getBehavior(0)->setBool("isSelected", true);
			}

			//Otherwise, if a token has already been selected...
			else if (selectedToken != NULL)
			{
				//If mouse is above a token that's highlighted for pushing...
				if (board->board[i][j]->token->highlight == PUSH_HOVER)
				{
					//Mark this token and the tokens behind it for pushing
					SetPushLine(CLICKED, selectedToken->getBehavior(0)->getInt("moveDir"), board, i, j);
									
					//Mark selected token for movement
					selectedToken->getBehavior(0)->setBool("isGonnaMove", true);

					//Startup animation for selected token
					selectedToken->getBehavior(0)->setBool("isAnimStarted", true);

					//Execute move (start animations)
					phase = ANIMATION_EXECUTION;
				}

				//Otherwise...
				else
				{
					//...If mouse is over an allied token, which is not the selected token...
					if (board->board[i][j]->token->player == turnPlayer)
					{
						//Unselect previous token
						selectedToken->getBehavior(0)->setBool("isSelected", false);

						//Select new token
						selectedToken = board->getToken(i,j);
						board->board[i][j]->token->getBehavior(0)->setBool("isSelected", true);
					}
									
					//...If mouse is over an enemy token...
					else
					{
						//Mark enemy as attack target
						board->board[i][j]->token->getBehavior(0)->setBool("isTargeted", true);

						//Mark selected token for movement
						selectedToken->getBehavior(0)->setBool("isGonnaMove", true);

						//Startup animation for enemy and selected token
						board->board[i][j]->token->getBehavior(0)->setBool("isAnimStarted", true);
						selectedToken->getBehavior(0)->setBool("isAnimStarted", true);

						//Execute move (start animations)
						animAttackDeath = true;
						phase = ANIMATION_EXECUTION;
					}
				}
			}
		}
	}

	//If the current phase involves reviving dead tokens...
	else if (phase == RESSURRECTION_PLACEMENT)
	{
		if (!tokenRessurrected)
		{
			//Iterate through all players' token lists, reviving dead tokens
						
			for (t = tokensTeam1->begin(); t != tokensTeam1->end(); t++) RessurrectToken((*t), board, i, j);
			for (t = tokensTeam2->begin(); t != tokensTeam2->end(); t++) RessurrectToken((*t), board, i, j);
			for (t = tokensTeam3->begin(); t != tokensTeam3->end(); t++) RessurrectToken((*t), board, i, j);
			for (t = tokensTeam4->begin(); t != tokensTeam4->end(); t++) RessurrectToken((*t), board, i, j);
		}
	}
}

void PrimePlayState::GetAdjacentTiles()
{
	//Get adjacent tile positions
	iNorth = selectedToken->parentNode->posi - 1;
	jNorth = selectedToken->parentNode->posj ;

	iSouth = selectedToken->parentNode->posi + 1;
	jSouth = selectedToken->parentNode->posj;

	iWest = selectedToken->parentNode->posi;
	jWest = selectedToken->parentNode->posj - 1;

	iEast = selectedToken->parentNode->posi;
	jEast = selectedToken->parentNode->posj + 1;

	//Get diagonal tile positions
	iNorthwest = selectedToken->parentNode->posi - 1;
	jNorthwest = selectedToken->parentNode->posj - 1;

	iNortheast = selectedToken->parentNode->posi - 1;
	jNortheast = selectedToken->parentNode->posj + 1;

	iSouthwest = selectedToken->parentNode->posi + 1;
	jSouthwest = selectedToken->parentNode->posj - 1;

	iSoutheast = selectedToken->parentNode->posi + 1;
	jSoutheast = selectedToken->parentNode->posj + 1;
}

int PrimePlayState::GetDestinationTile(int dir, int i, int j, bool iTile)
{
	int dest = -1;

	//If "iTile" is true, get the destination "i" tile (Row)
	if (iTile)
	{
		if (dir == NORTH || dir == NORTHEAST || dir == NORTHWEST) dest = i - 1;
		else if (dir == SOUTH || dir == SOUTHEAST || dir == SOUTHWEST) dest = i + 1;
		else if (dir == EAST || dir == WEST) dest = i;
	}

	//Otherwise, get the destination "j" tile (Column)
	else
	{
		if (dir == NORTH || dir == SOUTH) dest = j;
		else if (dir == EAST || dir == NORTHEAST || dir == SOUTHEAST) dest = j + 1;
		else if (dir == WEST || dir == NORTHWEST || dir == SOUTHWEST) dest = j - 1;
	}

	//Return destination
	return dest;
}

int PrimePlayState::GetRemainingTokens(bool dead, bool finished, bool animated)
{
	int remainingTokens = 0;

	//Look for tokens which animation hasn't finished
	if (animated)
	{
		//If "isAnimClosed" is false, then the token's animation hasn't been terminated by play state

		for (t = tokensTeam1->begin(); t != tokensTeam1->end(); t++)
		{
			if ((*t)->getBehavior(0)->getBool("isAnimStarted") && !(*t)->getBehavior(0)->getBool("isAnimClosed"))
				remainingTokens++;
		}
		for (t = tokensTeam2->begin(); t != tokensTeam2->end(); t++)
		{
			if ((*t)->getBehavior(0)->getBool("isAnimStarted") && !(*t)->getBehavior(0)->getBool("isAnimClosed"))
				remainingTokens++;
		}
		for (t = tokensTeam3->begin(); t != tokensTeam3->end(); t++)
		{
			if ((*t)->getBehavior(0)->getBool("isAnimStarted") && !(*t)->getBehavior(0)->getBool("isAnimClosed"))
				remainingTokens++;
		}
		for (t = tokensTeam4->begin(); t != tokensTeam4->end(); t++)
		{
			if ((*t)->getBehavior(0)->getBool("isAnimStarted") && !(*t)->getBehavior(0)->getBool("isAnimClosed"))
				remainingTokens++;
		}
	}

	//Otherwise, search for dead or finished tokens
	else
	{
		//Find out which player this turn belongs to,
		//and if that player has any dead tokens

		if (player1.isActive && turnPlayer == player1.idx)
		{
			//Search team 1's tokens
			for (t = tokensTeam1->begin(); t != tokensTeam1->end(); t++)
			{
				//Look for dead tokens or tokens which have already moved
				if (dead) { if ((*t)->getBehavior(0)->getBool("isDead")) remainingTokens++; }
				else if (finished) { if ((*t)->getBehavior(0)->getBool("isFinished")) remainingTokens++; }
			}
		}

		else if (player2.isActive && turnPlayer == player2.idx)
		{
			//Search for dead tokens among team 2's tokens
			for (t = tokensTeam2->begin(); t != tokensTeam2->end(); t++)
			{
				//Look for dead tokens or tokens which have already moved
				if (dead) { if ((*t)->getBehavior(0)->getBool("isDead")) remainingTokens++; }
				else if (finished) { if ((*t)->getBehavior(0)->getBool("isFinished")) remainingTokens++; }
			}
		}

		else if (player3.isActive && turnPlayer == player3.idx)
		{
			//Search for dead tokens among team 3's tokens
			for (t = tokensTeam3->begin(); t != tokensTeam3->end(); t++)
			{
				//Look for dead tokens or tokens which have already moved
				if (dead) { if ((*t)->getBehavior(0)->getBool("isDead")) remainingTokens++; }
				else if (finished) { if ((*t)->getBehavior(0)->getBool("isFinished")) remainingTokens++; }
			}
		}

		else if (player4.isActive && turnPlayer == player4.idx)
		{
			//Search for dead tokens among team 4's tokens
			for (t = tokensTeam4->begin(); t != tokensTeam4->end(); t++)
			{
				//Look for dead tokens or tokens which have already moved
				if (dead) { if ((*t)->getBehavior(0)->getBool("isDead")) remainingTokens++; }
				else if (finished) { if ((*t)->getBehavior(0)->getBool("isFinished")) remainingTokens++; }
			}
		}
	}

	//FOR TESTS
	//--------------------
	//remainingTokens = 1;

	//Return amout of dead or finished tokens
	return remainingTokens;
}

void PrimePlayState::UpdateCooldown()
{
	int currentCooldown = -1;

	//Decrease cooldown time for all units

	for (t = tokensTeam1->begin(); t != tokensTeam1->end(); t++)
	{
		currentCooldown = (*t)->getBehavior(0)->getInt("abilityCooldown");
		if (currentCooldown > 0) (*t)->getBehavior(0)->setInt("abilityCooldown", currentCooldown - 1);
	}

	for (t = tokensTeam2->begin(); t != tokensTeam2->end(); t++)
	{
		currentCooldown = (*t)->getBehavior(0)->getInt("abilityCooldown");
		if (currentCooldown > 0) (*t)->getBehavior(0)->setInt("abilityCooldown", currentCooldown - 1);
	}

	for (t = tokensTeam3->begin(); t != tokensTeam3->end(); t++)
	{
		currentCooldown = (*t)->getBehavior(0)->getInt("abilityCooldown");
		if (currentCooldown > 0) (*t)->getBehavior(0)->setInt("abilityCooldown", currentCooldown - 1);
	}

	for (t = tokensTeam4->begin(); t != tokensTeam4->end(); t++)
	{
		currentCooldown = (*t)->getBehavior(0)->getInt("abilityCooldown");
		if (currentCooldown > 0) (*t)->getBehavior(0)->setInt("abilityCooldown", currentCooldown - 1);
	}
}

void PrimePlayState::FinishTokens()
{
	//Find current player and end its turn by manually finishing all token moves

	if (turnPlayer == player1.idx)
	{
		for (t = tokensTeam1->begin(); t != tokensTeam1->end(); t++) (*t)->getBehavior(0)->setBool("isFinished", true);
	}

	else if (turnPlayer == player2.idx)
	{
		for (t = tokensTeam2->begin(); t != tokensTeam2->end(); t++) (*t)->getBehavior(0)->setBool("isFinished", true);
	}

	else if (turnPlayer == player3.idx)
	{
		for (t = tokensTeam3->begin(); t != tokensTeam3->end(); t++) (*t)->getBehavior(0)->setBool("isFinished", true);
	}

	else if (turnPlayer == player4.idx)
	{
		for (t = tokensTeam4->begin(); t != tokensTeam4->end(); t++) (*t)->getBehavior(0)->setBool("isFinished", true);
	}
}

void PrimePlayState::ResetTokenActionStates()
{
	//Reset action states for all tokens of all teams

	for (t = tokensTeam1->begin(); t != tokensTeam1->end(); t++) (*t)->getBehavior(0)->reset();
	for (t = tokensTeam2->begin(); t != tokensTeam2->end(); t++) (*t)->getBehavior(0)->reset();
	for (t = tokensTeam3->begin(); t != tokensTeam3->end(); t++) (*t)->getBehavior(0)->reset();
	for (t = tokensTeam4->begin(); t != tokensTeam4->end(); t++) (*t)->getBehavior(0)->reset();
}

void PrimePlayState::ManageRaceAbilities(IrrToken* token, IrrBoard* board)
{
	//Activate or deactivate abilities, when conditions are met!
	
	//KOBOLDs...
	if (token->getBehavior(0)->getInt("race") == KOBOLD)
	{
		//ADVANCED PROSPECTION activates when a Kobold unit is placed on an extraction tile
		if (board->board[token->parentNode->posi][token->parentNode->posj]->inf == RESOURCE)
		{
			if (!token->getBehavior(0)->getBool("isAbilityActive"))
			{
				//Activate ability and show special effect
				token->getBehavior(0)->setBool("isAbilityActive", true);
			}
		}

		else token->getBehavior(0)->setBool("isAbilityActive", false);
	}

	//GNOLLs...
	else if (token->getBehavior(0)->getInt("race") == GNOLL)
	{
		//RECOVERY RUSH activates when a dead Gnoll unit is placed back on the field
		if (tokenRessurrected && !token->getBehavior(0)->getBool("isDead") && token->getBehavior(0)->getBool("isFinished"))
		{
			if (!token->getBehavior(0)->getBool("isAbilityActive"))
			{
				//Activate ability and show special effect
				token->getBehavior(0)->setBool("isAbilityActive", true);
				token->getBehavior(0)->setBool("isFinished", false);
			}
		}

		else if (!tokenRessurrected && token->getBehavior(0)->getBool("isFinished"))
		{
			token->getBehavior(0)->setBool("isAbilityActive", false);
		}
	}

	//TROLLs...
	else if (token->getBehavior(0)->getInt("race") == TROLL)
	{
		//HEAVYWEIGHT activates when there's 2 or more trolls beside one another...
		if (TrollBesideMe(token, board))
		{
			//...As long as neither of them is dying.
			if (!token->getBehavior(0)->getBool("isGonnaBeTrapped") && !token->getBehavior(0)->getBool("isTargeted"))
			{
				if (!token->getBehavior(0)->getBool("isAbilityActive"))
				{
					//Activate ability and show special effect
					token->getBehavior(0)->setBool("isAbilityActive", true);
				}
			}
		}

		else token->getBehavior(0)->setBool("isAbilityActive", false);
	}

	//HOGs...
	else if (token->getBehavior(0)->getInt("race") == HOG)
	{
		//If this is the selected token and its animation has finished...
		if (token == selectedToken && token->getBehavior(0)->getBool("isAnimClosed"))
		{
			if (token->getBehavior(0)->getBool("isFinished") && token->getBehavior(0)->getInt("abilityCooldown") == 0)
			{
				//KILL RUSH activates when a Hog unit kills an enemy unit
				if (EnemyTokenKilled(board))
				{
					if (!token->getBehavior(0)->getBool("isAbilityActive"))
					{
						//Activate ability and show special effect
						token->getBehavior(0)->setBool("isAbilityActive", true);
						token->getBehavior(0)->setBool("isFinished", false);

						//This ability cannot be activated again for 3 rounds
						token->getBehavior(0)->setInt("abilityCooldown", (3 * playersActive));
					}
				}
			}
		}

		else if (token->getBehavior(0)->getBool("isFinished"))
		{
			token->getBehavior(0)->setBool("isAbilityActive", false);
		}
	}
}

void PrimePlayState::ManageRessurrection(IrrBoard* board, int i, int j)
{
	bool tileMarked = false;
	int iTile = -1;
	int jTile = -1;

	if (turnPlayer == player1.idx)
	{
		//If this tile is this team's safe zone, and there's no token on it...
		if (board->board[i][j]->inf == SAFE_ZONE_TEAM_1 && board->board[i][j]->token == NULL)
		{
			//Mark this tile's position for highlighting
			iTile = i; jTile = j; tileMarked = true;
		}
	}

	else if (turnPlayer == player2.idx)
	{
		//If this tile is this team's safe zone, and there's no token on it...
		if (board->board[i][j]->inf == SAFE_ZONE_TEAM_2 && board->board[i][j]->token == NULL)
		{
			//Mark this tile's position for highlighting
			iTile = i; jTile = j; tileMarked = true;
		}
	}

	else if (turnPlayer == player3.idx)
	{
		//If this tile is this team's safe zone, and there's no token on it...
		if (board->board[i][j]->inf == SAFE_ZONE_TEAM_3 && board->board[i][j]->token == NULL)
		{
			//Mark this tile's position for highlighting
			iTile = i; jTile = j; tileMarked = true;
		}
	}

	else if (turnPlayer == player4.idx)
	{
		//If this tile is this team's safe zone, and there's no token on it...
		if (board->board[i][j]->inf == SAFE_ZONE_TEAM_4 && board->board[i][j]->token == NULL)
		{
			//Mark this tile's position for highlighting
			iTile = i; jTile = j; tileMarked = true;
		}
	}

	//If a tile has been marked for highlighting...
	if (tileMarked)
	{
		//Highlight the tile
		board->board[iTile][jTile]->isHighlighted = true;

		if (board->board[iTile][jTile]->isMouseHover)
			board->board[iTile][jTile]->highlight = RESSURRECT_HOVER;

		else board->board[iTile][jTile]->highlight = RESSURRECT;
	}
}

void PrimePlayState::ManageTokenSelection(IrrBoard* board, int i, int j)
{
	//If the tile at (i,j) has a token
	if (board->board[i][j]->token != NULL)
	{
		//If the token belongs to the current player
		if (board->board[i][j]->token->player == turnPlayer)
		{
			//If this token isn't selected, neither dead and hasn't moved yet...
			if (!board->board[i][j]->token->getBehavior(0)->getBool("isSelected")
				&& !board->board[i][j]->token->getBehavior(0)->getBool("isDead")
				&& !board->board[i][j]->token->getBehavior(0)->getBool("isFinished"))
			{
				//Highlight tile
				board->board[i][j]->isHighlighted = true;

				if (board->board[i][j]->isMouseHover || board->board[i][j]->token->isMouseHover)
					board->board[i][j]->highlight = MOVE_HOVER;

				else board->board[i][j]->highlight = MOVE;

				//Check if token isn't already highlighted
				//by something else (like a Push move)
				if (!board->board[i][j]->token->isHighlighted)
				{
					//Highlight token
					board->board[i][j]->token->isHighlighted = true;
					board->board[i][j]->token->highlight = MOVE_HOVER;
				}
			}
		}
	}
}

void PrimePlayState::ManageMoveSelection(IrrBoard* board, int i, int j)
{
	int dir = -1;

	//Grab adjacent directions
	GetAdjacentTiles();

	//If this is not a trap or obstacle tile...
	if (board->board[i][j]->inf != TRAP && board->board[i][j]->inf != RUINS)
	{
		//Find out this tile's direction relative to selected token
		if (i == iNorth && j == jNorth) dir = NORTH;
		else if (i == iSouth && j == jSouth) dir = SOUTH;
		else if (i == iWest && j == jWest) dir = WEST;
		else if (i == iEast && j == jEast) dir = EAST;
		else if (i == iNorthwest && j == jNorthwest) dir = NORTHWEST;
		else if (i == iNortheast && j == jNortheast) dir = NORTHEAST;
		else if (i == iSouthwest && j == jSouthwest) dir = SOUTHWEST;
		else if (i == iSoutheast && j == jSoutheast) dir = SOUTHEAST;

		//If this is the North, South, West or East tile...
		if (dir == NORTH || dir == SOUTH || dir == WEST || dir == EAST)
		{
			//If there's NOT a token on this tile...
			if (board->board[i][j]->token == NULL)
			{
				//Highlight tile for Movement
				board->board[i][j]->isHighlighted = true;
						
				if (board->board[i][j]->isMouseHover)
					board->board[i][j]->highlight = MOVE_HOVER;

				else board->board[i][j]->highlight = MOVE;

				//Set move direction for selected token
				selectedToken->getBehavior(0)->setInt("moveDir", dir);
			}
			
			//Else, if there's a token on this tile...
			else if (board->board[i][j]->token != NULL)
			{
				//If its a valid Push move...
				if (PlayIsValid(PUSH,dir,board,i,j))
				{
					//Highlight tile for Push
					board->board[i][j]->isHighlighted = true;

					if (board->board[i][j]->isMouseHover || board->board[i][j]->token->isMouseHover)
					{
						board->board[i][j]->highlight = PUSH_HOVER;

						//Highlight token for Push
						board->board[i][j]->token->isHighlighted = true;
						board->board[i][j]->token->highlight = PUSH_HOVER;

						//Highlight other tokens in the Push line
						SetPushLine(ONLY_HIGHLIGHT, dir,board,i,j);

						//Set move direction for selected token
						selectedToken->getBehavior(0)->setInt("moveDir", dir);
					}
					
					else if (!board->board[i][j]->isMouseHover && !board->board[i][j]->token->isMouseHover)
					{
						board->board[i][j]->highlight = PUSH;
					}
				}
			}
		}
					
		//If this is the Northeast, Northwest, Southeast or Southwest tile...
		else if (dir == NORTHEAST || dir == NORTHWEST || dir == SOUTHEAST || dir == SOUTHWEST)
		{
			//If there's a token on this tile...
			if (board->board[i][j]->token != NULL)
			{
				//If its a valid Attack move...
				if (PlayIsValid(ATTACK,0,board,i,j))
				{
					//Highlight tile for Attack
					board->board[i][j]->isHighlighted = true;

					if (board->board[i][j]->isMouseHover || board->board[i][j]->token->isMouseHover)
					{
						board->board[i][j]->highlight = ATTACK_HOVER;

						//Highlight token for Attack
						board->board[i][j]->token->isHighlighted = true;
						board->board[i][j]->token->highlight = ATTACK_HOVER;

						//Set move direction for selected token
						selectedToken->getBehavior(0)->setInt("moveDir", dir);
					}
					
					else if (!board->board[i][j]->isMouseHover && !board->board[i][j]->token->isMouseHover)
					{
						board->board[i][j]->highlight = ATTACK;
					}
				}
			}
		}
	}
}

void PrimePlayState::UpdateTurnPhases(IrrBoard* board)
{
	bool tileSelected = false;
	bool tokenSelected = false;
	bool mouseClickedOnHighlight = false;

	//Advance phases when conditions are met
	SwapPhase(board);

	//By default, tiles and tokens are not highlighted
	ClearHighlights(board);

	//Scan the whole board
	for (int i=0; i < board->tile_i; i++)
	{
		for (int j=0; j < board->tile_j; j++)
		{
			//if (board->board[i][j]->isMouseHover) cout<<i<<", "<<j<<endl;

			//No token or tile is selected by default
			tileSelected = false;
			tokenSelected = false;

			//If a token has been selected...
			if (selectedToken != NULL)
			{
				//...But its animation hasn't begun...
				if (!selectedToken->getBehavior(0)->getBool("isAnimStarted"))
				{
					//...Reset its move direction.
					selectedToken->getBehavior(0)->setInt("moveDir", -1);
				}
			}

			//Highlight tiles and tokens according to phase


			//-------------------------------------------
			//-------- RESSURRECTION PLACEMENT ----------
			//-------------------------------------------


			if (phase == RESSURRECTION_PLACEMENT)
			{
				if (!tokenRessurrected) ManageRessurrection(board,i,j);
				
				else if (tokenRessurrected)
				{
					if (Wait(0.3f)) tokenRessurrected = false;
				}
			}


			//-------------------------------------------
			//------------ PLAY SELECTION ---------------
			//-------------------------------------------


			else if (phase == PLAY_SELECTION)
			{
				ManageTokenSelection(board,i,j);

				if (selectedToken != NULL)
				{
					ManageMoveSelection(board,i,j);
				}
			}


			//-------------------------------------------
			//---------- INPUT VERIFICATION -------------
			//-------------------------------------------


			//Check for mouse position over a tile which can be interacted with
			if (board->board[i][j]->isMouseHover && board->board[i][j]->isHighlighted)
			{
				tileSelected = true;
			}
			
			//Check for mouse position over a token which can be interacted with
			if (board->board[i][j]->token != NULL)
			{
				if (board->board[i][j]->token->isMouseHover && board->board[i][j]->token->isHighlighted)
				{
					tokenSelected = true;
				}
			}

			//If mouse button is pressed...
			if (input->getMouseState().leftButtonDown)
			{
				//If mouse cursor is above a highlighted tile or token...
				if (tileSelected || tokenSelected)
				{
					//Mouse has been clicked atop a highlighted object
					mouseClickedOnHighlight = true;

					//Select another token or advance phase
					SwapPhaseOnClick(board, i, j);
				}
			}
		}
	}


	//-------------------------------------------
	//-------- RACE ABILITY MANAGEMENT ----------
	//-------------------------------------------


	//Activate or deactivate abilities when necessary

	for (t = tokensTeam1->begin(); t != tokensTeam1->end(); t++) ManageRaceAbilities((*t), board);
	for (t = tokensTeam2->begin(); t != tokensTeam2->end(); t++) ManageRaceAbilities((*t), board);
	for (t = tokensTeam3->begin(); t != tokensTeam3->end(); t++) ManageRaceAbilities((*t), board);
	for (t = tokensTeam4->begin(); t != tokensTeam4->end(); t++) ManageRaceAbilities((*t), board);


	//-------------------------------------------
	//--------- ANIMATION EXECUTION -------------
	//-------------------------------------------


	//Set animation speed
	animSpeed = 0.5f;

	if (phase == ANIMATION_EXECUTION)
	{
		//Reset some animation control variables
		animSimpleMove = animPushMove = animTrapDeath = false;

		//Iterate through all players' token lists and animate them

		for (t = tokensTeam1->begin(); t != tokensTeam1->end(); t++) AnimateToken((*t), board, animSpeed);
		for (t = tokensTeam2->begin(); t != tokensTeam2->end(); t++) AnimateToken((*t), board, animSpeed);
		for (t = tokensTeam3->begin(); t != tokensTeam3->end(); t++) AnimateToken((*t), board, animSpeed);
		for (t = tokensTeam4->begin(); t != tokensTeam4->end(); t++) AnimateToken((*t), board, animSpeed);
	}

	//-------------------------------------------
	//--- VERIFICATION FOR TOKEN DESELECTION ----
	//-------------------------------------------


	if (input->getMouseState().leftButtonDown)
	{
		//If mouse has been clicked somewhere without interaction...
		if (!mouseClickedOnHighlight)
		{
			//If a token has already been selected...
			if (phase == PLAY_SELECTION && selectedToken != NULL)
			{
				//If neither selected token nor its tile are below mouse
				if (!selectedToken->isMouseHover && !selectedToken->parentNode->isMouseHover)
				{
					//Unselect token!
					selectedToken->getBehavior(0)->setBool("isSelected", false);
					selectedToken = NULL;
				}
			}
		}
	}
};

void PrimePlayState::Update(IrrBoard* board, int turn)
{
	Wait(); //Update "Wait" mini-engine

	//Update match
	SetTurnPlayer(turn);
	UpdateTurnPhases(board);
};