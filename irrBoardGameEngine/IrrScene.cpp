#include "IrrScene.h"

using namespace IrrBoardGameEngine;

IrrScene::IrrScene(ISceneManager *sm, ISoundEngine *se)
{
	smgr = sm;
	soundEngine = se;

	objects = new vector<IrrGameObject*>();
}

IrrScene::~IrrScene(void)
{
	delete objects;
}

void IrrScene::addObject(IrrGameObject *o){
	newObjects.push(o);
}

IrrGameObject *IrrScene::addCube(Vector* p)
{
	IrrGameObject *go = new IrrGameObject();
	go->node = smgr->addEmptySceneNode();
	go->setMesh(new IrrMesh(smgr->addCubeSceneNode(10.0f,go->node,-1,vector3df(p->x,p->y,p->z))));
	this->addObject(go);	
	return go;
}

IrrGameObject *IrrScene::addSphere(Vector* p)
{
	IrrGameObject *go = new IrrGameObject();
	go->node = smgr->addEmptySceneNode();
	go->setMesh(new IrrMesh(smgr->addSphereSceneNode(10.0f,16,go->node,-1,vector3df(p->x,p->y,p->z))));
	this->addObject(go);	
	return go;
}

IrrGameObject *IrrScene::addCamera(Vector* p, Vector* lookAt)
{
	IrrGameObject *go = new IrrGameObject();
	go->node = smgr->addEmptySceneNode();
	go->setCamera(new IrrCamera(smgr->addCameraSceneNode(go->node, vector3df(p->x,p->y,p->z), vector3df(lookAt->x,lookAt->y,lookAt->z))));
	this->addObject(go);
	return go;
}

IrrGameObject *IrrScene::addMesh(char *m, Vector* p)
{
	IrrGameObject *go = new IrrGameObject;
	go->node = smgr->addEmptySceneNode();
	go->setMesh(new IrrMesh(smgr->addMeshSceneNode(smgr->getMesh(m),go->node,-1,vector3df(p->x,p->y,p->z))));
	this->addObject(go);	
	return go;
}

IrrBoard *IrrScene::addBoard(std::string src, Vector* p)
{
	IrrBoard *go = new IrrBoard();
	std::string m;
	
	if(IrrLoader::loadBoard(src,go))
	{
		go->node = smgr->addEmptySceneNode();

		p->x -= go->width / 2;
		p->z -= go->length / 2;
		
		for(int i=0;i < go->tile_i; i++)
		{
			for(int j=0; j < go->tile_j; j++)
			{
				m = go->objs->at(go->board[i][j]->idx);
				go->board[i][j]->node = smgr->addMeshSceneNode(smgr->getMesh(m.c_str()),go->node,-1,vector3df((p->x+(i*go->tile_width)),p->y,(p->z+(j*go->tile_length))));
				go->node->addChild(go->board[i][j]->node);
				go->board[i][j]->node->setParent(go->node);
			}
		}
	}

	return go;
}

/*
GameObject *IrrScene::addAnimatedMesh(char *am, Vector* p)
{
	GameObject *go = new GameObject;
	((IrrGameObjectImpl*)go->getImplementor())->node = smgr->addEmptySceneNode();
	go->setAnimation(new IrrAnimatedMesh(smgr->addAnimatedMeshSceneNode(smgr->getMesh(am),((IrrGameObjectImpl*)go->getImplementor())->node,-1,vector3df(p->x,p->y,p->z))));
	this->addObject(go);	
	return go;
}

GameObject *IrrScene::addAudio(const char *filename,int id,Vector *p)
{
	GameObject *go = new GameObject;
	((IrrGameObjectImpl*)go->getImplementor())->node = smgr->addEmptySceneNode();

	IrrKlangSceneNode *ad;
	ad = new IrrKlangSceneNode(soundEngine,
		((IrrGameObjectImpl*)go->getImplementor())->node,
		smgr,
		id);
	ad->setSoundFileName(filename);
	go->setAudio(ad);
	go->setPosition(*p);
	
	this->addObject(go);		
	return go;
}
*/
void IrrScene::update(){
	while(newObjects.size() != 0){
		objects->push_back(newObjects.top());
		newObjects.pop();
	}

	vector<IrrGameObject*>::iterator i;	
	for(i=objects->begin(); i!=objects->end(); i++){		
		(*i)->update();
	}
}