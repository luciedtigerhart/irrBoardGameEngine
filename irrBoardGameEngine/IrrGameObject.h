#pragma once

#include <map>

#include "irrlicht.h"
#include <string>
#include <vector>

#include "Vector.h"
#include "IrrCamera.h"
#include "IrrMesh.h"
//#include "IrrBehavior.h"
//#include "IrrAnimation.h"
//#include "IrrAudio.h"

using namespace irr;
using namespace scene;
using namespace core;
using namespace std;

namespace IrrBoardGameEngine {
	class IrrGameObject
	{
	public:
		IrrGameObject(void);
		~IrrGameObject(void);

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

		void update();
		//void addBehaviour(Behavior *);

		void translate(float x, float y, float z);
		void play();

		int operator<=(const IrrGameObject &) const;

		ISceneNode *node;
	protected:
		std::string *name;
		IrrCamera *camera;
		IrrMesh *mesh;

		/*
		Animation *animation;
		Audio *audio;
		*/
		//vector<Behavior*> *behaviors;
		std::map<IrrGameObject*,ISceneNode*> *children;
	};
}