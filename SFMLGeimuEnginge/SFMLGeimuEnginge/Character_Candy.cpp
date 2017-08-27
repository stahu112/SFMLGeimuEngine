#include "Character_Candy.h"

Character_Candy::UniqueStats Character_Candy::getUniqueStats() const
{
	return uniqueStats;
}

void Character_Candy::handleInput()
{
	command = inputHandler.handleInput();

	if (command)
	{
		command->execute(*this);
	}
	else reset();
}

void Character_Candy::processStates()
{
}

void Character_Candy::update(float dt)
{
	//HANDLEINPUT
	handleInput();

	std::cout << getVelocity().x << std::endl;
	std::cout << getVelocity().y << std::endl;
	std::cout << getPosition().x << " " << getPosition().y << std::endl;

	//TODO Apply physics and stuff
	setPosition(sf::Vector2f(getPosition().x+getVelocity().x*dt, getPosition().y+getVelocity().y*dt));
	
	//SETPOSITION
	getSprite().setPosition(getPosition());
	
	//DRAW
	draw();
}

Character_Candy::Character_Candy()
{
	setBaseStats("Candy",1250,1);
	getSprite().setTexture(Resource_Holder::get().getTexture(Texture_Name::test1));
	setSize({ 16,32 });
	getSprite().setScale(
		getSize().x / getSprite().getLocalBounds().width,
		getSize().y / getSprite().getLocalBounds().height
	);
}
