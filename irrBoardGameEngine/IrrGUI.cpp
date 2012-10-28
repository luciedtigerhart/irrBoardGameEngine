#include <iostream>

#include "IrrGUI.h"

using namespace IrrBoardGameEngine;

IrrGUI::IrrGUI(IrrlichtDevice * device)
{	
	driver = device->getVideoDriver();
	guienv = device->getGUIEnvironment();

	//rootGUI = new IGUIElement(EGUIET_WINDOW,guienv,0,-1,rect<s32>(0, 0, 50, 50)); //guienv->addGUIElement(irr::gui::EGUI_ELEMENT_TYPE.EGUIET_ELEMENT);
	//rootGUI = guienv->addModalScreen(guienv->getRootGUIElement());
	rootGUI = guienv->addStaticText(L"",rect<s32>(0, 0, 800, 600));
}

IrrGUI::~IrrGUI(void)
{

}

void IrrGUI::addLabel(s32 id, char *text, int minX, int minY, int maxX, int maxY)
{
    std::string other(text);
    const std::wstring& ws =  std::wstring(other.begin(), other.end());
        
    labels.insert(pair<s32, IGUIStaticText*>(id,guienv->addStaticText(ws.c_str(), rect<s32>(minX, minY, maxX, maxY), false, true, rootGUI,id)));
	elementState.insert(pair<s32, EState>(id,EState()));
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
	elementState.insert(pair<s32, EState>(id,EState()));
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

void IrrGUI::addButton(s32 id, char* fileNormal, char* filePressed, int x, int y, int w, int h) {
	//imagens.insert(pair<std::string, IGUIImage*>(std::string(name),guienv->addImage(driver->getTexture(file),position2d<int>(x, y),true)));
	IGUIButton* bt = guienv->addButton(rect<s32>(x, y, x+w, y+h),rootGUI,id);

	bt->setImage(driver->getTexture(fileNormal),rect<s32>(0, 0, w, h));
	bt->setPressedImage(driver->getTexture(filePressed),rect<s32>(0, 0, w, h));

	buttons.insert(pair<s32, IGUIButton*>(id,bt));
	elementState.insert(pair<s32, EState>(id,EState()));
}

void IrrGUI::setButton(s32 id, bool visible) {
    std::map<s32, IGUIButton*>::iterator it = buttons.find(id);
    if(it != buttons.end())
		(*it).second->setVisible(visible);
}

void IrrGUI::removeButton(s32 id) {
    std::map<s32, IGUIButton*>::iterator it = buttons.find(id);
    if(it != buttons.end())
		(*it).second->remove();
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
	std::map<s32, EState>::iterator it = elementState.find(id);
    if(it != elementState.end())
		(*it).second.mouseOver = value;
}

void IrrGUI::resetPressed()
{
	std::map<s32, EState>::iterator it = elementState.begin();
    while(it != elementState.end())
	{		
		(*it).second.clicked = false;
		it++;
	}
}

void IrrGUI::setButtonPressed(s32 id, bool value)
{
	std::map<s32, EState>::iterator it = elementState.find(id);
    if(it != elementState.end())
	{
		(*it).second.clicked = value;
	}
}

EState IrrGUI::getElementState(s32 id)
{
	std::map<s32, EState>::iterator it = elementState.find(id);
    if(it != elementState.end())
	{
		return (*it).second;
	}
	else
	{
		return EState();
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
}

