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
#include "IrrMeshAnimated.h"
#include "IrrParticleSystem.h"
#include "IrrCamera.h"
#include "IrrAudio.h"

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

		core::line3d<f32> ray;
		core::vector3df intersection;
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
		IrrBoard *addBoard(std::string src,Vector*,bool animated = false, bool shadow = false);

	public:
		void update();

		//adiciona objetos na cena
		IrrGameObject *addCube(Vector*);
		IrrGameObject *addSphere(Vector*);
		IrrGameObject *addAnimatedMesh(char *,Vector*);
		IrrGameObject *addMesh(char *,Vector*);
		IrrBoard *addStaticBoard(std::string src,Vector*);
		IrrBoard *addAnimatedBoard(std::string src,Vector*,bool shadow = false);
		
		IrrGameObject *addCameraDefault(Vector*,Vector*);
		IrrGameObject *addCameraFPS(f32 rotateSpeed = 100.0f, f32 moveSpeed = 0.5f, s32 id=-1,
			SKeyMap* keyMapArray=0, s32 keyMapSize=0, bool noVerticalMovement=false,
			f32 jumpSpeed = 0.f, bool invertMouse=false,
			bool makeActive=true);
		IrrGameObject *addCameraBoardGame(Vector*,Vector*,Vector*,Vector*);
		IrrGameObject *addAudio(const char *,int,Vector*);

		ILightSceneNode * addLightSceneNode(const core::vector3df& position = core::vector3df(0,0,0),
			video::SColorf color = video::SColorf(1.0f, 1.0f, 1.0f),
			f32 radius=100.0f);

		ILightSceneNode * addLightSceneNode(ISceneNode* parent = 0, s32 id=-1, const core::vector3df& position = core::vector3df(0,0,0),
			video::SColorf color = video::SColorf(1.0f, 1.0f, 1.0f),
			f32 radius=100.0f);

		//Particula
		IrrParticleSystem * addParticleSystem();
		void removeParticleSystem(IrrParticleSystem * ps);

		//construtora
		IrrScene(IrrlichtDevice *,ISoundEngine *,IrrInput *);
		~IrrScene(void);

		//para definir a camera padr�o
		void setCamera(IrrCamera * camera);

		//para definir a camera padr�o
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
