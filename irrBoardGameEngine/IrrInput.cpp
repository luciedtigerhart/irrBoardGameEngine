#include <iostream>

#include "IrrInput.h"

using namespace IrrBoardGameEngine;

IrrInput::IrrInput()
{
	for (u32 i=0; i<KEY_KEY_CODES_COUNT / 32; ++i)
	{
		keyStatusDown[i] = keyStatusPressed[i] = keyStatusReleased[i] = 0;
	}

	multimap<string,int> *keys = new multimap<string,int>();
}

bool IrrInput::OnEvent(const SEvent& event)
{
	// Usando o teclado
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
	{
		//Marca da tecla (obtida no evento) como pressionada
		if(event.KeyInput.PressedDown && !getKeyStatus(keyStatusDown,event.KeyInput.Key))
		{
			// Recem pressionado
			setKeyStatus(keyStatusDown, event.KeyInput.Key, true);
			setKeyStatus(keyStatusPressed, event.KeyInput.Key, true);
		}
		else if(!event.KeyInput.PressedDown && getKeyStatus(keyStatusDown,event.KeyInput.Key))
		{
			// Recem solto
			setKeyStatus(keyStatusDown,event.KeyInput.Key, false);
			setKeyStatus(keyStatusReleased, event.KeyInput.Key, true);
		}
	}

	// Usando o mouse
    if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
    {
        switch(event.MouseInput.Event)
        {
			case EMIE_LMOUSE_PRESSED_DOWN:
				mouseState.leftButtonDown = true;
				break;

			case EMIE_LMOUSE_LEFT_UP:
				mouseState.leftButtonDown = false;
				break;

			case EMIE_RMOUSE_PRESSED_DOWN:
				mouseState.rightButtonDown = true;
				break;

			case EMIE_RMOUSE_LEFT_UP:
				mouseState.rightButtonDown = false;
				break;

			case EMIE_MOUSE_MOVED:
				mouseState.position.X = event.MouseInput.X;
				mouseState.position.Y = event.MouseInput.Y;
				break;

			default:
                // We won't use the wheel
                break;
        }
    }
	return false;
}

bool IrrInput::isKeyDown(int keyCode) {
	return getKeyStatus(keyStatusDown, keyCode);
}

bool IrrInput::isKeyReleased(int keyCode) {
	return getKeyStatus(keyStatusReleased, keyCode);
}

bool IrrInput::isKeyPressed(int keyCode) {
	return getKeyStatus(keyStatusPressed, keyCode);
}

void IrrInput::clear() {
	for (u32 i=0; i<KEY_KEY_CODES_COUNT / 32; ++i)
		keyStatusDown[i] = 0;
}

void IrrInput::update() {
	for (u32 i=0; i<KEY_KEY_CODES_COUNT / 32; ++i){
		keyStatusReleased[i] = 0;
		keyStatusPressed[i] = 0;
	}
}

void IrrInput::setKeyStatus(int* k, int keyCode, bool value) {
	if(value) {
		k[keyCode / 32] |= 1 << (keyCode % 32);
	} else {
		k[keyCode / 32] &= ~(1 << (keyCode % 32));
	}
	std::cout << getKeyStatus(k, keyCode) << " " << value << std::endl;
}

bool IrrInput::getKeyStatus(int* k, int keyCode) {
	return (k[keyCode / 32] & (1 << (keyCode % 32))) != 0;
}


bool IrrInput::getButton(char *c) {
	std::string t(c);
	multimap<std::string, int>::iterator i =	keys->find(t);
	if(i==keys->end()) {
		return false;
	} else {
		multimap<std::string, int>::iterator lastElement = keys->upper_bound(t);
		for(; i != lastElement; ++i) {
			if(isKeyDown(i->second)){
				return true;
			}
		}	
	}
	return false;
}

bool IrrInput::getButtonDown(char *c) {
	std::string t(c);
	multimap<std::string, int>::iterator i =	keys->find(t);
	if(i==keys->end()){
		return false;
	} else{
		multimap<std::string, int>::iterator lastElement = keys->upper_bound(t);
		for(; i != lastElement; ++i){
			if(isKeyDown(i->second)){
				return true;
			}
		}	
	}
	return false;
}

bool IrrInput::getButtonPressed(char *c) {
	std::string t(c);
	multimap<std::string, int>::iterator i =	keys->find(t);
	if(i==keys->end()){
		return false;
	} else{
		multimap<std::string, int>::iterator lastElement = keys->upper_bound(t);
		for(; i != lastElement; ++i){
			if(isKeyPressed(i->second)){
				return true;
			}
		}	
	}
	return false;
}

bool IrrInput::getButtonReleased(char *c) {
	std::string t(c);
	multimap<std::string, int>::iterator i =	keys->find(t);
	if(i==keys->end()){
		return false;
	} else{
		multimap<string, int>::iterator lastElement = keys->upper_bound(t);
		for(; i != lastElement; ++i){
			if(isKeyReleased(i->second)){
				return true;
			}
		}	
	}
	return false;
}

void IrrInput::registry(char *t, int k)
{
	keys->insert(std::pair<std::string,int>(string(t),k));
}