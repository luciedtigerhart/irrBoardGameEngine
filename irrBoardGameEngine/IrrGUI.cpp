#include <iostream>

#include "IrrGUI.h"

using namespace IrrBoardGameEngine;

IrrGUI::IrrGUI(IrrlichtDevice * device)
{	
	driver = device->getVideoDriver();
	guienv = device->getGUIEnvironment();

	irr::core::dimension2d<u32> d = driver->getScreenSize();
	//rootGUI = new IGUIElement(EGUIET_WINDOW,guienv,0,-1,rect<s32>(0, 0, 50, 50)); //guienv->addGUIElement(irr::gui::EGUI_ELEMENT_TYPE.EGUIET_ELEMENT);
	//rootGUI = guienv->addModalScreen(guienv->getRootGUIElement
	//rootGUI = guienv->addImage(rect<s32>(0, 0, d.Width, d.Height));
	rootGUI = guienv->addStaticText(L"",rect<s32>(0, 0, d.Width, d.Height));
	fader = NULL;
	isfadein = false;
}

IrrGUI::~IrrGUI(void)
{

}

void IrrGUI::addLabel(s32 id, char *text, int minX, int minY, int maxX, int maxY)
{
    std::string other(text);
    const std::wstring& ws =  std::wstring(other.begin(), other.end());
        
    labels.insert(pair<s32, IGUIStaticText*>(id,guienv->addStaticText(ws.c_str(), rect<s32>(minX, minY, maxX, maxY), false, true, rootGUI,id)));	
}

void IrrGUI::setText(s32 id, char *text) {
    // Converte char para wchar_t
    std::string other(text);
    const std::wstring& ws =  std::wstring(other.begin(), other.end());

    std::map<s32, IGUIStaticText*>::iterator it = labels.find(id);
    if(it != labels.end())
		(*it).second->setText(ws.c_str());
}

void IrrGUI::setLabel(s32 id, bool visible) {
    std::map<s32, IGUIStaticText*>::iterator it = labels.find(id);
    if(it != labels.end())
		(*it).second->setVisible(visible);
}

bool IrrGUI::getLabel(s32 id) {
    std::map<s32, IGUIStaticText*>::iterator it = labels.find(id);
    if(it != labels.end())
		return (*it).second->isVisible();

    return false;
}

void IrrGUI::removeLabel(s32 id) {
    std::map<s32, IGUIStaticText*>::iterator it = labels.find(id);
    if(it != labels.end())
		(*it).second->remove();
}

void IrrGUI::addImage(s32 id, char* file, int x, int y) {
	imagens.insert(pair<s32, IGUIImage*>(id,guienv->addImage(driver->getTexture(file),position2d<int>(x, y),true,rootGUI,id)));
}

void IrrGUI::setImage(s32 id, bool visible) {
    std::map<s32, IGUIImage*>::iterator it = imagens.find(id);
    if(it != imagens.end())
		(*it).second->setVisible(visible);
}

bool IrrGUI::getImage(s32 id) {
    std::map<s32, IGUIImage*>::iterator it = imagens.find(id);
    if(it != imagens.end())
		return (*it).second->isVisible();

    return false;
}

void IrrGUI::removeImage(s32 id) {
    std::map<s32, IGUIImage*>::iterator it = imagens.find(id);
    if(it != imagens.end())
		(*it).second->remove();
}

void IrrGUI::addButton(s32 id, char* fileNormal, char* fileHover, char* filePressed, char* filePressedHover, int x, int y, bool toggle, char* fileDisabled) {
	IrrGUIButton* bt = new IrrGUIButton(guienv,driver,id,x,y,rootGUI,toggle);
	
	bt->addImage(fileNormal);
	bt->addImageHover(fileHover);
	bt->addImagePressed(filePressed);
	bt->addImagePressedHover(filePressedHover);
	if(fileDisabled != NULL) bt->addImageDisabled(fileDisabled);

	buttons.insert(pair<s32, IrrGUIButton*>(id,bt));
}

void IrrGUI::setButton(s32 id, bool visible) {
    std::map<s32, IrrGUIButton*>::iterator it = buttons.find(id);
    if(it != buttons.end())
		(*it).second->setVisible(visible);
}

void IrrGUI::removeButton(s32 id) {
	/*
    std::map<s32, IrrGUIButton*>::iterator it = buttons.find(id);
    if(it != buttons.end())
		(*it).second->remove();
	*/
}

void IrrGUI::update()
{
	/*
	std::map<s32, EState>::iterator it = elementState.begin();
    while(it != elementState.end())
	{		
		if((*it).second.clicked)
		{
			std::cout << "elemento clicado";
		}
		it++;
	}
	*/
}

void IrrGUI::setMouseOver(s32 id, bool value)
{
	std::map<s32, IrrGUIButton*>::iterator it = buttons.find(id);
    if(it != buttons.end())
		(*it).second->setHover(value);
}

bool IrrGUI::isMouseOver(s32 id)
{
	std::map<s32, IrrGUIButton*>::iterator it = buttons.find(id);
    if(it != buttons.end())
	{
		return (*it).second->isHover();
	}
	else
	{
		return false;
	}
}

void IrrGUI::setPressedButton(s32 id, bool value)
{
	std::map<s32, IrrGUIButton*>::iterator it = buttons.find(id);
    if(it != buttons.end())
	{
		(*it).second->setPressed(value);
	}
}

void IrrGUI::setPressedButton(bool value)
{
	std::map<s32, IrrGUIButton*>::iterator it = buttons.begin();
    while(it != buttons.end())
	{
		(*it).second->setPressed(value);
		it++;
	}
}

bool IrrGUI::isPressedButton(s32 id)
{
	std::map<s32, IrrGUIButton*>::iterator it = buttons.find(id);
    if(it != buttons.end())
	{
		return (*it).second->isPressed();
	}
	else
	{
		return false;
	}
}

void IrrGUI::setDisabledButton(s32 id, bool value)
{
	std::map<s32, IrrGUIButton*>::iterator it = buttons.find(id);
    if(it != buttons.end())
	{
		(*it).second->setDisabled(value);
	}
}

bool IrrGUI::isDisabledButton(s32 id)
{
	std::map<s32, IrrGUIButton*>::iterator it = buttons.find(id);
    if(it != buttons.end())
	{
		return (*it).second->isDisabled();
	}
	else
	{
		return false;
	}
}

void IrrGUI::setActive(bool flag)
{
	rootGUI->setVisible(flag);
}

IGUIEnvironment * IrrGUI::getGUIenv()
{
	return guienv;
}

void IrrGUI::drawAll()
{
	guienv->drawAll();

	if(fader != NULL && isfadein && fader->isReady())
	{
		fader->setVisible(false);
	}
}

void IrrGUI::fadeIn(u32 time)
{
	fade(time,true);
}

void IrrGUI::fadeOut(u32 time)
{
	fade(time,false);
}

void IrrGUI::fade(u32 time, bool in)
{
	if(fader == NULL) fader = guienv->addInOutFader(0,rootGUI);
	fader->setVisible(true);
	if(in)
	{
		fader->fadeIn(time);
		isfadein = true;
	}
	else
	{
		isfadein = false;
		fader->fadeOut(time);
	}
}

bool IrrGUI::isReadyfade()
{
	if(fader != NULL)
		return fader->isReady();
	else
		return false;
}