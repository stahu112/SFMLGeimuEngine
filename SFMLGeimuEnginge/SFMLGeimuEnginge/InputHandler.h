#pragma once

#include <SFML/Graphics.hpp>

class InputHandler
{
public:

	static void updateInput(sf::Event e);
	static sf::Keyboard::Key key;
	static bool down;

	static bool checkDown(sf::Keyboard::Key keyp);
	static bool checkUp(sf::Keyboard::Key keyp);

	InputHandler();
};
