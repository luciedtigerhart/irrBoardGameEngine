#include "PrimeTile.h"

PrimeTile::PrimeTile() {};
PrimeTile::~PrimeTile() {};

void PrimeTile::turnOnHighlight(int type)
{
	//Deactivate highlight
	if (type == NONE) highlightPlane->setVisible(false);
	
	else
	{
		//Activate highlight
		highlightPlane->setVisible(true);

		//Set material to correct type of highlight
		if (type == MOVE)
		{
			//Move and ressurrect highlight (Light blue)
			highlightPlane->getMaterial(0) = matPlaneNormal;
			highlightPlane->getMaterial(0).EmissiveColor.set(255,40,80,255);
			highlightPlane->getMaterial(0).SpecularColor.set(255,40,80,255);
		}

		else if (type == MOVE_HOVER)
		{
			//Move and ressurrect hover highlight (Very Light blue)
			highlightPlane->getMaterial(0) = matPlaneHover;
			highlightPlane->getMaterial(0).EmissiveColor.set(255,100,180,255);
			highlightPlane->getMaterial(0).SpecularColor.set(255,100,180,255);
		}

		else if (type == PUSH)
		{
			//Push highlight (Orange)
			highlightPlane->getMaterial(0) = matPlaneNormal;
			highlightPlane->getMaterial(0).EmissiveColor.set(255,255,70,0);
			highlightPlane->getMaterial(0).SpecularColor.set(255,255,70,0);
		}

		else if (type == PUSH_HOVER)
		{
			//Push hover highlight (Light Orange)
			highlightPlane->getMaterial(0) = matPlaneHover;
			highlightPlane->getMaterial(0).EmissiveColor.set(255,255,110,40);
			highlightPlane->getMaterial(0).SpecularColor.set(255,255,110,40);
		}

		else if (type == ATTACK)
		{
			//Attack highlight (Red)
			highlightPlane->getMaterial(0) = matPlaneNormal;
			highlightPlane->getMaterial(0).EmissiveColor.set(255,255,0,0);
			highlightPlane->getMaterial(0).SpecularColor.set(255,255,0,0);
		}

		else if (type == ATTACK_HOVER)
		{
			//Attack hover highlight (Light Red)
			highlightPlane->getMaterial(0) = matPlaneHover;
			highlightPlane->getMaterial(0).EmissiveColor.set(255,255,80,80);
			highlightPlane->getMaterial(0).SpecularColor.set(255,255,80,80);
		}
	}
}

void PrimeTile::init()
{
	//Highlight plane has tranparent texture
	matPlaneNormal.setTexture(0, driver->getTexture("obj/tiles/highlight/tileHighlight.jpg"));
	matPlaneNormal.MaterialType = EMT_TRANSPARENT_ADD_COLOR;
	matPlaneNormal.Lighting = true;

	//Highlight plane hover has a symbol on the texture
	matPlaneHover.setTexture(0, driver->getTexture("obj/tiles/highlight/tileHover.jpg"));
	matPlaneHover.MaterialType = EMT_TRANSPARENT_ADD_COLOR;
	matPlaneHover.Lighting = true;

	//Create highlight plane
	IAnimatedMesh* plane = smgr->addHillPlaneMesh("Highlight Plane", // Name of mesh
      core::dimension2d<f32>(1.8,1.8), //	Size of a tile of the mesh
      core::dimension2d<u32>(1,1), 0, 0, // Specifies how many tiles there will be
      core::dimension2d<f32>(0,0), //Material 
      core::dimension2d<f32>(1,1)); //countHills 
	
	//Add highlight plane to scene
	highlightPlane = smgr->addMeshSceneNode(plane->getMesh(0), tile->node, -1, vector3df(0.0f,0.25f,0.0f));
	highlightPlane->getMaterial(0) = matPlaneNormal;

	//Highlights are deactivated by default
	turnOnHighlight(NONE);

	//Activate lighting
	tile->node->setMaterialFlag(EMF_LIGHTING, true);
}

void PrimeTile::update()
{
	float deltaTime = IrrEngine::getInstance()->getDeltaTime();

	//If this tile is highlighted...
	if (tile->isHighlighted)
	{
		//Activate the correct highlight plane

		if (tile->isMouseHover || (tile->token != NULL && tile->token->isMouseHover))
		{
			if (tile->highlight == MOVE_HOVER || tile->highlight == RESSURRECT_HOVER)
			{
				turnOnHighlight(MOVE_HOVER);
			}

			else if (tile->highlight == PUSH_HOVER) turnOnHighlight(PUSH_HOVER);
			else if (tile->highlight == ATTACK_HOVER) turnOnHighlight(ATTACK_HOVER);
			else turnOnHighlight(NONE);
		}

		else
		{
			if (tile->highlight == MOVE || tile->highlight == RESSURRECT)
			{
				turnOnHighlight(MOVE);
			}

			else if (tile->highlight == PUSH) turnOnHighlight(PUSH);
			else if (tile->highlight == ATTACK) turnOnHighlight(ATTACK);
			else turnOnHighlight(NONE);
		}
	}

	//Otherwise, if this tile isn't highlighted...
	else
	{
		//Deactivate highlight
		turnOnHighlight(NONE);
	}
}