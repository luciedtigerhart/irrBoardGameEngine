#include "PrimeTile.h"

PrimeTile::PrimeTile()
{
	/*
	//Create highlight planes
	highlightMove->node = scene->smgr->addMeshSceneNode(scene->smgr->getMesh("obj/nome_do_modelo.obj"), highlightMove->node, idx, node->getPosition());
	highlightMove->node->setParent(node);

	highlightMoveHover->node = scene->smgr->addMeshSceneNode(scene->smgr->getMesh("obj/nome_do_modelo.obj"), highlightMove->node, idx, node->getPosition());
	highlightMoveHover->node->setParent(node);

	highlightPush->node = scene->smgr->addMeshSceneNode(scene->smgr->getMesh("obj/nome_do_modelo.obj"), highlightMove->node, idx, node->getPosition());
	highlightPush->node->setParent(node);

	highlightPushHover->node = scene->smgr->addMeshSceneNode(scene->smgr->getMesh("obj/nome_do_modelo.obj"), highlightMove->node, idx, node->getPosition());
	highlightPushHover->node->setParent(node);

	highlightAttack->node = scene->smgr->addMeshSceneNode(scene->smgr->getMesh("obj/nome_do_modelo.obj"), highlightMove->node, idx, node->getPosition());
	highlightAttack->node->setParent(node);

	highlightAttackHover->node = scene->smgr->addMeshSceneNode(scene->smgr->getMesh("obj/nome_do_modelo.obj"), highlightMove->node, idx, node->getPosition());
	highlightAttackHover->node->setParent(node);
	*/
};

PrimeTile::~PrimeTile() {};

void PrimeTile::turnOffHighlightsExcept(int exception)
{
	if (exception != MOVE) highlightMove->node->setVisible(false);
	if (exception != MOVE_HOVER) highlightMoveHover->node->setVisible(false);
	if (exception != PUSH) highlightPush->node->setVisible(false);
	if (exception != PUSH_HOVER) highlightPushHover->node->setVisible(false);
	if (exception != ATTACK) highlightAttack->node->setVisible(false);
	if (exception != ATTACK_HOVER) highlightAttackHover->node->setVisible(false);
}

void PrimeTile::init()
{
	//Update graph parent
	//node->setParent(board->node);

	//Highlights are deactivated by default
	turnOffHighlightsExcept(NONE);

	//Activate lighting
	tile->node->setMaterialFlag(EMF_LIGHTING, true);
}

void PrimeTile::update()
{
	//If this tile is highlighted...
	if (isHighlighted)
	{
		//Activate the correct highlight plane and deactivate all others
		if (highlight == MOVE) { highlightMove->setActive(true); turnOffHighlightsExcept(MOVE); }
		else if (highlight == MOVE_HOVER) { highlightMoveHover->setActive(true); turnOffHighlightsExcept(MOVE_HOVER); }
		else if (highlight == PUSH) { highlightPush->setActive(true); turnOffHighlightsExcept(PUSH); }
		else if (highlight == PUSH_HOVER) { highlightPushHover->setActive(true); turnOffHighlightsExcept(PUSH_HOVER); }
		else if (highlight == ATTACK) { highlightAttack->setActive(true); turnOffHighlightsExcept(ATTACK); }
		else if (highlight == ATTACK_HOVER) { highlightAttackHover->setActive(true); turnOffHighlightsExcept(ATTACK_HOVER); }
	}

	//Otherwise, if this tile isn't highlighted...
	else
	{
		//Deactivate all highlights
		turnOffHighlightsExcept(NONE);
	}
}