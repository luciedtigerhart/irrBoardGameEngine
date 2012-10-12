#include "PrimeToken.h"

PrimeToken::PrimeToken() {};
PrimeToken::~PrimeToken() {};

void PrimeToken::init(IrrEngine* engine, IrrScene* scene, PrimeTeam team)
{
	player = team.idx;
	race = team.assignedRace;

	//Set mesh according to race

	if (race == KOBOLD)
	{
		node = scene->smgr->addMeshSceneNode(scene->smgr->getMesh("obj/nome_do_modelo_KOBOLD.obj"), node->getParent(), idx, node->getPosition());

		//Set texture according to team
		if (player == 1) node->setMaterialTexture(0, engine->driver->getTexture("obj/texturas/nome_da_textura_KOBOLD_TIME1.jpg"));
		else if (player == 2) node->setMaterialTexture(0, engine->driver->getTexture("obj/texturas/nome_da_textura_KOBOLD_TIME2.jpg"));
		else if (player == 3) node->setMaterialTexture(0, engine->driver->getTexture("obj/texturas/nome_da_textura_KOBOLD_TIME3.jpg"));
		else if (player == 4) node->setMaterialTexture(0, engine->driver->getTexture("obj/texturas/nome_da_textura_KOBOLD_TIME4.jpg"));
	}

	else if (race == GNOLL)
	{
		node = scene->smgr->addMeshSceneNode(scene->smgr->getMesh("obj/nome_do_modelo_GNOLL.obj"), node->getParent(), idx, node->getPosition());

		//Set texture according to team
		if (player == 1) node->setMaterialTexture(0, engine->driver->getTexture("obj/texturas/nome_da_textura_GNOLL_TIME1.jpg"));
		else if (player == 2) node->setMaterialTexture(0, engine->driver->getTexture("obj/texturas/nome_da_textura_GNOLL_TIME2.jpg"));
		else if (player == 3) node->setMaterialTexture(0, engine->driver->getTexture("obj/texturas/nome_da_textura_GNOLL_TIME3.jpg"));
		else if (player == 4) node->setMaterialTexture(0, engine->driver->getTexture("obj/texturas/nome_da_textura_GNOLL_TIME4.jpg"));
	}

	else if (race == TROLL)
	{
		node = scene->smgr->addMeshSceneNode(scene->smgr->getMesh("obj/nome_do_modelo_TROLL.obj"), node->getParent(), idx, node->getPosition());

		//Set texture according to team
		if (player == 1) node->setMaterialTexture(0, engine->driver->getTexture("obj/texturas/nome_da_textura_TROLL_TIME1.jpg"));
		else if (player == 2) node->setMaterialTexture(0, engine->driver->getTexture("obj/texturas/nome_da_textura_TROLL_TIME2.jpg"));
		else if (player == 3) node->setMaterialTexture(0, engine->driver->getTexture("obj/texturas/nome_da_textura_TROLL_TIME3.jpg"));
		else if (player == 4) node->setMaterialTexture(0, engine->driver->getTexture("obj/texturas/nome_da_textura_TROLL_TIME4.jpg"));
	}

	else if (race == HOG)
	{
		node = scene->smgr->addMeshSceneNode(scene->smgr->getMesh("obj/nome_do_modelo_HOG.obj"), node->getParent(), idx, node->getPosition());

		//Set texture according to team
		if (player == 1) node->setMaterialTexture(0, engine->driver->getTexture("obj/texturas/nome_da_textura_HOG_TIME1.jpg"));
		else if (player == 2) node->setMaterialTexture(0, engine->driver->getTexture("obj/texturas/nome_da_textura_HOG_TIME2.jpg"));
		else if (player == 3) node->setMaterialTexture(0, engine->driver->getTexture("obj/texturas/nome_da_textura_HOG_TIME3.jpg"));
		else if (player == 4) node->setMaterialTexture(0, engine->driver->getTexture("obj/texturas/nome_da_textura_HOG_TIME4.jpg"));
	}

	//Activate lighting
	node->setMaterialFlag(EMF_LIGHTING, true);

	//Activate transparency on this node
	//scene->smgr->registerNodeForRendering(node, ESNRP_TRANSPARENT);
	node->getMaterial(0).MaterialTypeParam = pack_texureBlendFunc(EBF_SRC_ALPHA, EBF_ONE_MINUS_SRC_ALPHA, EMFN_MODULATE_1X);
}

void PrimeToken::update()
{
	//Disable transparency
	node->getMaterial(0).MaterialType = EMT_SOLID;

	//Make this token invisible if dead
	if (isDead) node->setVisible(false);
	else node->setVisible(true);

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
				node->getMaterial(0).MaterialType = EMT_ONETEXTURE_BLEND;

				//Ressurrection placement highlight (Transparent Gray)
				//node->getMaterial(0).AmbientColor.set(150,100,100,100);
				node->getMaterial(0).DiffuseColor.set(150,100,100,100);
			}

			else
			{
				if (highlight == MOVE)
				{
					//Selected highlight (Very Light Blue)
					//node->getMaterial(0).AmbientColor.set(255,80,160,255);
					node->getMaterial(0).DiffuseColor.set(255,80,160,255);
				}

				else if (highlight == MOVE_HOVER)
				{
					//Selection hover highlight (Light Blue)
					//node->getMaterial(0).AmbientColor.set(255,40,80,255);
					node->getMaterial(0).DiffuseColor.set(255,40,80,255);
				}

				else if (highlight == PUSH)
				{
					//Push target highlight (Orange)
					//node->getMaterial(0).AmbientColor.set(255,255,160,0);
					node->getMaterial(0).DiffuseColor.set(255,255,160,0);
				}

				else if (highlight == PUSH_HOVER)
				{
					//Push hover highlight (Light Orange)
					//node->getMaterial(0).AmbientColor.set(255,255,200,40);
					node->getMaterial(0).DiffuseColor.set(255,255,200,40);
				}

				else if (highlight == ATTACK)
				{
					//Attack target highlight (Red)
					//node->getMaterial(0).AmbientColor.set(255,255,0,0);
					node->getMaterial(0).DiffuseColor.set(255,255,0,0);
				}

				else if (highlight == ATTACK_HOVER)
				{
					//Attack hover highlight (Light Red)
					//node->getMaterial(0).AmbientColor.set(255,255,80,80);
					node->getMaterial(0).DiffuseColor.set(255,255,80,80);
				}
			}
		}

		//Otherwise, if this token isn't highlighted...
		else
		{
			//Color it normally (Full White)
			//node->getMaterial(0).AmbientColor.set(255,255,255,255);
			node->getMaterial(0).DiffuseColor.set(255,255,255,255);
		}
	}

	//Otherwise, if this token already moved...
	else if (isFinished)
	{
		//Color it darker and grayer
		//node->getMaterial(0).AmbientColor.set(255,100,100,100);
		node->getMaterial(0).DiffuseColor.set(255,100,100,100);
	}
}