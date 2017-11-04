#pragma once

#include "Game_Object.h"
#include "Display.h"

namespace State { class Playing; };

class Character : public Game_Object
{
	
protected:

	sf::Sprite sprite;

public:

	sf::Vector2f goalVelocity;

	//Physics Component

	void draw();

	virtual void update(float dt) = 0;

	Character();

};

