#include "Character.h"

#include <iostream>
#include "States\Playing_State.h"

void Character::update(float dt)
{
}

sf::FloatRect Character::getHitbox(HitId box) const
{
	if (box == HitId::H) return higherHitbox;
	else if (box == HitId::L) return lowerHitbox;
}

void Character::setHitboxes()
{
	higherHitbox.width = size.x;
	higherHitbox.height = size.y / 2;

	higherHitbox.left = Position.x;
	higherHitbox.top = Position.y;

	lowerHitbox.width = size.x;
	lowerHitbox.height = (size.y / 2);

	lowerHitbox.left = Position.x;
	lowerHitbox.top = Position.y + size.y /2;
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

void Character::draw()
{
	Display::draw(getSprite());
}

Character::Character()
{	
}

//Commands
void Character::jump()
{
	velocity.y = -300;
}