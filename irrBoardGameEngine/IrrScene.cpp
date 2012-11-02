#include "IrrScene.h"

using namespace IrrBoardGameEngine;

enum
{
	// I use this ISceneNode ID to indicate a scene node that is
	// not pickable by getSceneNodeAndCollisionPointFromRay()
	ID_IsNotPickable = 0,

	// I use this flag in ISceneNode IDs to indicate that the
	// scene node can be picked by ray selection.
	IDFlag_IsPickable = 1 << 0,

	// I use this flag in ISceneNode IDs to indicate that the
	// scene node can be highlighted.  In this example, the
	// homonids can be highlighted, but the level mesh can't.
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

	//bola = addSphere(new Vector(0.0f, 0.0f, 0.0f));
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
void  IrrScene::addLightSceneNode(const core::vector3df& position,video::SColorf color,f32 radius)
{
	addLightSceneNode(rootScene,-1,position,color,radius);
}

void  IrrScene::addLightSceneNode(ISceneNode* parent, s32 id, const core::vector3df& position,video::SColorf color,f32 radius)
{
	smgr->addLightSceneNode(parent, position, color, radius, id);
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

IrrGameObject *IrrScene::addCamera(Vector* p, Vector* lookAt)
{
	IrrGameObject *go = new IrrGameObject();
	go->node = smgr->addEmptySceneNode();
	go->node->setParent(rootScene);

	IrrCamera * cam = new IrrCamera(smgr->addCameraSceneNode(go->node, vector3df(p->x,p->y,p->z), vector3df(lookAt->x,lookAt->y,lookAt->z)));	
	go->setCamera(cam);
	currentCamera = cam->node;
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

IrrBoard *IrrScene::addBoard(std::string src, Vector* p)
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

				go->board[i][j]->node = smgr->addMeshSceneNode(smgr->getMesh(m.c_str()),go->node,IDFlag_IsPickable,vector3df((p->x+(j*go->tile_width)),p->y,(p->z-(i*go->tile_length))));

				go->node->addChild(go->board[i][j]->node);
				go->board[i][j]->node->setParent(go->node);

				selector = smgr->createTriangleSelectorFromBoundingBox(go->board[i][j]->node);
				go->board[i][j]->node->setTriangleSelector(selector);
				selector->drop();

				//std::cout << i << " " << j << " | ";
			}
			//std::cout << endl;
		}

		this->addObject(go);
		currentBoard = go;
		selector = smgr->createTriangleSelectorFromBoundingBox(go->node);
		go->node->setTriangleSelector(selector);
		selector->drop();
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

ISceneNode * IrrScene::getSceneNodeAndCollisionPointFromRay()
{
	//ray.start = currentCamera->getPosition();
	//ray.end = ray.start + (currentCamera->getTarget() - ray.start).normalize() * 1000.0f;

	ray = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(input->getMouseState().position, currentCamera);

	//std::cout << ray.start.X << "," << ray.start.Y << "," << ray.start.Z << endl;
	//std::cout << ray.end.X << "," << ray.end.Y << "," << ray.end.Z << endl;


	Vector nm((float)ray.end.X, (float)ray.end.Y, (float)ray.end.Z);

	//bola->setPosition(nm);

	ISceneNode * node = collMan->getSceneNodeAndCollisionPointFromRay(
				ray,
				intersection, // This will be the position of the collision
				hitTriangle, // This will be the triangle hit in the collision
				IDFlag_IsPickable, // This ensures that only nodes that we have
									// set up to be pickable are considered
									rootScene); // Check the entire scene (this is actually the implicit default)

	//if(node != NULL) std::cout << "ACHOU" << endl;

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