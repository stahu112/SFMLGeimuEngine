#include "Character_Candy.h"
#include "States\Playing_State.h"

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
	else if (getVelocity().x != 0)
	{
		resetX();
	}
	else if (getVelocity().y < 0)
	{
		resetY();
	}
}

void Character_Candy::processStates()
{
	
}

void Character_Candy::update(float dt)
{
	//HANDLEINPUT
	handleInput();

	setBaseHitbox();

	//Apply Gravity
	if (!getFlags().onGround)
	{
		float olVy = getVelocity().y;
		getVelocity().y = olVy + 10;
	}

	setPosition(sf::Vector2f(getPosition().x + getVelocity().x*dt, getPosition().y + getVelocity().y*dt));

	processStates();

	//SETPOSITION
	getSprite().setPosition(getPosition());
	
	//DRAW
	draw();
}

Character_Candy::Character_Candy()
{
	setBaseStats("Candy",1250,1);
	setBaseHitbox(sf::Vector2i(getSize().x*16, getSize().y * 2)*16);
	setPosition(sf::Vector2f(50, 20));
	getSprite().setTexture(Resource_Holder::get().getTexture(Texture_Name::test1));
	setSize({ 16,32 });
	getSprite().setScale(
		getSize().x / getSprite().getLocalBounds().width,
		getSize().y / getSprite().getLocalBounds().height
	);
}
