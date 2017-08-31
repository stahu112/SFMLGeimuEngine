#include "Game_Object.h"

unsigned Game_Object::count = 0;

Game_Object::Game_Object() 
{
	count++;

	Position.x = 0;
	Position.y = 0;
}

void Game_Object::setPosition(sf::Vector2f newPos)
{
	Position = newPos;
}

void Game_Object::setSize(sf::Vector2f newsize)
{
	size = newsize;
}

sf::Vector2f Game_Object::getPosition() const
{
	return Position;
}

sf::Vector2f Game_Object::getSize() const
{
	return size;
}

void Game_Object::move(sf::Vector2f moveo)
{
	Position.x += moveo.x;
	Position.y += moveo.y;
}

sf::Vector2f & Game_Object::getVelocity()
{
	return velocity;
}

float & Game_Object::getMass()
{
	return mass;
}
