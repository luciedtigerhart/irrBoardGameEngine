#pragma once

#include "irrlicht.h"
#include "irrKlang.h"
#include "IrrGameObject.h"
#include "IrrTile.h"
#include "IrrBoard.h"
#include "IrrLoader.h"
#include "IrrMesh.h"
#include "IrrCamera.h"
#include "Vector.h"
#include <stack>
#include <string>
#include <vector>

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
		ISoundEngine *soundEngine;

		vector<IrrGameObject*> *objects;
		stack<IrrGameObject*> newObjects;

	protected:
		void addObject(IrrGameObject*);

	public:
		void update();
		IrrGameObject *addCube(Vector*);
		IrrGameObject *addSphere(Vector*);
		IrrGameObject *addAnimatedMesh(char *,Vector*);
		IrrGameObject *addMesh(char *,Vector*);
		IrrBoard *addBoard(std::string src,Vector*);
		IrrGameObject *addCamera(Vector*,Vector*);
		IrrGameObject *addAudio(const char *,int,Vector*);

		IrrScene(ISceneManager *,ISoundEngine *);
		~IrrScene(void);
	};
}