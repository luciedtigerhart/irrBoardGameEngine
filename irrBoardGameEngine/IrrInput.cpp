#include <iostream>

#include "IrrInput.h"

using namespace IrrBoardGameEngine;

IrrInput::IrrInput() {
	for (u32 i=0; i<KEY_KEY_CODES_COUNT / 32; ++i) {
		keyStatusDown[i] = keyStatusPressed[i] = keyStatusReleased[i] = 0;
	}
}

bool IrrInput::OnEvent(const SEvent& event) {
	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		//Marca da tecla (obtida no evento) como pressionada
		if(event.KeyInput.PressedDown && !getKeyStatus(keyStatusDown,event.KeyInput.Key)) {
			// Recem pressionado
			setKeyStatus(keyStatusDown, event.KeyInput.Key, true);
			setKeyStatus(keyStatusPressed, event.KeyInput.Key, true);
		} else if(!event.KeyInput.PressedDown && getKeyStatus(keyStatusDown,event.KeyInput.Key)) {
			// Recem solto
			setKeyStatus(keyStatusDown,event.KeyInput.Key, false);
			setKeyStatus(keyStatusReleased, event.KeyInput.Key, true);
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