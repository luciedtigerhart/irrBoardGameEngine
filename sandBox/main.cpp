#include <string>
#include <iostream>
#include <list>
#include <list>

#include "IrrEngine.h"
#include "TokenNoob.h"
#include "TokenDummy.h"
#include "TileComum.h"

using namespace IrrBoardGameEngine;

// Define some values that we'll use to identify individual GUI controls.
enum
{
    GUI_ID_TEXT_01 = 101,
    GUI_ID_TEXT_02,
    GUI_ID_TEXT_03,
    GUI_ID_BUTTON,
	GUI_ID_BUTTON_02
};

IrrEngine * engine;
IrrScene * cena;
IrrBoard * board;

IrrGUI * fgui;
IrrGameObject * audio;

void myLoop()
{
	if(engine->getInput()->isKeyDown(KEY_SPACE))
	{
		fgui->fadeIn(5000);
		audio->getAudio()->stop();
	}
	/*
	std::cout << fgui->isReadyfade();
	
	if(fgui->isReadyfade())
	{
		fgui->fade(5000,true);
	}
	*/

	if(fgui->isPressedButton(GUI_ID_BUTTON_02))
	{
		fgui->fadeOut(5000);
		audio->getAudio()->setLoopingStreamMode();
	}
}

int main()
{
	engine = IrrEngine::getInstance(video::EDT_OPENGL, dimension2d<u32>(1024, 768), 16, false, false, false,L"Jogo Dummy");
    
	cena = engine->getScene();

	IrrGameObject *cam = cena->addCameraDefault(new Vector(20.0f, 20.0f, 20.0f),new Vector(0.0f, 0.0f, 1.0f));
	cam->setName("Camera principal");

	board = cena->addStaticBoard("boards/board-01.txt",new Vector(0.0f, 1.0f, 0.0f));
	//board = cena->addAnimatedBoard("boards/board-01.txt",new Vector(0.0f, 1.0f, 0.0f));

	cena->addLightSceneNode(vector3df(0,5,-20), SColorf(1.0f,1.0f,1.0f,1.0f), 30.0f);

	//
	// CONFIGURA TILES
	//

	std::list<IrrTile*> * list_tiles = board->getAllTiles();
	std::list<IrrTile*>::iterator i;
	for(i=list_tiles->begin(); i!=list_tiles->end(); i++)
	{
		board->addTileBehavior((*i), new TileComum());
	}

	//
	// CONFIGURA TOKENS
	//

	std::list<IrrToken*>::iterator t;

	std::list<IrrToken*> * list_token_player_one = board->createTokens(1);
	for(t=list_token_player_one->begin(); t!=list_token_player_one->end(); t++)
	{
		board->addTokenBehavior((*t), new TokenNoob());
	}
	
	std::list<IrrToken*> * list_token_player_two = board->createTokens(2);
	for(t=list_token_player_two->begin(); t!=list_token_player_two->end(); t++)
	{
		board->addTokenBehavior((*t), new TokenDummy());
	}

	//
	//
	//

	IrrParticleSystem * ps = cena->addParticleSystem();

	IParticleEmitter * em = ps->createBoxEmitter(2,core::aabbox3d<f32>(-2,0,-2,2,1,2), // emitter size
                core::vector3df(0.0f,0.06f,0.0f),   // initial direction
                20,30,                              // emit rate
                video::SColor(0,255,255,255),       // darkest color
                video::SColor(0,255,255,255),       // brightest color
                100,260,25,                         // min and max age, angle
                core::dimension2df(1.f,1.f),        // min size
                core::dimension2df(2.f,2.f));       // max size

	//ps->setPosition(new Vector(0.0f,0.0f,0.0f));
	//ps->setScale(new Vector(-3,-3,-3));
	ps->setMaterialFlag(video::EMF_LIGHTING, false);
	ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, true);
	ps->setMaterialTexture(0,"texturas/blue.jpg");
	ps->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);

	ps->addFadeOutAffector(0);

	/*
	IrrScene *scene_dois = engine->createScene();

	scene_dois->addCube(new Vector(0.0f, 0.0f, 0.0f));

	IrrGameObject *cam_dois = scene->addCamera(new Vector(2.0f, 20.0f, 20.0f),new Vector(0.0f, 0.0f, 0.0f));

	engine->setCurrentScene(scene_dois);
	*/

	/*
	if(board->moveToken(0,3,5,2))
	{
		cout << "aa";
	}
	else
	{
		cout << "nao";
	}
	*/

	//
	// CONSTRUÇÃO DO GUI
	//
	fgui = engine->getGUI();

	fgui->addLabel(GUI_ID_TEXT_01,"meu texto meu texto meu texto meu texto meu texto",0,0,50,80);

	fgui->addLabel(GUI_ID_TEXT_02,"sdfsdf sdfs df",50,0,100,80);

	fgui->addLabel(GUI_ID_TEXT_03,"m450s45d4f05sd40f5sdfexto",100,0,150,80);

	fgui->addButton(GUI_ID_BUTTON,"gui/botao-off.png","gui/botao-on.png","gui/botao-off-click.png","gui/botao-on-click.png",30,60, true);

	fgui->addButton(GUI_ID_BUTTON_02,"gui/botao-off.png","gui/botao-on.png","gui/botao-off-click.png","gui/botao-on-click.png",30,290);

	//
	// FADE
	//
	fgui->fadeIn(2000);


	//
	// AUDIO
	//
	audio = cena->addAudio("sound/sfx_special_unitDie_trapTroll.wav",12,new Vector(0.0f, 0.0f, 0.0f));
	//setPlayOnceMode > toca uma vez
	//setLoopingStreamMode > loca em loop

	//
	/*
	IrrGUI * gui_dois = engine->createGUI();

	gui_dois->addLabel("mostro","mostro texto meu mostro meu mostro meu mostro meu mostro",0,0,50,80);

	engine->setCurrentGUI(gui_dois);
	*/

	engine->loop(myLoop);

	delete cena;
	delete engine;
	delete fgui;
	delete cam;
	

	return 0;
}