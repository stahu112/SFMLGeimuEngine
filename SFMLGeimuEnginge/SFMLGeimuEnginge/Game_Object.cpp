#include "Game_Object.h"



Game_Object::Game_Object() 
{
	Position.x = 0;
	Position.y = 0;
}

sf::Vector2f Game_Object::getPosition() const
{
	return Position;
}
