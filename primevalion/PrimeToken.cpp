#include "PrimeToken.h"

PrimeToken::PrimeToken(PrimeTeam myTeam)
{
	team = myTeam.idx;
	race = myTeam.assignedRace;

	//Set mesh according to race
	
	if (race == KOBOLD)
	{
		pathOBJ = "obj/tokens/token01.obj";

		//Set texture according to team
		if (team == 1) pathTEX = "obj/tokens/texturas/team1.jpg";
		else if (team == 2) pathTEX = "obj/tokens/texturas/team2.jpg";
		else if (team == 3) pathTEX = "obj/tokens/texturas/team3.jpg";
		else if (team == 4) pathTEX = "obj/tokens/texturas/team4.jpg";

		//Highlight texture
		pathTEXHL = "obj/tokens/texturas/highlight.jpg";
	}

	else if (race == GNOLL)
	{
		pathOBJ = "obj/tokens/token01.obj";

		//Set texture according to team
		if (team == 1) pathTEX = "obj/tokens/texturas/team1.jpg";
		else if (team == 2) pathTEX = "obj/tokens/texturas/team2.jpg";
		else if (team == 3) pathTEX = "obj/tokens/texturas/team3.jpg";
		else if (team == 4) pathTEX = "obj/tokens/texturas/team4.jpg";

		//Highlight texture
		pathTEXHL = "obj/tokens/texturas/highlight.jpg";
	}

	else if (race == TROLL)
	{
		pathOBJ = "obj/tokens/token02.obj";

		//Set texture according to team
		if (team == 1) pathTEX = "obj/tokens/texturas/team1.jpg";
		else if (team == 2) pathTEX = "obj/tokens/texturas/team2.jpg";
		else if (team == 3) pathTEX = "obj/tokens/texturas/team3.jpg";
		else if (team == 4) pathTEX = "obj/tokens/texturas/team4.jpg";

		//Highlight texture
		pathTEXHL = "obj/tokens/texturas/highlight.jpg";
	}

	else if (race == HOG)
	{
		pathOBJ = "obj/tokens/token02.obj";

		//Set texture according to team
		if (team == 1) pathTEX = "obj/tokens/texturas/team1.jpg";
		else if (team == 2) pathTEX = "obj/tokens/texturas/team2.jpg";
		else if (team == 3) pathTEX = "obj/tokens/texturas/team3.jpg";
		else if (team == 4) pathTEX = "obj/tokens/texturas/team4.jpg";

		//Highlight texture
		pathTEXHL = "obj/tokens/texturas/highlight.jpg";
	}

	//Set initial states
	isDead = false;
	isFinished = false;
	isAbilityActive = false;
	
	//The team score is a secret identifier for ghost tokens
	if (myTeam.primevalium == -6969) isGhost = true;
	else isGhost = false;

	//Reset other attributes
	ResetActionStates();
};

void PrimeToken::init()
{
	//Highlight material uses a gray texture
	matHighlight.setTexture(0, driver->getTexture(pathTEXHL));
	matHighlight.Lighting = true;

	//Non-highlighted material uses texture with team color
	matNormal.setTexture(0, driver->getTexture(pathTEX));
	matNormal.Lighting = true;

	//Load model and texture
	token->node = smgr->addMeshSceneNode(smgr->getMesh(pathOBJ), token->parentNode->node, -1, vector3df(0,0,0));
	token->node->getMaterial(0) = matNormal;

	//Update graph parent and team
	token->node->setParent(token->parentNode->node);
	token->player = team;

	//Attach triangle selector if this isn't a ghost token
	if (!isGhost)
	{
		ITriangleSelector* selector = smgr->createTriangleSelectorFromBoundingBox(token->node);
		token->node->setTriangleSelector(selector);
		selector->drop();
	}

	//Make this token transparent if its a ghost
	else if (isGhost)
	{
		//Ressurrection placement highlight (Transparent Gray)
		token->node->getMaterial(0) = matHighlight;
		token->node->getMaterial(0).EmissiveColor.set(255,10,10,10);
		token->node->getMaterial(0).SpecularColor.set(255,10,10,10);

		//Enable transparency
		token->node->getMaterial(0).MaterialType = EMT_TRANSPARENT_ADD_COLOR;
	}
}

void PrimeToken::update()
{
	float deltaTime = IrrEngine::getInstance()->getDeltaTime();

	//Disable transparency
	if (!isGhost) token->node->getMaterial(0).MaterialType = EMT_SOLID;

	//If token dies...
	if (isDead)
	{
		//If still attached to parent...
		if (!orphan)
		{
			//Store pointer to old parent
			IrrTile* oldParent;
			oldParent = token->parentNode;

			//Unattach token from its parent
			token->node->grab();
			token->node->remove();

			//Empty parent tile
			oldParent->token = NULL;

			//Make token orphan, and deactivate it
			orphan = true;
			token->setActive(false);
		}
	}

	//If token is alive...
	else if (!isDead) orphan = false;

	//If this token can still move...
	if (!isFinished)
	{
		//If this token is highlighted...
		if (token->isHighlighted)
		{
			//Change color according to type of highlight

			if (token->isMouseHover || token->parentNode->isMouseHover)
			{
				if (token->highlight == MOVE_HOVER)
				{
					//Selection hover highlight (Light Blue)
					token->node->getMaterial(0) = matHighlight;
					token->node->getMaterial(0).EmissiveColor.set(255,40,80,255);
					token->node->getMaterial(0).SpecularColor.set(255,40,80,255);
				}

				else if (token->highlight == PUSH_HOVER)
				{
					//Push target hover highlight (Orange)
					token->node->getMaterial(0) = matHighlight;
					token->node->getMaterial(0).EmissiveColor.set(255,255,70,0);
					token->node->getMaterial(0).SpecularColor.set(255,255,70,0);
				}

				else if (token->highlight == ATTACK_HOVER)
				{
					//Attack target hover highlight (Red)
					token->node->getMaterial(0) = matHighlight;
					token->node->getMaterial(0).EmissiveColor.set(255,255,0,0);
					token->node->getMaterial(0).SpecularColor.set(255,255,0,0);
				}

				else PaintVanilla();
			}

			else
			{
				if (token->highlight == MOVE)
				{
					//Selected highlight (Very Light Blue)
					token->node->getMaterial(0) = matHighlight;
					token->node->getMaterial(0).EmissiveColor.set(255,100,180,255);
					token->node->getMaterial(0).SpecularColor.set(255,100,180,255);
				}

				else if (token->highlight == PUSH_HOVER)
				{
					//Push victim highlight (Orange)
					token->node->getMaterial(0) = matHighlight;
					token->node->getMaterial(0).EmissiveColor.set(255,255,70,0);
					token->node->getMaterial(0).SpecularColor.set(255,255,70,0);
				}

				else PaintVanilla();
			}
		}

		//Otherwise, if this token isn't highlighted...
		else if (token->isHighlighted == false)
		{
			//Color it normally
			PaintVanilla();
		}
	}

	//Otherwise, if this token already moved...
	else if (isFinished)
	{
		//If this token is being highlighted by another token...
		if (token->isHighlighted)
		{
			//...Like an allied token that's trying to push it...
			if (token->highlight == PUSH_HOVER)
			{
				//Push victim highlight (Orange)
				token->node->getMaterial(0) = matHighlight;
				token->node->getMaterial(0).EmissiveColor.set(255,255,70,0);
				token->node->getMaterial(0).SpecularColor.set(255,255,70,0);
			}
		}

		//If not being highlighted at all...
		else
		{
			//Color it darker and grayer
			token->node->getMaterial(0) = matHighlight;
			token->node->getMaterial(0).EmissiveColor.set(255,0,0,0);
			token->node->getMaterial(0).SpecularColor.set(255,100,100,100);
		}
	}
}

void PrimeToken::PaintVanilla()
{
	//Color token normally (Full White)
	token->node->getMaterial(0) = matNormal;
	token->node->getMaterial(0).EmissiveColor.set(255,0,0,0);
	token->node->getMaterial(0).SpecularColor.set(255,255,255,255);
}

void PrimeToken::ResetActionStates()
{
	//Do exactly what the method name says

	isSelected = false;
	isTargeted = false;
	isGonnaMove = false;
	isGonnaBePushed = false;
	isAnimStarted = false;
	isAnimRunning = false;
	isAnimFinished = false;
	isAnimClosed = false;

	moveDir = -1; //Reset move direction as well

	//...And translation animation variables too
	iDest = jDest = -1;
	destPosition.x = destPosition.y = destPosition.z = 0.0f;
	originPosition.x = originPosition.y = originPosition.z = 0.0f;
}

void PrimeToken::setInt(char const * key, int value)
{
	if (key == "moveDir") moveDir = value;
	else if (key == "iDest") iDest = value;
	else if (key == "jDest") jDest = value;
}

int PrimeToken::getInt(char const * key)
{
	if (key == "moveDir") return moveDir;
	else if (key == "iDest") return iDest;
	else if (key == "jDest") return jDest;

	else return 0;
}

void PrimeToken::setBool(char const * key, bool value)
{
	if (key == "isGhost") isGhost = value;
	else if (key == "isDead") isDead = value;
	else if (key == "isFinished") isFinished = value;
	else if (key == "isAbilityActive") isAbilityActive = value;

	else if (key == "isSelected") isSelected = value;
	else if (key == "isTargeted") isTargeted = value;
	else if (key == "isGonnaMove") isGonnaMove = value;
	else if (key == "isGonnaBePushed") isGonnaBePushed = value;

	else if (key == "isAnimStarted") isAnimStarted = value;
	else if (key == "isAnimRunning") isAnimRunning = value;
	else if (key == "isAnimFinished") isAnimFinished = value;
	else if (key == "isAnimClosed") isAnimClosed = value;
}

bool PrimeToken::getBool(char const * key)
{
	if (key == "isGhost") return isGhost;
	else if (key == "isDead") return isDead;
	else if (key == "isFinished") return isFinished;
	else if (key == "isAbilityActive") return isAbilityActive;

	else if (key == "isSelected") return isSelected;
	else if (key == "isTargeted") return isTargeted;
	else if (key == "isGonnaMove") return isGonnaMove;
	else if (key == "isGonnaBePushed") return isGonnaBePushed;

	else if (key == "isAnimStarted") return isAnimStarted;
	else if (key == "isAnimRunning") return isAnimRunning;
	else if (key == "isAnimFinished") return isAnimFinished;
	else if (key == "isAnimClosed") return isAnimClosed;

	else return false;
}