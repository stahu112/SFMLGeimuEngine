#pragma once

//Zrobi sie cos jak w unity
//TODO wykombinowac jak zrobic componenty

#include <SFML/Graphics.hpp>

class Game_Object
{
public:
	Game_Object();

	void setPosition(sf::Vector2f newPos);

	virtual void update(float dt) = 0;
	
	sf::Vector2f getPosition() const;

private:

	static unsigned count;

	sf::Vector2f Position;
};

