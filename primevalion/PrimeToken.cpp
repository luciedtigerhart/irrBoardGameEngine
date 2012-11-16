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

		//Ability icon texture
		if (team == 1) pathBBICO = "billboard/ability/billboard_kobold_icon_t1.png";
		else if (team == 2) pathBBICO = "billboard/ability/billboard_kobold_icon_t2.png";
		else if (team == 3) pathBBICO = "billboard/ability/billboard_kobold_icon_t3.png";
		else if (team == 4) pathBBICO = "billboard/ability/billboard_kobold_icon_t4.png";
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

		//Ability icon texture
		if (team == 1) pathBBICO = "billboard/ability/billboard_gnoll_icon_t1.png";
		else if (team == 2) pathBBICO = "billboard/ability/billboard_gnoll_icon_t2.png";
		else if (team == 3) pathBBICO = "billboard/ability/billboard_gnoll_icon_t3.png";
		else if (team == 4) pathBBICO = "billboard/ability/billboard_gnoll_icon_t4.png";
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

		//Ability icon texture
		if (team == 1) pathBBICO = "billboard/ability/billboard_troll_icon_t1.png";
		else if (team == 2) pathBBICO = "billboard/ability/billboard_troll_icon_t2.png";
		else if (team == 3) pathBBICO = "billboard/ability/billboard_troll_icon_t3.png";
		else if (team == 4) pathBBICO = "billboard/ability/billboard_troll_icon_t4.png";
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

		//Ability icon texture
		if (team == 1) pathBBICO = "billboard/ability/billboard_hog_icon_t1.png";
		else if (team == 2) pathBBICO = "billboard/ability/billboard_hog_icon_t2.png";
		else if (team == 3) pathBBICO = "billboard/ability/billboard_hog_icon_t3.png";
		else if (team == 4) pathBBICO = "billboard/ability/billboard_hog_icon_t4.png";
	}

	//Billboard textures
	if (race == KOBOLD)
	{
		if (team == 1) pathBBEXT = "billboard/resource/billboard_extract_160_t1.png";
		else if (team == 2) pathBBEXT = "billboard/resource/billboard_extract_160_t2.png";
		else if (team == 3) pathBBEXT = "billboard/resource/billboard_extract_160_t3.png";
		else if (team == 4) pathBBEXT = "billboard/resource/billboard_extract_160_t4.png";
	}
	else
	{
		if (team == 1) pathBBEXT = "billboard/resource/billboard_extract_100_t1.png";
		else if (team == 2) pathBBEXT = "billboard/resource/billboard_extract_100_t2.png";
		else if (team == 3) pathBBEXT = "billboard/resource/billboard_extract_100_t3.png";
		else if (team == 4) pathBBEXT = "billboard/resource/billboard_extract_100_t4.png";
	}

	//Set initial states
	isDead = false;
	isFinished = false;
	isExtracting = false;
	isAbilityActive = false;
	
	//The team score is a secret identifier for ghost tokens
	if (myTeam.primevalium == -6969) isGhost = true;
	else isGhost = false;

	//Reset ability-related attributes
	abilityCooldown = 0;
	abilityBlink = -1.0f;

	//Reset other attributes
	reset();
};

void PrimeToken::PaintVanilla()
{
	//Color token normally (Full White)
	token->node->getMaterial(0) = matNormal;
	token->node->getMaterial(0).EmissiveColor.set(255,0,0,0);
	token->node->getMaterial(0).SpecularColor.set(255,255,255,255);
}

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

	//Create ability icon billboard
	billboardAbility = smgr->addBillboardSceneNode(token->node, dimension2d<f32>(1.5f, 1.5f), vector3df(0.0f,5.0f,0.0f));
	billboardAbility->getMaterial(0).setTexture(0, driver->getTexture(pathBBICO));
	billboardAbility->getMaterial(0).MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL;
	billboardAbility->getMaterial(0).Lighting = false;
	billboardAbility->setVisible(false);

	//Create extraction billboard
	billboardExtraction = smgr->addBillboardSceneNode(token->node, dimension2d<f32>(2.1f, 2.1f), vector3df(0.0f,5.0f,0.0f));
	billboardExtraction->getMaterial(0).setTexture(0, driver->getTexture(pathBBEXT));
	billboardExtraction->getMaterial(0).MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL;
	billboardExtraction->getMaterial(0).Lighting = false;
	billboardExtraction->setVisible(false);

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

	//Startup stuff that will help during trap death animation
	then = IrrEngine::getInstance()->getDevice()->getTimer()->getTime();
	deathCounter = 0.0f;
}

void PrimeToken::reset()
{
	//Reset action states

	isSelected = false;
	isTargeted = false;
	isGonnaMove = false;
	isGonnaBePushed = false;
	isGonnaBeTrapped = false;
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

void PrimeToken::update()
{
	//Disable transparency
	if (!isGhost) token->node->getMaterial(0).MaterialType = EMT_SOLID;

	//If token dies...
	if (isDead)
	{
		//If still attached to parent...
		if (!orphan)
		{
			//If killed by trap or attack...
			if (isTargeted || isGonnaBeTrapped)
			{
				deathCounter = 0.0f; //Reset death animation counter
				abilityBlink = -1.0f; //Reset "blink" effect counter

				//Reset position after falling into trap
				if (isGonnaBeTrapped) token->node->setPosition(vector3df(0,0,0));
			}

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
					token->node->getMaterial(0).EmissiveColor.set(255,210,120,0);
					token->node->getMaterial(0).SpecularColor.set(255,210,120,0);
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
					token->node->getMaterial(0).EmissiveColor.set(255,210,120,0);
					token->node->getMaterial(0).SpecularColor.set(255,210,120,0);
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

	//Ability activation/deactivation management
	if (isAbilityActive)
	{
		//Show billboard
		billboardAbility->setVisible(true);

		if (abilityBlink >= 0.0f && abilityBlink < 0.1f)
		{
			//Calculate frame-independent time
			now = IrrEngine::getInstance()->getDevice()->getTimer()->getTime();
			deltaTime = (float)(now - then) / 1000.f;

			//Blink briefly, indicating ability is "On"
			token->node->getMaterial(0) = matHighlight;
			token->node->getMaterial(0).EmissiveColor.set(200,255,255,255);
			token->node->getMaterial(0).SpecularColor.set(255,255,255,255);

			//Increment "blink" effect counter
			abilityBlink += 1.0f * deltaTime;
		}

		else if (abilityBlink < 0.0f) abilityBlink = 0.0f;
	}
	else if (!isAbilityActive)
	{
		//Deactivate billboard and reset "blink" effect
		billboardAbility->setVisible(false);
		abilityBlink = -1.0f;
	}

	//Resouce extraction billboard management
	if (isExtracting) { billboardExtraction->setVisible(true); billboardAbility->setVisible(false); }
	else if (!isExtracting) billboardExtraction->setVisible(false);

	//Death animation management
	if (isTargeted || (isGonnaBeTrapped && !isGonnaBePushed))
	{
		if (isAnimStarted && isAnimRunning)
		{
			//Calculate frame-independent time
			now = IrrEngine::getInstance()->getDevice()->getTimer()->getTime();
			deltaTime = (float)(now - then) / 1000.f;

			//Increment death counter
			deathCounter += 1.0f * deltaTime;

			//Attack death animation
			if (isTargeted)
			{
				//Run animation
				//...

				//When animation is over...
				//if (animation over)
				//{
					//isAnimRunning = false;
					//isAnimFinished = true;
				//}
			}

			//Periodically change material to simulate
			//bleeding and disappearance

			if ((deathCounter > 0.2f && deathCounter <= 0.3f)
				|| (deathCounter > 0.4f && deathCounter <= 0.5f)
				|| (deathCounter > 0.6f && deathCounter <= 0.7f))
			{
				//Red
				token->node->getMaterial(0) = matHighlight;
				token->node->getMaterial(0).EmissiveColor.set(255,255,0,0);
				token->node->getMaterial(0).SpecularColor.set(255,255,0,0);
			}

			else if ((deathCounter > 1.5f && deathCounter <= 1.6f)
					|| (deathCounter > 1.7f && deathCounter <= 1.8f)
					|| (deathCounter > 1.9f && deathCounter <= 2.0f)
					|| (deathCounter > 2.1f && deathCounter <= 2.2f)
					|| (deathCounter > 2.3f && deathCounter <= 2.4f))
			{
				//Light Red
				token->node->getMaterial(0) = matHighlight;
				token->node->getMaterial(0).EmissiveColor.set(255,150,0,0);
				token->node->getMaterial(0).SpecularColor.set(255,255,0,0);
			}

			else if ((deathCounter > 0.8f && deathCounter <= 0.9f)
					|| (deathCounter > 1.0f && deathCounter <= 1.1f)
					|| (deathCounter > 1.2f && deathCounter <= 1.3f)
					|| (deathCounter > 1.4f && deathCounter <= 1.5f))
			{
				//Transparent red
				token->node->getMaterial(0) = matHighlight;
				token->node->getMaterial(0).EmissiveColor.set(255,255,0,0);
				token->node->getMaterial(0).SpecularColor.set(255,255,0,0);

				//Enable transparency
				token->node->getMaterial(0).MaterialType = EMT_TRANSPARENT_ADD_COLOR;
			}

			else if ((deathCounter > 1.6f && deathCounter <= 1.7f)
					|| (deathCounter > 1.8f && deathCounter <= 1.9f)
					|| (deathCounter > 2.0f && deathCounter <= 2.1f)
					|| (deathCounter > 2.2f && deathCounter <= 2.3f))
			{
				//Transparent white
				token->node->getMaterial(0) = matHighlight;
				token->node->getMaterial(0).EmissiveColor.set(255,0,0,0);
				token->node->getMaterial(0).SpecularColor.set(255,255,0,0);

				//Enable transparency
				token->node->getMaterial(0).MaterialType = EMT_TRANSPARENT_ADD_COLOR;
			}
		}
	}

	//Update time
	then = IrrEngine::getInstance()->getDevice()->getTimer()->getTime();
}

void PrimeToken::setInt(char const * key, int value)
{
	if (key == "moveDir") moveDir = value;
	else if (key == "iDest") iDest = value;
	else if (key == "jDest") jDest = value;
	else if (key == "abilityCooldown") abilityCooldown = value;
}

int PrimeToken::getInt(char const * key)
{
	if (key == "moveDir") return moveDir;
	else if (key == "iDest") return iDest;
	else if (key == "jDest") return jDest;
	else if (key == "race") return race;
	else if (key == "team") return team;
	else if (key == "abilityCooldown") return abilityCooldown;

	else return 0;
}

void PrimeToken::setFloat(char const * key, float value)
{
	if (key == "originPosition.x") originPosition.x = value;
	else if (key == "originPosition.y") originPosition.y = value;
	else if (key == "originPosition.z") originPosition.z = value;
	else if (key == "destPosition.x") destPosition.x = value;
	else if (key == "destPosition.y") destPosition.y = value;
	else if (key == "destPosition.z") destPosition.z = value;
}

float PrimeToken::getFloat(char const * key)
{
	if (key == "originPosition.x") return originPosition.x;
	else if (key == "originPosition.y") return originPosition.y;
	else if (key == "originPosition.z") return originPosition.z;
	else if (key == "destPosition.x") return destPosition.x;
	else if (key == "destPosition.y") return destPosition.y;
	else if (key == "destPosition.z") return destPosition.z;

	else return 0;
}

void PrimeToken::setBool(char const * key, bool value)
{
	if (key == "isGhost") isGhost = value;
	else if (key == "isDead") isDead = value;
	else if (key == "isFinished") isFinished = value;
	else if (key == "isExtracting") isExtracting = value;
	else if (key == "isAbilityActive") isAbilityActive = value;

	else if (key == "isSelected") isSelected = value;
	else if (key == "isTargeted") isTargeted = value;
	else if (key == "isGonnaMove") isGonnaMove = value;
	else if (key == "isGonnaBePushed") isGonnaBePushed = value;
	else if (key == "isGonnaBeTrapped") isGonnaBeTrapped = value;

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
	else if (key == "isExtracting") return isExtracting;
	else if (key == "isAbilityActive") return isAbilityActive;

	else if (key == "isSelected") return isSelected;
	else if (key == "isTargeted") return isTargeted;
	else if (key == "isGonnaMove") return isGonnaMove;
	else if (key == "isGonnaBePushed") return isGonnaBePushed;
	else if (key == "isGonnaBeTrapped") return isGonnaBeTrapped;

	else if (key == "isAnimStarted") return isAnimStarted;
	else if (key == "isAnimRunning") return isAnimRunning;
	else if (key == "isAnimFinished") return isAnimFinished;
	else if (key == "isAnimClosed") return isAnimClosed;

	else return false;
}

void PrimeToken::setVector(char const * key, Vector value)
{
	if (key == "originPosition") originPosition = value;
	else if (key == "destPosition") destPosition = value;
}

Vector PrimeToken::getVector(char const * key)
{
	if (key == "originPosition") return originPosition;
	else if (key == "destPosition") return destPosition;

	else return 0;
}