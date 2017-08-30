#pragma once

//Zrobi sie cos jak w unity
//TODO wykombinowac jak zrobic componenty

#include <SFML/Graphics.hpp>

class Game_Object
{
public:
	Game_Object();

	//Setters
	void setPosition(sf::Vector2f newPos);
	void setSize(sf::Vector2f newsize);

	//Getters
	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;

	void move(sf::Vector2f moveo);

private:

	static unsigned count;

protected:

	sf::Vector2f size = {1, 1};

	sf::Vector2f Position = {0,0};
};

