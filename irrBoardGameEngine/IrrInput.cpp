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
	//multimap<std::string,int> *keys = new multimap<std::string,int>();
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
				//std::cout << "EMIE_LMOUSE_PRESSED_DOWN" << endl;
				break;
			case EMIE_LMOUSE_LEFT_UP:
				gui->setPressedButton(false);
				mouseState.leftButtonDown = false;
				//std::cout << "EMIE_LMOUSE_LEFT_UP" << endl;
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
			/*
			if( ev->Key == KEY_LEFT )
				camera->m_Rot.Y -= 0.1f;
			else if( ev->Key == KEY_RIGHT )
				camera->m_Rot.Y += 0.1f;
			else if( ev->Key == KEY_UP )
				camera->m_Rot.X += 0.1f;
			else if( ev->Key == KEY_DOWN )
				camera->m_Rot.X -= 0.1f;
			*/			

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
							//camera->m_LookAt.Z += 0.1f;
							//camera->m_Trans.Z += 0.1f;
				
							camera->moveForward(100.0f * deltaTime);
							camera->is_move = true;
						}
						else if( ev->Key == KEY_KEY_S  || ev->Key == KEY_DOWN )
						{
							//camera->m_LookAt.Z -= 0.1f;
							//camera->m_Trans.Z -= 0.1f;
				
							camera->moveBackward(100.0f * deltaTime);
							camera->is_move = true;
						}
						else if( ev->Key == KEY_KEY_A  || ev->Key == KEY_LEFT )
						{
							//camera->m_LookAt.X -= 0.1f;
							//camera->m_Trans.X -= 0.1f;
				
							camera->moveLeft(100.0f * deltaTime);
							camera->is_move = true;
						}
						else if( ev->Key == KEY_KEY_D  || ev->Key == KEY_RIGHT )
						{
							//camera->m_LookAt.X += 0.1f;
							//camera->m_Trans.X += 0.1f;
				
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

			//camera->update();

			return true;
		}
		else if( event.EventType == EET_MOUSE_INPUT_EVENT )
		{
			const SEvent::SMouseInput *ev = &event.MouseInput;
			if( ev->Event == EMIE_MOUSE_WHEEL )
			{
				//cout << "Wheel event: " << ev->Wheel << endl;

				if (!camera->is_focused)
				{
					if( ev->Wheel >= 0 )
						camera->m_Rad -= 100.0f * deltaTime;
					else
						camera->m_Rad += 100.0f * deltaTime;
				}

				//camera->update();
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
						// Calculate a rotational offset in the range of -PI to +PI
						f32 dx = (( ev->X - camera->m_DragStart.X ) / driver->getScreenSize().Width ) * PI;
						f32 dy = (( ev->Y - camera->m_DragStart.Y ) / driver->getScreenSize().Height ) * PI;
						// Calculate the new total rotation
						camera->m_Rot.X = camera->m_DragStartRotation.X + dy;
						camera->m_Rot.Y = camera->m_DragStartRotation.Y + dx;

						//camera->update();
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
/*
bool IrrInput::getButton(char *c)
{
	std::string t(c);
	multimap<std::string, int>::iterator i = keys->find(t);
	if(i==keys->end())
	{
		return false;
	}
	else
	{
		multimap<std::string, int>::iterator lastElement = keys->upper_bound(t);
		for(; i != lastElement; ++i)
		{
			if(isKeyDown(i->second))
			{
				return true;
			}
		}	
	}
	return false;
}

bool IrrInput::getButtonDown(char *c)
{
	std::string t(c);
	multimap<std::string, int>::iterator i = keys->find(t);
	if(i==keys->end())
	{
		return false;
	}
	else
	{
		multimap<std::string, int>::iterator lastElement = keys->upper_bound(t);
		for(; i != lastElement; ++i)
		{
			if(isKeyDown(i->second))
			{
				return true;
			}
		}	
	}
	return false;
}

bool IrrInput::getButtonPressed(char *c)
{
	std::string t(c);
	multimap<std::string, int>::iterator i = keys->find(t);
	if(i==keys->end())
	{
		return false;
	}
	else
	{
		multimap<std::string, int>::iterator lastElement = keys->upper_bound(t);
		for(; i != lastElement; ++i)
		{
			if(isKeyPressed(i->second))
			{
				return true;
			}
		}	
	}
	return false;
}

bool IrrInput::getButtonReleased(char *c)
{
	std::string t(c);
	multimap<std::string, int>::iterator i = keys->find(t);
	if(i==keys->end())
	{
		return false;
	}
	else
	{
		multimap<std::string, int>::iterator lastElement = keys->upper_bound(t);
		for(; i != lastElement; ++i)
		{
			if(isKeyReleased(i->second))
			{
				return true;
			}
		}	
	}
	return false;
}

void IrrInput::registry(char *t, int k)
{
	//keys->insert(std::pair<std::string,int>(std::string(t),k));
	keys->insert(std::pair<std::string,int>(std::string("Fire"),irr::KEY_SPACE));
}
*/