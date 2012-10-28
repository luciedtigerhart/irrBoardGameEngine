#include "IrrGUI.h"

using namespace IrrBoardGameEngine;

IrrGUI::IrrGUI(IrrlichtDevice * device, IrrInput * irrinput)
{	
	driver = device->getVideoDriver();
	guienv = device->getGUIEnvironment();
	input = irrinput;

	//rootGUI = new IGUIElement(EGUIET_WINDOW,guienv,0,-1,rect<s32>(0, 0, 50, 50)); //guienv->addGUIElement(irr::gui::EGUI_ELEMENT_TYPE.EGUIET_ELEMENT);
	//rootGUI = guienv->addModalScreen(guienv->getRootGUIElement());
	rootGUI = guienv->addStaticText(L"",rect<s32>(0, 0, 50, 50));
}

IrrGUI::~IrrGUI(void)
{

}

void IrrGUI::addLabel(char *name, char *text, int minX, int minY, int maxX, int maxY)
{
    std::string other(text);
    const std::wstring& ws =  std::wstring(other.begin(), other.end());
        
    labels.insert(pair<std::string, IGUIStaticText*>(std::string(name),guienv->addStaticText(ws.c_str(), rect<s32>(minX, minY, maxX, maxY), false, true, rootGUI)));
}

void IrrGUI::setText(char *nome, char *text) {
    // Converte char para wchar_t
    std::string other(text);
    const std::wstring& ws =  std::wstring(other.begin(), other.end());

    std::map<std::string, IGUIStaticText*>::iterator it = labels.find(std::string(nome));
    if(it != labels.end())
		(*it).second->setText(ws.c_str());
}

void IrrGUI::setLabel(char *nome, bool visible) {
    std::map<std::string, IGUIStaticText*>::iterator it = labels.find(std::string(nome));
    if(it != labels.end())
		(*it).second->setVisible(visible);
}

bool IrrGUI::getLabel(char *nome) {
    std::map<std::string, IGUIStaticText*>::iterator it = labels.find(std::string(nome));
    if(it != labels.end())
		return (*it).second->isVisible();

    return false;
}

void IrrGUI::removeLabel(char *nome) {
    std::map<std::string, IGUIStaticText*>::iterator it = labels.find(std::string(nome));
    if(it != labels.end())
		(*it).second->remove();
}

void IrrGUI::addImage(char* name, char* file, int x, int y) {
	imagens.insert(pair<std::string, IGUIImage*>(std::string(name),guienv->addImage(driver->getTexture(file),position2d<int>(x, y),true,rootGUI)));
}

void IrrGUI::setImage(char *nome, bool visible) {
    std::map<std::string, IGUIImage*>::iterator it = imagens.find(std::string(nome));
    if(it != imagens.end())
		(*it).second->setVisible(visible);
}

bool IrrGUI::getImage(char *nome) {
    std::map<std::string, IGUIImage*>::iterator it = imagens.find(std::string(nome));
    if(it != imagens.end())
		return (*it).second->isVisible();

    return false;
}

void IrrGUI::removeImage(char *nome) {
    std::map<std::string, IGUIImage*>::iterator it = imagens.find(std::string(nome));
    if(it != imagens.end())
		(*it).second->remove();
}

void IrrGUI::addButton(char *name, char* fileNormal, char* filePressed, int x, int y, int w, int h) {
	//imagens.insert(pair<std::string, IGUIImage*>(std::string(name),guienv->addImage(driver->getTexture(file),position2d<int>(x, y),true)));
	IGUIButton* bt = guienv->addButton(rect<s32>(x, y, x+w, y+h),rootGUI);

	bt->setImage(driver->getTexture(fileNormal),rect<s32>(0, 0, w, h));
	bt->setPressedImage(driver->getTexture(filePressed),rect<s32>(0, 0, w, h));
	buttons.insert(pair<std::string, IGUIButton*>(std::string(name),bt));
}

void IrrGUI::setButton(char *nome, bool visible) {
    std::map<std::string, IGUIButton*>::iterator it = buttons.find(std::string(nome));
    if(it != buttons.end())
		(*it).second->setVisible(visible);
}

void IrrGUI::removeButton(char *nome) {
    std::map<std::string, IGUIButton*>::iterator it = buttons.find(std::string(nome));
    if(it != buttons.end())
		(*it).second->remove();
}

void IrrGUI::update()
{

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