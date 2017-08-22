#include "Character.h"

#include <iostream>

void Character::update(float dt)
{
	//applyPhysics(dt);
	processStates();
	handleInput();
	std::cout << (int)currentState << std::endl;
}

void Character::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		velocity.y = -10;
	}
}

void Character::processStates()
{
	if (velocity.x == 0 && velocity.y == 0) currentState = State::Idle; else
		if (velocity.y < 0) currentState = State::Jumping; else
			if (velocity.x > 0) currentState = State::WalkRight; else
				if (velocity.x < 0) currentState = State::WalkLeft;
}

Character::Character()
{
	
}
