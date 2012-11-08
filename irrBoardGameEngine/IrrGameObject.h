#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "irrlicht.h"
#include "irrKlang.h"
#include <map>
#include <string>
#include <vector>

#include "Vector.h"
#include "IrrCamera.h"
#include "IrrMesh.h"
#include "IrrMeshAnimated.h"
#include "IrrBehavior.h"

//#include "IrrAnimation.h"
//#include "IrrAudio.h"


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace std;

namespace IrrBoardGameEngine {
	class IrrGameObject
	{
	public:
		IrrGameObject(void);
		~IrrGameObject(void);

		IrrInput * s;

		void setPosition(Vector&);
		void setScale(Vector&);
		void setRotation(Vector&);		
		void getPosition(Vector&);

		void setName(std::string*);
		void setName(const char*s){name = new std::string(s);}
		std::string *getName();

		void setCamera(IrrCamera *);
		IrrCamera* getCamera(); 

		void setMesh(IrrMesh *);
		IrrMesh* getMesh();

		void setAnimatedMesh(IrrMeshAnimated *);
		IrrMeshAnimated* getAnimatedMesh();

		/*
		void setAnimation(Animation *);
		IrrAnimation* getAnimation();
		
		void setAudio(Audio *);
		IrrAudio *getAudio();
		*/

		void addChild(IrrGameObject *o);
		void removeChild(IrrGameObject *o);
		IrrGameObject *getChild(int);
		int getSize();

		void setActive(bool a);	
		bool isActive();

		virtual void update();
		void addBehaviour(IrrBehavior *b);

		void translate(float x, float y, float z);
		void play();

		int operator<=(const IrrGameObject &) const;

		ISceneNode *node;

		IrrBehavior * getBehavior(int index);
	protected:
		std::string *name;
		IrrCamera *camera;
		IrrMesh *mesh;
		IrrMeshAnimated *ani_mesh;

		/*
		Animation *animation;
		Audio *audio;
		*/

		vector<IrrBehavior*> *behaviors;
		std::map<IrrGameObject*,ISceneNode*> *children;
	};
}