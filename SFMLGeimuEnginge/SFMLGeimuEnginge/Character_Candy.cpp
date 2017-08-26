#include "Character_Candy.h"

Character_Candy::UniqueStats Character_Candy::getUniqueStats() const
{
	return uniqueStats;
}

void Character_Candy::handleInput()
{
}

void Character_Candy::processStates()
{
}

void Character_Candy::update(float dt)
{
	//apply physics and shit
	getSprite().setPosition(getPosition());
	draw();
}

Character_Candy::Character_Candy()
{
	setBaseStats("Candy",1250,1);
	getSprite().setTexture(Resource_Holder::get().getTexture(Texture_Name::test1));
}

void Character_Candy::jump()
{
	setVelocity(sf::Vector2f(getVelocity().x, -10));
}

void Character_Candy::jump(float vel)
{
	setVelocity(sf::Vector2f(getVelocity().x, -vel));
}

void Character_Candy::walkL()
{
	setVelocity(sf::Vector2f(-5,getVelocity().y));
}

void Character_Candy::walkR()
{
	setVelocity(sf::Vector2f(5, getVelocity().y));
}

void Character_Candy::runL()
{
	setVelocity(sf::Vector2f(-15, getVelocity().y));
}

void Character_Candy::runR()
{
	setVelocity(sf::Vector2f(15, getVelocity().y));
}