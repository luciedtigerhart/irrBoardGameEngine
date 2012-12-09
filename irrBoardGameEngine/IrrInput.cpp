#include <iostream>

#include "IrrInput.h"

using namespace IrrBoardGameEngine;
using namespace gui;

IrrInput::IrrInput()
{
	for (u32 i=0; i<KEY_KEY_CODES_COUNT / 32; ++i)
	{
		keyStatusDown[i] = keyStatusPressed[i] = keyStatusReleased[i] = 0;
	}
	camera = NULL;	
}

void IrrInput::setDriver(IVideoDriver * d)
{
	driver = d;
}

void IrrInput::setDevice(IrrlichtDevice * d)
{
	device = d;

	then = device->getTimer()->getTime();
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
				gui->setPressedButton(guiElementid, true);
				mouseState.leftButtonDown = true;
				break;
			case EMIE_LMOUSE_LEFT_UP:
				gui->setPressedButton(false);
				mouseState.leftButtonDown = false;				
				break;

			case EMIE_RMOUSE_PRESSED_DOWN:
				mouseState.rightButtonDown = true;
				break;

			case EMIE_RMOUSE_LEFT_UP:
				mouseState.rightButtonDown = false;
				break;

			case EMIE_MMOUSE_PRESSED_DOWN:
				mouseState.middleButtonDown = true;
				break;

			case EMIE_MMOUSE_LEFT_UP:
				mouseState.middleButtonDown = false;
				break;

			case EMIE_MOUSE_MOVED:
				mouseState.position.X = event.MouseInput.X;
				mouseState.position.Y = event.MouseInput.Y;
				break;

			default:
				break;
        }
    }

	if (event.EventType == EET_GUI_EVENT)
	{
		guiElementid = event.GUIEvent.Caller->getID();
		switch(event.GUIEvent.EventType)
		{
			case EGET_ELEMENT_HOVERED:
				gui->setMouseOver(guiElementid, true);
				break;
			case EGET_ELEMENT_LEFT:
				gui->setMouseOver(guiElementid, false);
				break;
		}
	}

	if(camera != NULL && camera->is_manager)
	{
		if( event.EventType == EET_KEY_INPUT_EVENT )
		{
			const SEvent::SKeyInput *ev = &event.KeyInput;

			if (!camera->m_Dragging)
			{
				if ( ev->Key == KEY_KEY_F || ev->Key == KEY_SPACE ) camera->is_focused = true;

				else if ( ev->Key != KEY_KEY_F && ev->Key != KEY_SPACE )
				{
					if ( ev->Key == KEY_KEY_R || ev->Key == KEY_HOME )
					{
						camera->is_move = false;
						camera->reset();
					}
					else
					{
						if( ev->Key == KEY_KEY_W || ev->Key == KEY_UP )
						{			
							camera->moveForward(100.0f * deltaTime);
							camera->is_move = true;
						}
						else if( ev->Key == KEY_KEY_S  || ev->Key == KEY_DOWN )
						{			
							camera->moveBackward(100.0f * deltaTime);
							camera->is_move = true;
						}
						else if( ev->Key == KEY_KEY_A  || ev->Key == KEY_LEFT )
						{				
							camera->moveLeft(100.0f * deltaTime);
							camera->is_move = true;
						}
						else if( ev->Key == KEY_KEY_D  || ev->Key == KEY_RIGHT )
						{
							camera->moveRight(100.0f * deltaTime);
							camera->is_move = true;
						}
						else if( ev->Key == KEY_KEY_E  || ev->Key == KEY_PRIOR )
						{
							camera->moveUp(100.0f * deltaTime);
							camera->is_move = true;
						}
						else if( ev->Key == KEY_KEY_Q  || ev->Key == KEY_NEXT )
						{
							camera->moveDown(100.0f * deltaTime);
							camera->is_move = true;
						}
					}
				}
			}

			if(!ev->PressedDown)
			{
				camera->is_focused = false;
				camera->is_move = false;
			}

			return true;
		}
		else if( event.EventType == EET_MOUSE_INPUT_EVENT )
		{
			const SEvent::SMouseInput *ev = &event.MouseInput;
			if( ev->Event == EMIE_MOUSE_WHEEL )
			{
				if (!camera->is_focused)
				{
					if( ev->Wheel >= 0 )
						camera->m_Rad -= 100.0f * deltaTime;
					else
						camera->m_Rad += 100.0f * deltaTime;
				}
			}
			else
			{
				if (!camera->is_move && !camera->is_focused)
				{
					if( !camera->m_Dragging && ev->isRightPressed() )
					{
						camera->m_DragStart.X = (f32)ev->X;
						camera->m_DragStart.Y = (f32)ev->Y;
						camera->m_DragStartRotation.X = camera->m_Rot.X;
						camera->m_DragStartRotation.Y = camera->m_Rot.Y;
						camera->m_Dragging = true;
					}
					else if( camera->m_Dragging && ! ev->isRightPressed() )
					{
						camera->m_Dragging = false;
					}
					else if( camera->m_Dragging && ev->isRightPressed() )
					{		
						//
						// Calcula a rotação feita pelo mouse
						//
						f32 dx = (( ev->X - camera->m_DragStart.X ) / driver->getScreenSize().Width ) * PI;
						f32 dy = (( ev->Y - camera->m_DragStart.Y ) / driver->getScreenSize().Height ) * PI;

						camera->m_Rot.X = camera->m_DragStartRotation.X + dy;
						camera->m_Rot.Y = camera->m_DragStartRotation.Y + dx;
					}
				}
			}
		}
	}

	return false;
}

bool IrrInput::isKeyDown(int keyCode)
{
	return getKeyStatus(keyStatusDown, keyCode);
}

bool IrrInput::isKeyReleased(int keyCode)
{
	return getKeyStatus(keyStatusReleased, keyCode);
}

bool IrrInput::isKeyPressed(int keyCode)
{
	return getKeyStatus(keyStatusPressed, keyCode);
}

void IrrInput::clear()
{
	for (u32 i=0; i<KEY_KEY_CODES_COUNT / 32; ++i)
		keyStatusDown[i] = 0;
}

void IrrInput::update()
{
	now = device->getTimer()->getTime();
	deltaTime = (float)(now - then) / 1000.f;

	for (u32 i=0; i<KEY_KEY_CODES_COUNT / 32; ++i){
		keyStatusReleased[i] = 0;
		keyStatusPressed[i] = 0;
	}

	then = device->getTimer()->getTime();
}

void IrrInput::setKeyStatus(int* k, int keyCode, bool value)
{
	if(value)
	{
		k[keyCode / 32] |= 1 << (keyCode % 32);
	}
	else
	{
		k[keyCode / 32] &= ~(1 << (keyCode % 32));
	}
	std::cout << getKeyStatus(k, keyCode) << " " << value << std::endl;
}

bool IrrInput::getKeyStatus(int* k, int keyCode)
{
	return (k[keyCode / 32] & (1 << (keyCode % 32))) != 0;
}

void IrrInput::setGUI(IrrGUI * currentGUI)
{
	gui = currentGUI;
}

void IrrInput::setCamera(IrrCamera * currentCamera)
{
	camera = currentCamera;
}