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

	isDead = false;
	isFinished = false;
	isAbilityActive = false;

	//The team score is a secret identifier for ghost tokens
	if (myTeam.primevalium == -6969) isGhost = true;
	else isGhost = false;
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

	//Make this token invisible if dead
	if (isDead) token->setActive(false);
	else token->setActive(true);

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
		//Color it darker and grayer
		token->node->getMaterial(0) = matHighlight;
		token->node->getMaterial(0).EmissiveColor.set(255,0,0,0);
		token->node->getMaterial(0).SpecularColor.set(255,100,100,100);
	}
}

void PrimeToken::PaintVanilla()
{
	//Color token normally (Full White)
	token->node->getMaterial(0) = matNormal;
	token->node->getMaterial(0).EmissiveColor.set(255,0,0,0);
	token->node->getMaterial(0).SpecularColor.set(255,255,255,255);
}