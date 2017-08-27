#include "Character.h"

#include <iostream>
#include "States\Playing_State.h"

void Character::update(float dt)
{
}

void Character::setBaseHitbox(sf::Vector2i size)
{
	baseHitbox.left = getPosition().x;
	baseHitbox.top = getPosition().y;

	baseHitbox.width = size.x;
	baseHitbox.height = size.y;
}

void Character::setBaseHitbox()
{
	baseHitbox.left = getPosition().x;
	baseHitbox.top = getPosition().y;
}

sf::IntRect & Character::getBaseHitbox()
{
	return baseHitbox;
}

sf::Sprite & Character::getSprite()
{
	return spriteSheet;
}

Character::Flags & Character::getFlags()
{
	return flags;
}

Character::BaseStats Character::getBaseStats() const
{
	return baseStats;
}

void Character::setBaseStats(std::string ID, unsigned BaseHP, unsigned Level)
{
	this->baseStats.Level = Level;
	this->baseStats.ID = ID;
	this->baseStats.BaseHP = BaseHP;
}

void Character::setVelocity(sf::Vector2f newVel)
{
	velocity = newVel;
}

sf::Vector2f & Character::getVelocity()
{
	return velocity;
}

void Character::handleInput()
{
}

void Character::processStates()
{
}

void Character::draw()
{
	Display::draw(getSprite());
}

Character::Character()
{	
}

void Character::resetX()
{
	setVelocity({ 0,getVelocity().y });
}

void Character::resetY()
{
	setVelocity({getVelocity().x,0});
}

//Commands
void Character::jump()
{
	setVelocity(sf::Vector2f(getVelocity().x, -50));
}

void Character::walkL()
{
	setVelocity(sf::Vector2f(-20, getVelocity().y));
}

void Character::walkR()
{
	setVelocity(sf::Vector2f(20, getVelocity().y));
}

void Character::runL()
{
	setVelocity(sf::Vector2f(-50, getVelocity().y));
}

void Character::runR()
{
	setVelocity(sf::Vector2f(50, getVelocity().y));
}