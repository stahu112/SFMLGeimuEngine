#include "InputHandler.h"

sf::Keyboard::Key InputHandler::key = sf::Keyboard::Unknown;
bool InputHandler::down = false;

void InputHandler::updateInput(sf::Event e)
{
	if (e.type == sf::Event::KeyPressed)
	{
		key = e.key.code;
		down = true;
		return;
	}
	else if (e.type == sf::Event::KeyReleased)
	{
		key = e.key.code;
		down = false;
		return;
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

InputHandler::InputHandler()
{
}
