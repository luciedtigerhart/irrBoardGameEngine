#include "PrimeTile.h"

#define GRASS_1 0
#define GRASS_2 1

PrimeTile::PrimeTile(PrimeTeam p1, PrimeTeam p2, PrimeTeam p3, PrimeTeam p4)
{
	//No ghost token by default
	ghost = NULL;

	raceP1 = raceP2 = raceP3 = raceP4 = -1;
	idxP1 = idxP2 = idxP3 = idxP4 = -1;

	//Get team races and indexes
	if (p1.isActive) { raceP1 = p1.assignedRace; idxP1 = p1.idx; }
	if (p2.isActive) { raceP2 = p2.assignedRace; idxP2 = p2.idx; }
	if (p3.isActive) { raceP3 = p3.assignedRace; idxP3 = p3.idx; }
	if (p4.isActive) { raceP4 = p4.assignedRace; idxP4 = p4.idx; }

	angle = 0.0f;
	then = IrrEngine::getInstance()->getDevice()->getTimer()->getTime();
};

PrimeTile::~PrimeTile()
{
	//Delete ghost if it has been loaded
	if (ghost != NULL) delete ghost;
};

void PrimeTile::addGhostBehavior(IrrTokenBehavior * behavior)
{
	//Initialize and set parent
	ghost = new IrrToken();
	ghost->parentNode = tile;

	//Set associated token
	behavior->setToken(ghost);

	//Set engine components
	behavior->driver = driver;
	behavior->smgr = smgr;
	behavior->soundEngine = soundEngine;
	behavior->input = input;
	behavior->init();

	//Set new behavior
	ghost->addBehaviour(behavior);
}

void PrimeTile::loadGhost()
{
	PrimeTeam player;
	bool playerLoaded = false;

	//Load ghost token based on type of tile and teams
	
	//If this is a Team 1 safe zone...
	if (tile->inf == SAFE_ZONE_TEAM_1)
	{
		//If P1 is active...
		if (idxP1 != -1) { player.assignedRace = raceP1; player.idx = idxP1; playerLoaded = true; }
	}
	
	//If this is a Team 2 safe zone...
	else if (tile->inf == SAFE_ZONE_TEAM_2)
	{
		//If P2 is active...
		if (idxP2 != -1) { player.assignedRace = raceP2; player.idx = idxP2; playerLoaded = true; }
	}
	
	//If this is a Team 3 safe zone...
	else if (tile->inf == SAFE_ZONE_TEAM_3)
	{
		//If P3 is active...
		if (idxP3 != -1) { player.assignedRace = raceP3; player.idx = idxP3; playerLoaded = true; }
	}
	
	//If this is a Team 4 safe zone...
	else if (tile->inf == SAFE_ZONE_TEAM_4)
	{
		//If P4 is active...
		if (idxP4 != -1) { player.assignedRace = raceP4; player.idx = idxP4; playerLoaded = true; }
	}

	//Load ghost
	if (playerLoaded)
	{
		//Set special ghost identifier
		player.primevalium = -6969;

		//Add token behavior to ghost
		addGhostBehavior(new PrimeToken(player));
	}
}

void PrimeTile::turnOnHighlight(int type)
{
	//Deactivate highlight
	if (type == NONE) highlightPlane->setVisible(false);
	
	else
	{
		//Activate highlight
		highlightPlane->setVisible(true);

		//Set material to correct type of highlight

		//Ressurrect highlight (White)
		if (type == RESSURRECT) highlightPlane->getMaterial(0) = matPlaneRessurrectNormal;
		else if (type == RESSURRECT_HOVER) highlightPlane->getMaterial(0) = matPlaneRessurrectHover;

		//Move highlight (Light blue)
		else if (type == MOVE) highlightPlane->getMaterial(0) = matPlaneMoveNormal;
		else if (type == MOVE_HOVER) highlightPlane->getMaterial(0) = matPlaneMoveHover;

		//Push highlight (Orange)
		else if (type == PUSH) highlightPlane->getMaterial(0) = matPlanePushNormal;
		else if (type == PUSH_HOVER) highlightPlane->getMaterial(0) = matPlanePushHover;

		//Attack highlight (Red)
		else if (type == ATTACK) highlightPlane->getMaterial(0) = matPlaneAttackNormal;
		else if (type == ATTACK_HOVER) highlightPlane->getMaterial(0) = matPlaneAttackHover;
	}
}

void PrimeTile::paintSafeZone()
{
	//Change tile texture according to team, if its a safe zone tile

	if (tile->inf == SAFE_ZONE_TEAM_1)
	{
		if (tile->idx == GRASS_1) tile->node->getMaterial(0).setTexture(0, driver->getTexture("obj/tiles/tile_grama_1_sf1.jpg"));
		if (tile->idx == GRASS_2) tile->node->getMaterial(0).setTexture(0, driver->getTexture("obj/tiles/tile_grama_2_sf1.jpg"));
	}
	else if (tile->inf == SAFE_ZONE_TEAM_2)
	{
		if (tile->idx == GRASS_1) tile->node->getMaterial(0).setTexture(0, driver->getTexture("obj/tiles/tile_grama_1_sf2.jpg"));
		if (tile->idx == GRASS_2) tile->node->getMaterial(0).setTexture(0, driver->getTexture("obj/tiles/tile_grama_2_sf2.jpg"));
	}
	else if (tile->inf == SAFE_ZONE_TEAM_3)
	{
		if (tile->idx == GRASS_1) tile->node->getMaterial(0).setTexture(0, driver->getTexture("obj/tiles/tile_grama_1_sf3.jpg"));
		if (tile->idx == GRASS_2) tile->node->getMaterial(0).setTexture(0, driver->getTexture("obj/tiles/tile_grama_2_sf3.jpg"));
	}
	else if (tile->inf == SAFE_ZONE_TEAM_4)
	{
		if (tile->idx == GRASS_1) tile->node->getMaterial(0).setTexture(0, driver->getTexture("obj/tiles/tile_grama_1_sf4.jpg"));
		if (tile->idx == GRASS_2) tile->node->getMaterial(0).setTexture(0, driver->getTexture("obj/tiles/tile_grama_2_sf4.jpg"));
	}
}

void PrimeTile::rotateHighlight(float speed)
{
	//Calculate frame-independent time
	now = IrrEngine::getInstance()->getDevice()->getTimer()->getTime();
	deltaTime = (float)(now - then) / 1000.f;

	//Increment rotation
	angle += speed * deltaTime;
	if (angle > 360.0f) angle = 0.0f;

	//Rotate highlight plane on Y axis
	highlightPlane->setRotation(vector3df(0.0f, angle, 0.0f));

	//Update time
	then = IrrEngine::getInstance()->getDevice()->getTimer()->getTime();
}

void PrimeTile::init()
{
	//Re-texture and paint this tile if its a safe zone
	paintSafeZone();

	//Ressurrection highlight plane normal state
	matPlaneRessurrectNormal.setTexture(0, driver->getTexture("obj/tiles/highlight/highlight_ressurrect_normal.jpg"));
	matPlaneRessurrectNormal.MaterialType = EMT_TRANSPARENT_ADD_COLOR; //Highlight planes have tranparent texture
	matPlaneRessurrectNormal.Lighting = true;

	//Ressurrection highlight plane hovered state
	matPlaneRessurrectHover.setTexture(0, driver->getTexture("obj/tiles/highlight/highlight_ressurrect_hover.jpg"));
	matPlaneRessurrectHover.MaterialType = EMT_TRANSPARENT_ADD_COLOR;
	matPlaneRessurrectHover.Lighting = true;

	//Movement highlight plane normal state
	matPlaneMoveNormal.setTexture(0, driver->getTexture("obj/tiles/highlight/highlight_move_normal.jpg"));
	matPlaneMoveNormal.MaterialType = EMT_TRANSPARENT_ADD_COLOR;
	matPlaneMoveNormal.Lighting = true;

	//Movement highlight plane hovered state
	matPlaneMoveHover.setTexture(0, driver->getTexture("obj/tiles/highlight/highlight_move_hover.jpg"));
	matPlaneMoveHover.MaterialType = EMT_TRANSPARENT_ADD_COLOR;
	matPlaneMoveHover.Lighting = true;

	//Push highlight plane normal state
	matPlanePushNormal.setTexture(0, driver->getTexture("obj/tiles/highlight/highlight_push_normal.jpg"));
	matPlanePushNormal.MaterialType = EMT_TRANSPARENT_ADD_COLOR;
	matPlanePushNormal.Lighting = false;

	//Push highlight plane hovered state
	matPlanePushHover.setTexture(0, driver->getTexture("obj/tiles/highlight/highlight_push_hover.jpg"));
	matPlanePushHover.MaterialType = EMT_TRANSPARENT_ADD_COLOR;
	matPlanePushHover.Lighting = false;

	//Attack highlight plane normal state
	matPlaneAttackNormal.setTexture(0, driver->getTexture("obj/tiles/highlight/highlight_attack_normal.jpg"));
	matPlaneAttackNormal.MaterialType = EMT_TRANSPARENT_ADD_COLOR;
	matPlaneAttackNormal.Lighting = false;

	//Attack highlight plane hovered state
	matPlaneAttackHover.setTexture(0, driver->getTexture("obj/tiles/highlight/highlight_attack_hover.jpg"));
	matPlaneAttackHover.MaterialType = EMT_TRANSPARENT_ADD_COLOR;
	matPlaneAttackHover.Lighting = false;

	//Create highlight plane
	IAnimatedMesh* plane = smgr->addHillPlaneMesh("Highlight Plane", // Name of mesh
		core::dimension2d<f32>(8.8f,8.8f), //	Size of a tile of the mesh
		core::dimension2d<u32>(1,1), 0, 0, // Specifies how many tiles there will be
		core::dimension2d<f32>(0,0), //Material
		core::dimension2d<f32>(1,1)); //countHills
	
	//Add highlight plane to scene
	highlightPlane = smgr->addMeshSceneNode(plane->getMesh(0), tile->node, -1, vector3df(0.0f,0.05f,0.0f));
	highlightPlane->getMaterial(0) = matPlaneMoveNormal;

	//Highlights are deactivated by default
	turnOnHighlight(NONE);

	//Load ghost token, if necessary...
	loadGhost();

	//...And deactivate it.
	if (ghost != NULL) ghost->setActive(false);

	//Activate lighting
	tile->node->setMaterialType(EMT_SOLID);
	tile->node->setMaterialFlag(EMF_LIGHTING, true);

	//Set correct tile scale
	tile->setScale(Vector(0.2145f,0.2145f,0.2145f));
	//tile->node->getMaterial(0).NormalizeNormals = true;
}

void PrimeTile::reset()
{
};

void PrimeTile::update()
{
	//Scale highlight plane back to original size, in case its been scaled elsewhere
	highlightPlane->setScale(vector3df(1.0f, 1.0f, 1.0f));

	//Rotate highlight plane
	rotateHighlight(20.0f);

	//Ghost token is normally invisible
	if (ghost != NULL) ghost->setActive(false);

	//If this tile is highlighted...
	if (tile->isHighlighted)
	{
		//Activate the correct highlight plane

		if (tile->isMouseHover || (tile->token != NULL && tile->token->isMouseHover))
		{
			if (tile->highlight == RESSURRECT_HOVER)
			{
				turnOnHighlight(RESSURRECT_HOVER);

				//Show ghost token when hovering a ressurrection tile
				if (ghost != NULL) ghost->setActive(true);
			}

			else if (tile->highlight == MOVE_HOVER)
			{
				turnOnHighlight(MOVE_HOVER);
			}

			else if (tile->highlight == PUSH_HOVER) turnOnHighlight(PUSH_HOVER);
			else if (tile->highlight == ATTACK_HOVER) turnOnHighlight(ATTACK_HOVER);
			else turnOnHighlight(NONE);

			//If there's a token on this tile, and its not selected...
			if (tile->token != NULL && !tile->token->getBehavior(0)->getBool("isSelected"))
			{
				//Scale highlight plane a bit
				highlightPlane->setScale(vector3df(1.2f, 1.0f, 1.2f));
			}
		}

		else
		{
			if (tile->highlight == RESSURRECT) turnOnHighlight(RESSURRECT);

			else if (tile->highlight == MOVE)
			{
				turnOnHighlight(MOVE);
			}

			else if (tile->highlight == PUSH) turnOnHighlight(PUSH);
			else if (tile->highlight == ATTACK) turnOnHighlight(ATTACK);
			else turnOnHighlight(NONE);

			//If there's a token on this tile, and its not selected...
			if (tile->token != NULL && !tile->token->getBehavior(0)->getBool("isSelected"))
			{
				//Scale highlight plane a bit
				highlightPlane->setScale(vector3df(1.2f, 1.0f, 1.2f));
			}
		}
	}

	//Otherwise, if this tile isn't highlighted...
	else
	{
		//Deactivate highlight
		turnOnHighlight(NONE);
	}
}

void PrimeTile::setInt(char const * key, int value)
{
}

int PrimeTile::getInt(char const * key)
{
	return 0;
}

void PrimeTile::setFloat(char const * key, float value)
{
}

float PrimeTile::getFloat(char const * key)
{
	return 0;
}

void PrimeTile::setBool(char const * key, bool value)
{
}

bool PrimeTile::getBool(char const * key)
{
	return false;
}

void PrimeTile::setVector(char const * key, Vector value)
{
}

Vector PrimeTile::getVector(char const * key)
{
	return 0;
}