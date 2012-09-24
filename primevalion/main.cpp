#include <string>
#include <iostream>

#include "IrrEngine.h"

using namespace IrrBoardGameEngine;

int main() {
	//1. Pegar a referencia para o motor
	IrrEngine *engine = IrrEngine::GetInstance();
	
	//2. Registrar as teclas de comandos
	/*
	Input::registry("MoveUp",irr::KEY_KEY_W);
	Input::registry("MoveDown",irr::KEY_KEY_S);
	Input::registry("MoveRight",irr::KEY_KEY_D);
	Input::registry("MoveLeft",irr::KEY_KEY_A);
	Input::registry("Fire",irr::KEY_SPACE);
	*/
        
	//3. Cria um nova cena vazia
	IrrScene *scene = engine->createScene();
	engine->setCurrentScene(scene);

	//4. Adiciona-se objetos na cena
	IrrGameObject *cam = scene->addCamera(new Vector(0.0f, -50.0f, 0.0f),new Vector(0.0f, 0.0f, 0.0f));
	cam->setName("Camera principal");
	
	//IrrGameObject *perso = scene->addMesh("media/carinha.obj",new Vector(0.0f, 0.0f, 0.0f));
	IrrGameObject * cube = scene->addCube(new Vector(0.0f, 0.0f, 0.0f));
	//perso->addBehaviour(new Personagem());

	//GameObject *a = scene->addAudio("media/bell.wav",101,new Vector(10,0,0));
	//cube->addChild(a);
	//cube->addBehaviour(new MyBehavior());
	//cube->setActive(false);
        
		
	//6. Coloca-se a engine a funcionar!
	engine->loop();

	//7. Ao encerrar deleta cena e o motor
	delete scene;
	delete engine;

	return 0;
} 