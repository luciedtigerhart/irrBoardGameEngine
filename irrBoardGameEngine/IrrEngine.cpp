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

	input->setDriver(driver);
	input->setDevice(device);

	//
	// GUI
	//
	//guienv = device->getGUIEnvironment();
	currentGUI = createGUI();
	input->setGUI(currentGUI);
	currentGUI->setActive(true);

	driver->getMaterial2D().TextureLayer[0].BilinearFilter=true;
	driver->getMaterial2D().AntiAliasing=video::EAAM_FULL_BASIC;

	//
	// SCENE
	//
	//smgr = device->getSceneManager();
	currentScene = createScene();
	currentScene->setActive(true);

	return 0;
}

bool IrrEngine::run()
{
	bool isrun = device->run();
	
	//Limpa a cena com uma cor
	driver->beginScene(true, true, SColor(255,100,101,140));

	return isrun;
}

void IrrEngine::update()
{
	//Atualiza a cena
	currentScene->update();

	//atualiza a gui
	currentGUI->update();

	//Atualiza o input
	input->update();
}

void IrrEngine::draw()
{
	//Grafo de cena renderiza
	currentScene->drawAll();

	//Gerenciador da GUI renderiza
	currentGUI->drawAll();

	//Exibe o resultado na tela
	driver->endScene();
}

void IrrEngine::loop(void(*f)()) {
	// Qual foi a ultima fatia de tempo
	u32 then = device->getTimer()->getTime();
	int lastFPS = -1;
	
	//Game loop
	while(run())
	{
		//Pega a fatia de tempo atual
		const u32 now = device->getTimer()->getTime();
		//Pega a variacao do tempo
		frameDeltaTime = (f32)(now - then) / 1000.f; //Tempo em segundos
		//Define o tempo passado com o atual
		then = now;

		/*
		vector3df pos(0.0f, 0.0f, 0.0f);
		SMaterial m;
		m.setTexture(0,0);
		m.Lighting=false; 
		driver->setMaterial(m); 
		driver->setTransform(video::ETS_WORLD, core::matrix4()); 

		//y
		driver->draw3DLine(pos,vector3df(0,10,0),SColor(255,255,0,0));

		//x
		driver->draw3DLine(pos,vector3df(10,0,0),SColor(255,0,255,0)); 

		//z
		driver->draw3DLine(pos,vector3df(0,0,10),SColor(255,0,0,255)); 
		*/
		update();
		
		//Função do usuario
		(*f)();

		draw();

		//Pega o FPS
		int fps = driver->getFPS();
		//Se mudou ...
		if (lastFPS != fps)
		{					
			lastFPS = fps;
		}
	}
	
	//Encerra. Deleta todos os objetos
	device->drop();
}

IrrScene *IrrEngine::createScene()
{
	IrrScene * newScene = new IrrScene(device, soundEngine, input);
	newScene->setActive(false);
	return newScene;
}

IrrScene *IrrEngine::getScene()
{
	return currentScene;
}

void IrrEngine::setCurrentScene(IrrScene *s)
{
	this->currentScene->setActive(false);
	this->currentScene = s;
	this->currentScene->setActive(true);
}

float IrrEngine::getDeltaTime()
{
	return (float)frameDeltaTime;
}

IrrGUI *IrrEngine::createGUI()
{
	IrrGUI * newGUI = new IrrGUI(device);
	newGUI->setActive(false);
	return newGUI;
}

void IrrEngine::setCurrentGUI(IrrGUI * gui)
{
	currentGUI->setActive(false);
	currentGUI = gui;
	input->setGUI(currentGUI);
	currentGUI->setActive(true);
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
	return currentScene->getSceneManager();
}

IGUIEnvironment *IrrEngine::getGUIenv()
{
	return currentGUI->getGUIenv();
}

ISoundEngine *IrrEngine::getSoundEngine()
{
	return soundEngine;
}