#include "Character_Candy.h"

Character_Candy::UniqueStats Character_Candy::getUniqueStats() const
{
	return uniqueStats;
}

void Character_Candy::handleInput()
{
	command = inputHandler.handleInput();

	if(command) command->execute(*this);
}

void Character_Candy::processStates()
{
}

void Character_Candy::update(float dt)
{
	//apply physics and shit
	handleInput();

	std::cout << getVelocity().y;

	getSprite().setPosition(getPosition());
	draw();
}

Character_Candy::Character_Candy()
{
	setBaseStats("Candy",1250,1);
	getSprite().setTexture(Resource_Holder::get().getTexture(Texture_Name::test1));
}
