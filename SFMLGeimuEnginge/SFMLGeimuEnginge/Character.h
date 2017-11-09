#pragma once

#include "Game_Object.h"
#include "Display.h"
#include <Box2D\Box2D.h>

namespace State { class Playing; };

class Character : public Game_Object
{
	
protected:

	sf::Sprite sprite;

	b2World * boxWorldPtr = nullptr;

public:

	void draw();

	virtual void processStates() = 0;
	virtual void update(float dt) = 0;

	Character();

};

