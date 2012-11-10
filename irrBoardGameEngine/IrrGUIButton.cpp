#include "IrrGUIButton.h"

using namespace IrrBoardGameEngine;

IrrGUIButton::IrrGUIButton(IGUIEnvironment * g, IVideoDriver * d, s32 ID, int posx, int posy, IGUIElement* parent, bool Toggle)
{
	guienv = g;
	driver = d;

	id = ID;

	parent_node = parent;

	x = posx;
	y = posy;

	pressed = false;
	hover = false;
	visible = true;
	disabled = false;

	img_disabled = NULL;

	toggle = Toggle;
}

IrrGUIButton::~IrrGUIButton(void)
{
}

void IrrGUIButton::addImage(char* file)
{
	img_normal = guienv->addImage(driver->getTexture(file),position2d<int>(x, y),true,parent_node,id);
}

void IrrGUIButton::addImageHover(char* file)
{
	img_hover = guienv->addImage(driver->getTexture(file),position2d<int>(x, y),true,parent_node,id);
	img_hover->setVisible(false);
}

void IrrGUIButton::addImagePressed(char* file)
{
	img_pressed = guienv->addImage(driver->getTexture(file),position2d<int>(x, y),true,parent_node,id);
	img_pressed->setVisible(false);
}

void IrrGUIButton::addImagePressedHover(char* file)
{
	img_pressed_hover = guienv->addImage(driver->getTexture(file),position2d<int>(x, y),true,parent_node,id);
	img_pressed_hover->setVisible(false);
}

void IrrGUIButton::addImageDisabled(char* file)
{
	img_disabled = guienv->addImage(driver->getTexture(file),position2d<int>(x, y),true,parent_node,id);
	img_disabled->setVisible(false);
}

void IrrGUIButton::setHover(bool value)
{
	hover = value;
	update();
}

bool IrrGUIButton::isHover()
{
	return hover;
}

void IrrGUIButton::setPressed(bool value)
{
	if(toggle && pressed)
	{
		if(value) pressed = false;
	}
	else
	{
		pressed = value;
	}
	update();
}

bool IrrGUIButton::isPressed()
{
	return (pressed && !disabled);
}

void IrrGUIButton::setVisible(bool value)
{
	visible = value;
	update();
}

void IrrGUIButton::setDisabled(bool value)
{
	disabled = value;
}

bool IrrGUIButton::isDisabled()
{
	return disabled;
}

void IrrGUIButton::update()
{
	img_normal->setVisible(false);
	img_hover->setVisible(false);
	img_pressed->setVisible(false);
	img_pressed_hover->setVisible(false);
	if(img_disabled != NULL) img_disabled->setVisible(false);

	if(visible)
	{
		if(disabled)
		{
			if(img_disabled == NULL)
			{
				img_normal->setVisible(true);
				img_normal->setColor(SColor(255,100,100,100));
			}
			else
			{
				img_disabled->setVisible(true);
			}
		}
		else if(pressed)
		{
			if(hover)
			{
				img_pressed_hover->setVisible(true);
			}
			else
			{
				img_pressed->setVisible(true);
			}
		}
		else if(hover)
		{
			img_hover->setVisible(true);
		}
		else
		{
			img_normal->setVisible(true);
		}
	}
}
