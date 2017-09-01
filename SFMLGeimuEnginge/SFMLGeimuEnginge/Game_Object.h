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
	const static unsigned getCount();

	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;
	sf::Vector2f & getVelocity();
	float & getMass();

	void move(sf::Vector2f moveo);

private:

	static unsigned count;

protected:

	float mass = 10;

	sf::Vector2f size = {1, 1};

	sf::Vector2f velocity = { 0,0 };

	sf::Vector2f Position = {0,0};
};

