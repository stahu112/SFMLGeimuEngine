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

	bool onGround = false, wallL = false, wallR = false, wallDone = false, falling = false;
	int numContacts = 0, numWallLContacts = 0, numWallRContacts = 0;

	int maxJumps = 1;

	float speedX = 5.f;

	float force;

	void draw();

	virtual void createRigidBody() = 0;

	virtual void changePosition(b2Vec2 newPos) = 0;

	virtual void processStates(float dt) = 0;
	virtual void update(float dt) = 0;

	Character();

};

