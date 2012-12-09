#include "IrrScene.h"

using namespace IrrBoardGameEngine;

enum
{
	ID_IsNotPickable = 0,
	IDFlag_IsPickable = 1 << 0,
	IDFlag_IsHighlightable = 1 << 1
};

IrrScene::IrrScene(IrrlichtDevice *device, ISoundEngine *se, IrrInput *inp)
{
	//pega o SceneManager
	smgr = device->getSceneManager();

	//pega drive
	driver = device->getVideoDriver();

	//cria o node root da scena
	rootScene = smgr->addEmptySceneNode();

	soundEngine = se;
	input = inp;

	currentBoard = NULL; 
	currentCamera = NULL;
	currentCollisionPoint = NULL;

	collMan = smgr->getSceneCollisionManager();
	selector = 0;

	objects = new vector<IrrGameObject*>();
}

IrrScene::~IrrScene(void)
{
	delete objects;
}

IrrParticleSystem * IrrScene::addParticleSystem()
{
	IrrParticleSystem * ps = new IrrParticleSystem(smgr, driver);
	rootScene->addChild(ps->node);
	ps->node->setParent(rootScene);
	return ps;
}

void IrrScene::removeParticleSystem(IrrParticleSystem * ps)
{
	delete ps;
}

ILightSceneNode* IrrScene::addLightSceneNode(const core::vector3df& position,video::SColorf color,f32 radius)
{
	return addLightSceneNode(rootScene,-1,position,color,radius);
}

ILightSceneNode* IrrScene::addLightSceneNode(ISceneNode* parent, s32 id, const core::vector3df& position,video::SColorf color,f32 radius)
{
	return smgr->addLightSceneNode(parent, position, color, radius, id);
}

void IrrScene::addObject(IrrGameObject *o){
	newObjects.push(o);
}

IrrGameObject *IrrScene::addCube(Vector* p)
{
	IrrGameObject *go = new IrrGameObject();
	go->node = smgr->addEmptySceneNode();
	go->node->setParent(rootScene);
	go->setMesh(new IrrMesh(smgr->addCubeSceneNode(10.0f,go->node,IDFlag_IsPickable | IDFlag_IsHighlightable,vector3df(p->x,p->y,p->z))));
	this->addObject(go);	
	return go;
}

IrrGameObject *IrrScene::addSphere(Vector* p)
{
	IrrGameObject *go = new IrrGameObject();
	go->node = smgr->addEmptySceneNode();
	go->node->setParent(rootScene);
	go->setMesh(new IrrMesh(smgr->addSphereSceneNode(10.0f,16,go->node,ID_IsNotPickable,vector3df(p->x,p->y,p->z))));
	this->addObject(go);	
	return go;
}

IrrGameObject *IrrScene::addCameraDefault(Vector* p, Vector* lookAt)
{
	IrrGameObject *go = new IrrGameObject();
	go->node = smgr->addEmptySceneNode();
	go->node->setParent(rootScene);

	IrrCamera * cam = new IrrCamera(smgr->addCameraSceneNode(go->node, vector3df(p->x,p->y,p->z), vector3df(lookAt->x,lookAt->y,lookAt->z)));	
	go->setCamera(cam);
	currentCamera = cam->node;

	input->setCamera(cam);
	this->addObject(go);
	return go;
}

IrrGameObject *IrrScene::addCameraFPS(f32 rotateSpeed, f32 moveSpeed, s32 id,
			SKeyMap* keyMapArray, s32 keyMapSize, bool noVerticalMovement,
			f32 jumpSpeed, bool invertMouse,
			bool makeActive)
{
	IrrGameObject *go = new IrrGameObject();
	go->node = smgr->addEmptySceneNode();
	go->node->setParent(rootScene);

	IrrCamera * cam = new IrrCamera(smgr->addCameraSceneNodeFPS(go->node,rotateSpeed, moveSpeed, id,
			keyMapArray, keyMapSize, noVerticalMovement,
			jumpSpeed, invertMouse,
			makeActive));

	go->setCamera(cam);
	currentCamera = cam->node;

	input->setCamera(cam);
	this->addObject(go);
	return go;
}

IrrGameObject *IrrScene::addCameraBoardGame(Vector* p, Vector* lookAt, Vector* focus_p, Vector* focus_lookAt)
{
	IrrGameObject *go = new IrrGameObject();
	go->node = smgr->addEmptySceneNode();
	go->node->setParent(rootScene);

	IrrCamera * cam = new IrrCamera(smgr->addCameraSceneNode(go->node, vector3df(p->x,p->y,p->z), vector3df(lookAt->x,lookAt->y,lookAt->z)),true);
	cam->setFocus(vector3df(focus_p->x,focus_p->y,focus_p->z), vector3df(focus_lookAt->x,focus_lookAt->y,focus_lookAt->z));
	go->setCamera(cam);
	currentCamera = cam->node;

	input->setCamera(cam);
	this->addObject(go);
	return go;
}

IrrGameObject *IrrScene::addAnimatedMesh(char *m, Vector* p)
{
	IrrGameObject *go = new IrrGameObject;
	go->node = smgr->addEmptySceneNode();
	go->node->setParent(rootScene);
	go->setAnimatedMesh(new IrrMeshAnimated(smgr->addAnimatedMeshSceneNode(smgr->getMesh(m),go->node,IDFlag_IsPickable | IDFlag_IsHighlightable,vector3df(p->x,p->y,p->z))));
	this->addObject(go);	
	return go;
}

IrrGameObject *IrrScene::addMesh(char *m, Vector* p)
{
	IrrGameObject *go = new IrrGameObject;
	go->node = smgr->addEmptySceneNode();
	go->node->setParent(rootScene);
	go->setMesh(new IrrMesh(smgr->addMeshSceneNode(smgr->getMesh(m),go->node,IDFlag_IsPickable | IDFlag_IsHighlightable,vector3df(p->x,p->y,p->z))));
	this->addObject(go);	
	return go;
}

IrrBoard *IrrScene::addStaticBoard(std::string src,Vector*p)
{
	return addBoard(src, p);
}

IrrBoard *IrrScene::addAnimatedBoard(std::string src,Vector*p,bool shadow)
{
	return addBoard(src, p, true, shadow);
}

IrrBoard *IrrScene::addBoard(std::string src,Vector*p,bool animated, bool shadow)
{
	IrrBoard *go = new IrrBoard();
	std::string m;
	
	if(IrrLoader::loadBoard(src,go))
	{
		go->node = smgr->addEmptySceneNode();
		go->node->setParent(rootScene);

		p->x -= go->width / 2;
		p->z += go->length / 2;
		
		for(int i=0;i < go->tile_i; i++)
		{
			for(int j=0; j < go->tile_j; j++)
			{
				m = go->objs->at(go->board[i][j]->idx);

				if(animated)
				{
					IAnimatedMesh * ms = smgr->getMesh(m.c_str());
					IAnimatedMeshSceneNode * c = smgr->addAnimatedMeshSceneNode(ms,go->node,IDFlag_IsPickable,vector3df((p->x+(j*go->tile_width)),p->y,(p->z-(i*go->tile_length))));
					if(shadow)
					{
						c->addShadowVolumeSceneNode(ms,ID_IsNotPickable);
					}
					go->board[i][j]->node = c;
				}
				else
				{
					go->board[i][j]->node = smgr->addMeshSceneNode(smgr->getMesh(m.c_str()),go->node,IDFlag_IsPickable,vector3df((p->x+(j*go->tile_width)),p->y,(p->z-(i*go->tile_length))));
				}
				go->node->addChild(go->board[i][j]->node);
				go->board[i][j]->node->setParent(go->node);

				selector = smgr->createTriangleSelectorFromBoundingBox(go->board[i][j]->node);
				go->board[i][j]->node->setTriangleSelector(selector);
				selector->drop();
			}
		}

		this->addObject(go);
		currentBoard = go;
		selector = smgr->createTriangleSelectorFromBoundingBox(go->node);
		go->node->setTriangleSelector(selector);
		selector->drop();
	}

	return go;
}

IrrGameObject *IrrScene::addAudio(const char *filename, int id, Vector *p)
{
	IrrGameObject *go = new IrrGameObject;
	go->node = smgr->addEmptySceneNode();
	
	IrrAudio *ad = new IrrAudio(soundEngine,go->node,smgr,id);
	ad->setSoundFileName(filename);
	ad->stop();
	go->setAudio(ad);
	go->setPosition(*p);
	
	this->addObject(go);
	
	return go;
}

ISceneNode * IrrScene::getSceneNodeAndCollisionPointFromRay()
{
	ray = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(input->getMouseState().position, currentCamera);


	Vector nm((float)ray.end.X, (float)ray.end.Y, (float)ray.end.Z);

	ISceneNode * node = collMan->getSceneNodeAndCollisionPointFromRay(
				ray,
				intersection,
				hitTriangle,
				IDFlag_IsPickable,
				rootScene);

	return node;
}

void IrrScene::update()
{
	while(newObjects.size() != 0)
	{
		objects->push_back(newObjects.top());
		newObjects.pop();
	}

	if(currentBoard != NULL && currentCamera != NULL)
	{
		currentCollisionPoint = getSceneNodeAndCollisionPointFromRay();
		currentBoard->setHighlight(currentCollisionPoint);
	}

	vector<IrrGameObject*>::iterator i;	
	for(i=objects->begin(); i!=objects->end(); i++)
	{
		(*i)->update();
	}
}

void IrrScene::removeBoard()
{
	removeBoard(currentBoard);
	currentBoard = NULL;
}

void IrrScene::removeBoard(IrrBoard * board)
{	
	vector<IrrGameObject*>::iterator i;

	for(i=objects->begin(); i!=objects->end(); i++)
	{
		if(board == (*i))
		{			
			break;
		}
	}

	if(i != objects->end())
	{
		objects->erase(i);		
		delete board;
	}
}

void IrrScene::setCamera(IrrCamera * camera)
{
	currentCamera = camera->node;
	input->setCamera(camera);
}

void IrrScene::setBoard(IrrBoard * board)
{
	currentBoard = board;
}

void IrrScene::drawAll()
{
	smgr->drawAll();
}

ISceneManager *IrrScene::getSceneManager()
{
	return smgr;
}

void IrrScene::setActive(bool flag)
{
	rootScene->setVisible(flag);
}