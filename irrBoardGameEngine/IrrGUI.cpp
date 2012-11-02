#include <iostream>

#include "IrrGUI.h"

using namespace IrrBoardGameEngine;

/*

há fazer:::

Pelo menos em teoria é bem simples: vamos supor que temos a imagem de hover para quando o botão está em estado normal, 
que chamamos "ImageHoverNormal". Também temos uma imagem de hover para quando o botão está em estado "pressed", 
que vamos chamar de "ImageHoverPressed". Ambas essas imagens tem que ser um ITexture*, que é o que o IGUIButton 
usa como textura (é bem simples criar um ITexture, só passar o caminho da imagem no construtor).

Tudo beleza até aqui? Para trocar a imagem, 
quando o mouse estiver sobre o botão (você diz que tem como saber quando isso acontece) é só verificar o "isPressed" desse botão:

-> Se "isPressed == false", então muda a imagem para "ImageHoverNormal" com o método "setImage()" do IGUIButton.
-> Se "isPressed == true", então muda a imagem para "ImageHoverPressed" com o método "setPressedImage()" do IGUIButton.

Fácil não? Só tem que lembrar de fazer as imagens 
trocarem de volta para as normais (não-hover) 
quando o mouse não estiver sobre o botão. 
A moral então seria ter um método para o programador de jogo 
setar quais são essas "ImageHoverNormal" e "ImageHoverPressed", 
e um método que é sempre chamado no update que faz a verificação 
de mouse sobre botão e a troca de imagens.

Seria legal ter um fader padrão já na GUI do motor, do tamanho da tela (que o motor já sabe). 
Aí é só criar métodos para dar fadeIn e fadeOut nesse fader 
(passando como parâmetro o tempo) e um método que retorna se ele já terminou (verifica o atributo "isReady").
http://irrlicht.sourceforge.net/docu/classirr_1_1gui_1_1_i_g_u_i_in_out_fader.html
*/

IrrGUI::IrrGUI(IrrlichtDevice * device)
{	
	driver = device->getVideoDriver();
	guienv = device->getGUIEnvironment();


	irr::core::dimension2d<u32> d = driver->getScreenSize();
	//rootGUI = new IGUIElement(EGUIET_WINDOW,guienv,0,-1,rect<s32>(0, 0, 50, 50)); //guienv->addGUIElement(irr::gui::EGUI_ELEMENT_TYPE.EGUIET_ELEMENT);
	//rootGUI = guienv->addModalScreen(guienv->getRootGUIElement
	rootGUI = guienv->addStaticText(L"",rect<s32>(0, 0, d.Width, d.Height));

	//std::cout << d.Width << " " << d.Height;
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

void IrrGUI::setPressedButton(s32 id, bool value)
{
	std::map<s32, IGUIButton*>::iterator it = buttons.find(id);
    if(it != buttons.end())
	{
		(*it).second->setPressed(value);
	}
}

bool IrrGUI::isPressedButton(s32 id)
{
	std::map<s32, IGUIButton*>::iterator it = buttons.find(id);
    if(it != buttons.end())
	{
		return (*it).second->isPressed();
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
}

