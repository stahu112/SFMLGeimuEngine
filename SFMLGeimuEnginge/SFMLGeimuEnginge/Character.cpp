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
	
	if (isDEBUG)
	{
		sf::CircleShape sh1(1), sh2(1), sh3(1), sh4(1), sh11(1), sh12(1), sh13(1), sh14(1), sh15(1), sh16(1);

		sh1.setPosition(left - 0.5, top - 0.5);
		sh2.setPosition(right - 0.5, top - 0.5);
		sh3.setPosition(left - 0.5, bot - 0.5);
		sh4.setPosition(right - 0.5, bot - 0.5);

		sh11.setPosition(topLeft.x*tileSize - 0.5, topLeft.y*tileSize - 0.5);
		sh12.setPosition(topRight.x*tileSize - 0.5, topRight.y*tileSize - 0.5);
		//sh13.setPosition(Left.x*tileSize - 0.5, Left.y*tileSize - 0.5);
		//sh14.setPosition(Right.x*tileSize - 0.5, Right.y*tileSize - 0.5);
		sh15.setPosition(botLeft.x*tileSize - 0.5, botLeft.y*tileSize - 0.5);
		sh16.setPosition(botRight.x*tileSize - 0.5, botRight.y*tileSize - 0.5);

		sh1.setFillColor(sf::Color::Blue);
		sh2.setFillColor(sf::Color::Blue);
		sh3.setFillColor(sf::Color::Blue);
		sh4.setFillColor(sf::Color::Blue);

		sh11.setFillColor(sf::Color::Magenta);
		sh12.setFillColor(sf::Color::Magenta);
		//sh13.setFillColor(sf::Color::Magenta);
		//sh14.setFillColor(sf::Color::Magenta);
		sh15.setFillColor(sf::Color::Magenta);
		sh16.setFillColor(sf::Color::Magenta);

		Display::draw(sh1);
		Display::draw(sh2);
		Display::draw(sh3);
		Display::draw(sh4);

		Display::draw(sh11);
		Display::draw(sh12);
		//Display::draw(sh13);
		//Display::draw(sh14);
		Display::draw(sh15);
		Display::draw(sh16);
	}
}

Character::Character()
{	
}