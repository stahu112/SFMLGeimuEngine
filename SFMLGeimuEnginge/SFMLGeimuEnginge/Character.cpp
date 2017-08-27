#include "Character.h"

#include <iostream>

void Character::update(float dt)
{
}

void Character::setBaseHitbox(sf::Vector2f size)
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

sf::FloatRect & Character::getBaseHitbox()
{
	return baseHitbox;
}

sf::Sprite & Character::getSprite()
{
	return spriteSheet;
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

void Character::draw()
{
	Display::draw(getSprite());
}

Character::Character()
{	
}

void Character::reset()
{
	setVelocity({ 0,0 });
}

//Commands
void Character::jump()
{
	setVelocity(sf::Vector2f(getVelocity().x, -10));
}

void Character::walkL()
{
	setVelocity(sf::Vector2f(-1000, getVelocity().y));
}

void Character::walkR()
{
	setVelocity(sf::Vector2f(1000, getVelocity().y));
}

void Character::runL()
{
	setVelocity(sf::Vector2f(-15, getVelocity().y));
}

void Character::runR()
{
	setVelocity(sf::Vector2f(15, getVelocity().y));
}