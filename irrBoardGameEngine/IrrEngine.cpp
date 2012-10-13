#include "irrEngine.h"

using namespace IrrBoardGameEngine;

IrrEngine *IrrEngine::instance = 0;

IrrEngine::IrrEngine(void)
{

}

IrrEngine::~IrrEngine(void)
{
}


//singleton
IrrEngine *IrrEngine::GetInstance()
{
	if(IrrEngine::instance==NULL){
		IrrEngine::instance = new IrrEngine();
		IrrEngine::instance->init();
	}
	return IrrEngine::instance;
}
int IrrEngine::init() {
	//irrklang::ISoundEngine* soundEngine = irrklang::createIrrKlangDevice();
	soundEngine = createIrrKlangDevice();
	
	input = new IrrInput();
	//Cria um novo dispositivo
	//qual o driver - no caso esta usando via software mesmo
	//tamanho da janela - 640x480
	//deep color
	//fullscren?
	//usa stencil buffer?
	//se utiliza vsync
	//o endereço objeto para receber os eventos. No caso o default é 0
	device = createDevice( video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16, false, false, false, input);
	//Se nao conseguiu retornar encerra a aplicação
    if (!device) return 1;

	//Titulo na janela
	device->setWindowCaption(L"IrrBGE");

	//Pegar o driver de video
	driver = device->getVideoDriver();

	smgr = device->getSceneManager();

	return 0;
}

void IrrEngine::loop()
{
	this->loop(this->currentScene);
}

void IrrEngine::loop(IrrScene *scene) {
	// Qual foi a ultima fatia de tempo
	u32 then = device->getTimer()->getTime();
	int lastFPS = -1;
	
	//Game loop
	while(device->run())
	{
		
		//Pega a fatia de tempo atual
		const u32 now = device->getTimer()->getTime();
		//Pega a variacao do tempo
		frameDeltaTime = (f32)(now - then) / 1000.f; //Tempo em segundos
		//Define o tempo passado com o atual
		then = now;
		
		//Atualiza a cena			
		scene->update();

		//Limpa a cena com uma cor
		driver->beginScene(true, true, SColor(255,100,101,140));
			
		//Grafo de cena renderiza
		smgr->drawAll();


		//Gerenciador da GUI renderiza
		//guienv->drawAll();
		//Exibe o resultado na tela
		driver->endScene();

		//Pega o FPS
		int fps = driver->getFPS();
		//Se mudou ...
		if (lastFPS != fps)
		{					
			lastFPS = fps;
		}

		//Atualiza o input
		input->update();
	}
	
	//Encerra. Deleta todos os objetos
	device->drop();
}

IrrScene *IrrEngine::createScene()
{
	return new IrrScene(smgr,soundEngine);
}

IrrScene *IrrEngine::getScene() {
	return currentScene;
}

void IrrEngine::setCurrentScene(IrrScene *s)
{
	this->currentScene = s;
}

float IrrEngine::getDeltaTime() {
	return (float)frameDeltaTime;
}