#pragma once

#include <SFML/Graphics.hpp>

class Game_Object
{
public:
	Game_Object();

	void setPosition(sf::Vector2f newPos);
	
	sf::Vector2f getPosition() const;

private:

	sf::Vector2f Position;
};

