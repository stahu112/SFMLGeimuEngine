#pragma once

#include "Game_Object.h"
#include "Res\Resource_Holder.h"

class Platform : public Game_Object
{

protected:
	sf::RectangleShape shape;
	sf::Vector2f size;

public:
	Platform();

};

