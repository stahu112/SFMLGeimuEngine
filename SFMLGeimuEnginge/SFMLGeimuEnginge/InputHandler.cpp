#include "InputHandler.h"
#include <iostream>

//KEYBOARD
sf::Keyboard::Key InputHandler::key = sf::Keyboard::Unknown;
bool InputHandler::down = false;

//JOYSTICK
bool InputHandler::joyConnected = false;
unsigned InputHandler::jKey = -1;
bool InputHandler::jDown = false;
unsigned InputHandler::joyId = -1;

void InputHandler::updateInput(sf::Event e)
{
	if(!joyConnected) connectJoy();

	//KEYBOARD
	if (e.type == sf::Event::KeyPressed)
	{
		key = e.key.code;
		down = true;
	}
	else if (e.type == sf::Event::KeyReleased)
	{
		key = e.key.code;
		down = false;
	}

	//JOYSTICK
	if (joyConnected)
	{
		if (e.type == sf::Event::JoystickButtonPressed)
		{
			jKey = e.joystickButton.button;
			jDown = true;
		}
		else if (e.type == sf::Event::JoystickButtonReleased)
		{
			jKey = e.joystickButton.button;
			jDown = false;
		}
	}
}

bool InputHandler::checkDown(sf::Keyboard::Key keyp)
{
	if (down == true)
	{
		if (key == keyp) return true;
		else return false;
	}
	return false;
}

bool InputHandler::checkUp(sf::Keyboard::Key keyp)
{
	if (!down)
	{
		if (key == keyp) return true;
		else return false;
	}
	return false;
}

void InputHandler::connectJoy()
{	
	if(!joyConnected)
		for (unsigned i = 0; i < 8; i++)
		{
			if (sf::Joystick::isConnected(i))
			{
				joyId = i;
				joyConnected = true;
			}
		}
}

bool InputHandler::checkJDown(unsigned butt)
{
	if (jDown)
	{
		if (jKey == butt) return true;
		else return false;
	}
	return false;
}

bool InputHandler::checkJUp(unsigned butt)
{
	if (!jDown)
	{
		if (jKey == butt) return true;
		else return false;
	}
	return false;
}

InputHandler::InputHandler()
{
}
