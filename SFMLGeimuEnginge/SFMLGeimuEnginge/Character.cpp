#include "Character.h"

#include <iostream>
#include "States\Playing_State.h"

void Character::update(float dt)
{
}

void Character::setLevelHandle(LevelID id, State::Playing& state)
{
	levelHandle = state.getCurrentLevel();
}

void Character::setVelocity(sf::Vector2f newVel)
{
	velocity = newVel;
}

sf::Vector2f Character::getVelocity() const
{
	return velocity;
}

void Character::handleInput()
{
}

void Character::processStates()
{
}

Character::Character()
{	
}
