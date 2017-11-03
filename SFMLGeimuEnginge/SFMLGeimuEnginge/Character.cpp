#include "Character.h"

#include <iostream>
#include "States\Playing_State.h"

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
	this->baseStats.ID = ID;
	this->baseStats.BaseHP = BaseHP;
}

void Character::draw()
{
	Display::draw(getSprite());
}

Character::Character()
{	
}