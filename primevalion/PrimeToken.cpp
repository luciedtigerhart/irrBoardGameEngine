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
	}

	else if (race == GNOLL)
	{
		pathOBJ = "obj/tokens/token01.obj";

		//Set texture according to team
		if (team == 1) pathTEX = "obj/tokens/texturas/team1.jpg";
		else if (team == 2) pathTEX = "obj/tokens/texturas/team2.jpg";
		else if (team == 3) pathTEX = "obj/tokens/texturas/team3.jpg";
		else if (team == 4) pathTEX = "obj/tokens/texturas/team4.jpg";
	}

	else if (race == TROLL)
	{
		pathOBJ = "obj/tokens/token02.obj";

		//Set texture according to team
		if (team == 1) pathTEX = "obj/tokens/texturas/team1.jpg";
		else if (team == 2) pathTEX = "obj/tokens/texturas/team2.jpg";
		else if (team == 3) pathTEX = "obj/tokens/texturas/team3.jpg";
		else if (team == 4) pathTEX = "obj/tokens/texturas/team4.jpg";
	}

	else if (race == HOG)
	{
		pathOBJ = "obj/tokens/token02.obj";

		//Set texture according to team
		if (team == 1) pathTEX = "obj/tokens/texturas/team1.jpg";
		else if (team == 2) pathTEX = "obj/tokens/texturas/team2.jpg";
		else if (team == 3) pathTEX = "obj/tokens/texturas/team3.jpg";
		else if (team == 4) pathTEX = "obj/tokens/texturas/team4.jpg";
	}

	isDead = false;
	isFinished = false;
	isAbilityActive = false;
};

void PrimeToken::init()
{
	//Highlight material uses a gray texture
	matHighlight.setTexture(0, driver->getTexture("obj/tokens/texturas/highlight.jpg"));
	matHighlight.Lighting = true;

	//Non-highlighted material uses texture with team color
	matNormal.setTexture(0, driver->getTexture(pathTEX));
	matNormal.Lighting = true;

	//Load model and texture
	token->node = smgr->addMeshSceneNode(smgr->getMesh(pathOBJ), token->parentNode->node, -1, vector3df(0,0,0));
	token->node->getMaterial(0) = matNormal;

	//Update graph parent
	token->node->setParent(token->parentNode->node);

	//Attach triangle selector
	ITriangleSelector* selector = smgr->createTriangleSelectorFromBoundingBox(token->node);
	token->node->setTriangleSelector(selector);
	selector->drop();
}

void PrimeToken::update()
{
	float deltaTime = IrrEngine::getInstance()->getDeltaTime();

	//Disable transparency
	token->node->getMaterial(0).MaterialType = EMT_SOLID;

	//Make this token invisible if dead
	if (isDead) token->setActive(false);
	else token->setActive(true);

	//If this token can still move...
	if (!isFinished)
	{
		//If this token is highlighted...
		if (token->isHighlighted)
		{
			token->highlight = MOVE_HOVER;

			//Change color according to type of highlight

			if (token->highlight == MOVE)
			{
				//Selected highlight (Very Light Blue)
				token->node->getMaterial(0) = matHighlight;
				token->node->getMaterial(0).EmissiveColor.set(255,100,180,255);
				token->node->getMaterial(0).SpecularColor.set(255,100,180,255);
			}

			else if (token->highlight == MOVE_HOVER)
			{
				//Selection hover highlight (Light Blue)
				token->node->getMaterial(0) = matHighlight;
				token->node->getMaterial(0).EmissiveColor.set(255,40,80,255);
				token->node->getMaterial(0).SpecularColor.set(255,40,80,255);
			}

			else if (token->highlight == PUSH)
			{
				//Push target highlight (Orange)
				token->node->getMaterial(0) = matHighlight;
				token->node->getMaterial(0).EmissiveColor.set(255,255,70,0);
				token->node->getMaterial(0).SpecularColor.set(255,255,70,0);
			}

			else if (token->highlight == PUSH_HOVER)
			{
				//Push hover highlight (Light Orange)
				token->node->getMaterial(0) = matHighlight;
				token->node->getMaterial(0).EmissiveColor.set(255,255,110,40);
				token->node->getMaterial(0).SpecularColor.set(255,255,110,40);
			}

			else if (token->highlight == ATTACK)
			{
				//Attack target highlight (Red)
				token->node->getMaterial(0) = matHighlight;
				token->node->getMaterial(0).EmissiveColor.set(255,255,0,0);
				token->node->getMaterial(0).SpecularColor.set(255,255,0,0);
			}

			else if (token->highlight == ATTACK_HOVER)
			{
				//Attack hover highlight (Light Red)
				token->node->getMaterial(0) = matHighlight;
				token->node->getMaterial(0).EmissiveColor.set(255,255,80,80);
				token->node->getMaterial(0).SpecularColor.set(255,255,80,80);
			}

			else if (token->highlight == RESSURRECT)
			{
				//Ressurrection placement highlight (Transparent Gray)
				token->node->getMaterial(0) = matHighlight;
				token->node->getMaterial(0).EmissiveColor.set(255,10,10,10);
				token->node->getMaterial(0).SpecularColor.set(255,10,10,10);

				//Enable transparency
				token->node->getMaterial(0).MaterialType = EMT_TRANSPARENT_ADD_COLOR;
			}
		}

		//Otherwise, if this token isn't highlighted...
		else if (token->isHighlighted == false)
		{
			//Color it normally (Full White)
			token->node->getMaterial(0) = matNormal;
			token->node->getMaterial(0).EmissiveColor.set(255,0,0,0);
			token->node->getMaterial(0).SpecularColor.set(255,255,255,255);
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