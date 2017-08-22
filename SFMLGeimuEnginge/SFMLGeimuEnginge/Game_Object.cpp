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

sf::Vector2f Game_Object::getPosition() const
{
	return Position;
}
