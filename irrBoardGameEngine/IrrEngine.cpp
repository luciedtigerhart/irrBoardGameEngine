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
//IrrEngine *IrrEngine::getInstance(video::E_DRIVER_TYPE deviceType = video::EDT_SOFTWARE,const core::dimension2d<u32>& windowSize = (core::dimension2d<u32>(640,480)),u32 bits = 16,bool fullscreen = false,bool stencilbuffer = false,bool vsync = false)
IrrEngine *IrrEngine::getInstance(video::E_DRIVER_TYPE deviceType,const core::dimension2d<u32>& windowSize,u32 bits,bool fullscreen,bool stencilbuffer,bool vsync,const wchar_t* text)
{
	if(IrrEngine::instance==NULL){
		IrrEngine::instance = new IrrEngine();
		IrrEngine::instance->init(deviceType,windowSize,bits,fullscreen,stencilbuffer,vsync,text);
	}
	return IrrEngine::instance;
}

//int IrrEngine::init(video::E_DRIVER_TYPE deviceType = video::EDT_SOFTWARE,const core::dimension2d<u32>& windowSize = (core::dimension2d<u32>(640,480)),u32 bits = 16,bool fullscreen = false,bool stencilbuffer = false,bool vsync = false) {
int IrrEngine::init(video::E_DRIVER_TYPE deviceType,const core::dimension2d<u32>& windowSize,u32 bits,bool fullscreen,bool stencilbuffer,bool vsync,const wchar_t* text)
{
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
	device = createDevice(deviceType,windowSize,bits,fullscreen,stencilbuffer,vsync,input);
	//Se nao conseguiu retornar encerra a aplicação
    if (!device) return 1;

	//Titulo na janela
	device->setWindowCaption(text);

	//device->getCursorControl()->setVisible(true);

	//Pegar o driver de video
	driver = device->getVideoDriver();

	guienv = device->getGUIEnvironment();

	smgr = device->getSceneManager();

	return 0;
}

void IrrEngine::loop()
{
	this->loop(this->currentScene,this->currentGUI);
}

void IrrEngine::loop(IrrGUI * gui)
{
	this->loop(this->currentScene,gui);
}

void IrrEngine::loop(IrrScene * scene, IrrGUI * gui) {
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

		//atualiza a gui
		gui->update();

		//Limpa a cena com uma cor
		driver->beginScene(true, true, SColor(255,100,101,140));
			
		//Grafo de cena renderiza
		smgr->drawAll();

		//Gerenciador da GUI renderiza
		guienv->drawAll();

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
	return new IrrScene(smgr,soundEngine,input);
}

IrrScene *IrrEngine::getScene()
{
	return currentScene;
}

void IrrEngine::setCurrentScene(IrrScene *s)
{
	this->currentScene = s;
}

float IrrEngine::getDeltaTime()
{
	return (float)frameDeltaTime;
}

void IrrEngine::setCurrentGUI(IrrGUI * gui)
{
	currentGUI = gui;
}

IrrGUI *IrrEngine::createGUI()
{
	return new IrrGUI();
}

IrrGUI *IrrEngine::getGUI()
{
	return currentGUI;
}

IrrInput *IrrEngine::getInput()
{
	return input;
}

IrrlichtDevice *IrrEngine::getDevice()
{
	return device;
}

IVideoDriver *IrrEngine::getDriver()
{
	return driver;
}

ISceneManager *IrrEngine::getSceneManager()
{
	return smgr;
}

IGUIEnvironment *IrrEngine::getGUIenv()
{
	return guienv;
}

ISoundEngine *IrrEngine::getSoundEngine()
{
	return soundEngine;
}