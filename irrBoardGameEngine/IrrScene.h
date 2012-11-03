#pragma once

#include "irrlicht.h"
#include "irrKlang.h"
#include "Vector.h"
#include <stack>
#include <string>
#include <vector>

#include "IrrInput.h"

#include "IrrGameObject.h"

#include "IrrTile.h"
#include "IrrBoard.h"

#include "IrrLoader.h"
#include "IrrMesh.h"
#include "IrrParticleSystem.h"
#include "IrrCamera.h"

using namespace irr;
using namespace scene;
using namespace core;
using namespace irrklang;
using namespace std;

namespace IrrBoardGameEngine {
	class IrrScene
	{
	private:
		ISceneManager *smgr;
		IrrInput *input;
		ISoundEngine *soundEngine;
		IVideoDriver *driver;

		vector<IrrGameObject*> *objects;
		stack<IrrGameObject*> newObjects;

		// All intersections in this example are done with a ray cast out from the camera to
		// a distance of 1000.  You can easily modify this to check (e.g.) a bullet
		// trajectory or a sword's position, or create a ray from a mouse click position using
		// ISceneCollisionManager::getRayFromScreenCoordinates()
		core::line3d<f32> ray;

		// Tracks the current intersection point with the level or a mesh
		core::vector3df intersection;
		// Used to show with triangle has been hit
		core::triangle3df hitTriangle;

		ISceneNode * rootScene;
		ISceneNode * currentCollisionPoint;
		ICameraSceneNode * currentCamera;
		IrrBoard * currentBoard;

		ISceneCollisionManager* collMan;

		ISceneNode * getSceneNodeAndCollisionPointFromRay();
		ITriangleSelector* selector;

		IrrGameObject * bola;
	protected:
		void addObject(IrrGameObject*);

	public:
		void update();

		//adiciona objetos na cena
		IrrGameObject *addCube(Vector*);
		IrrGameObject *addSphere(Vector*);
		IrrGameObject *addAnimatedMesh(char *,Vector*);
		IrrGameObject *addMesh(char *,Vector*);
		IrrBoard *addBoard(std::string src,Vector*);
		IrrGameObject *addCamera(Vector*,Vector*);
		IrrGameObject *addAudio(const char *,int,Vector*);

		ILightSceneNode * addLightSceneNode(const core::vector3df& position = core::vector3df(0,0,0),
			video::SColorf color = video::SColorf(1.0f, 1.0f, 1.0f),
			f32 radius=100.0f);

		ILightSceneNode * addLightSceneNode(ISceneNode* parent = 0, s32 id=-1, const core::vector3df& position = core::vector3df(0,0,0),
			video::SColorf color = video::SColorf(1.0f, 1.0f, 1.0f),
			f32 radius=100.0f);

		IrrParticleSystem * addParticleSystem();

		//construtora
		IrrScene(IrrlichtDevice *,ISoundEngine *,IrrInput *);
		~IrrScene(void);

		//para definir a camera padrão
		void setCamera(IrrCamera * camera);

		//para definir a camera padrão
		void setBoard(IrrBoard * board);
		void removeBoard();
		void removeBoard(IrrBoard * board);

		//ativa a scena
		void setActive(bool flag);

		//manda desenhar a cena
		void drawAll();

		//pega o scene
		ISceneManager *getSceneManager();
	};
}