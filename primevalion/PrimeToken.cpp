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
};

void PrimeToken::init()
{
	token->player = team;

	//Load model and texture
	token->node = smgr->addMeshSceneNode(smgr->getMesh(pathOBJ), token->parentNode, token->idx, vector3df(0,0,0));
	token->node->setMaterialTexture(0, driver->getTexture(pathTEX));

	//Update graph parent
	token->node->setParent(token->parentNode);

	//Activate lighting
	token->node->setMaterialFlag(EMF_LIGHTING, true);

	//Activate transparency on this node
	//scene->smgr->registerNodeForRendering(node, ESNRP_TRANSPARENT);
	token->node->getMaterial(0).MaterialTypeParam = pack_texureBlendFunc(EBF_SRC_ALPHA, EBF_ONE_MINUS_SRC_ALPHA, EMFN_MODULATE_1X);
}

void PrimeToken::update()
{
	float deltaTime = IrrEngine::getInstance()->getDeltaTime();

	//Disable transparency
	token->node->getMaterial(0).MaterialType = EMT_SOLID;

	//Make this token invisible if dead
	if (isDead) token->node->setVisible(false);
	else token->node->setVisible(true);

	//If this token can still move...
	if (!isFinished)
	{
		//If this token is highlighted...
		if (isHighlighted)
		{
			//Change color according to type of highlight

			if (highlight == RESSURRECT)
			{
				//Enable transparency
				token->node->getMaterial(0).MaterialType = EMT_ONETEXTURE_BLEND;

				//Ressurrection placement highlight (Transparent Gray)
				//node->getMaterial(0).AmbientColor.set(150,100,100,100);
				token->node->getMaterial(0).DiffuseColor.set(150,100,100,100);
			}

			else
			{
				if (highlight == MOVE)
				{
					//Selected highlight (Very Light Blue)
					//node->getMaterial(0).AmbientColor.set(255,80,160,255);
					token->node->getMaterial(0).DiffuseColor.set(255,80,160,255);
				}

				else if (highlight == MOVE_HOVER)
				{
					//Selection hover highlight (Light Blue)
					//node->getMaterial(0).AmbientColor.set(255,40,80,255);
					token->node->getMaterial(0).DiffuseColor.set(255,40,80,255);
				}

				else if (highlight == PUSH)
				{
					//Push target highlight (Orange)
					//node->getMaterial(0).AmbientColor.set(255,255,160,0);
					token->node->getMaterial(0).DiffuseColor.set(255,255,160,0);
				}

				else if (highlight == PUSH_HOVER)
				{
					//Push hover highlight (Light Orange)
					//node->getMaterial(0).AmbientColor.set(255,255,200,40);
					token->node->getMaterial(0).DiffuseColor.set(255,255,200,40);
				}

				else if (highlight == ATTACK)
				{
					//Attack target highlight (Red)
					//node->getMaterial(0).AmbientColor.set(255,255,0,0);
					token->node->getMaterial(0).DiffuseColor.set(255,255,0,0);
				}

				else if (highlight == ATTACK_HOVER)
				{
					//Attack hover highlight (Light Red)
					//node->getMaterial(0).AmbientColor.set(255,255,80,80);
					token->node->getMaterial(0).DiffuseColor.set(255,255,80,80);
				}
			}
		}

		//Otherwise, if this token isn't highlighted...
		else
		{
			//Color it normally (Full White)
			//node->getMaterial(0).AmbientColor.set(255,255,255,255);
			token->node->getMaterial(0).DiffuseColor.set(255,255,255,255);
		}
	}

	//Otherwise, if this token already moved...
	else if (isFinished)
	{
		//Color it darker and grayer
		//node->getMaterial(0).AmbientColor.set(255,100,100,100);
		token->node->getMaterial(0).DiffuseColor.set(255,100,100,100);
	}
}