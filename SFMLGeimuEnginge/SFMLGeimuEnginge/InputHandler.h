#pragma once

#include <SFML/Graphics.hpp>

class InputHandler
{
public:


	static void updateInput(sf::Event e);
	
	//KEYBOARD
	static sf::Keyboard::Key key;
	static bool down;

	static bool checkDown(sf::Keyboard::Key keyp);
	static bool checkUp(sf::Keyboard::Key keyp);

	//JOYSTICK
	static bool joyConnected;
	static unsigned joyId;

	static unsigned jKey;
	static bool jDown;

	static void connectJoy();

	static float getAxisPosition(sf::Joystick::Axis jAxis);

	static bool checkJDown(unsigned butt);
	static bool checkJUp(unsigned butt);

	InputHandler();
};
