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
#include "IrrAudio.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace std;

//
// Objeto padrão da cena
//

namespace IrrBoardGameEngine {
	class IrrGameObject
	{
	public:
		IrrGameObject(void);
		~IrrGameObject(void);

		IrrInput * s;

		//
		// Controle de posicionamento
		//
		void setPosition(Vector&);
		void setScale(Vector&);
		void setRotation(Vector&);		
		void getPosition(Vector&);
		void translate(float x, float y, float z);

		//
		// Configura um nome para o objeto
		//
		void setName(std::string*);
		void setName(const char*s){name = new std::string(s);}
		std::string *getName();

		//
		// Confugura uma camera
		//
		void setCamera(IrrCamera *);
		IrrCamera* getCamera(); 

		//
		// Configura um mesh para o obejto
		//
		void setMesh(IrrMesh *);
		IrrMesh* getMesh();

		//
		// Configura um mesh animado para o objeto
		//
		void setAnimatedMesh(IrrMeshAnimated *);
		IrrMeshAnimated* getAnimatedMesh();

		//
		// Configura um audio
		//
		void setAudio(IrrAudio *);
		IrrAudio *getAudio();
		void play();

		//
		// Adiciona um objeto filho
		//
		void addChild(IrrGameObject *o);
		void removeChild(IrrGameObject *o);
		IrrGameObject *getChild(int);
		int getSize();

		//
		// Configura se o objeto está ativo
		//
		void setActive(bool a);	
		bool isActive();

		virtual void update();

		//
		// Adiciona um comportamento ao objeto
		//
		void addBehaviour(IrrBehavior *b);
		IrrBehavior * getBehavior(int index);


		//
		// operador de <=
		//
		int operator<=(const IrrGameObject &) const;


		//
		// variavel responsavel do objeto no nodo da cena
		//
		ISceneNode *node;

	protected:
		std::string *name;
		IrrCamera *camera;
		IrrMesh *mesh;
		IrrMeshAnimated *ani_mesh;
		IrrAudio *audio;
		
		vector<IrrBehavior*> *behaviors;
		std::map<IrrGameObject*,ISceneNode*> *children;
	};
}