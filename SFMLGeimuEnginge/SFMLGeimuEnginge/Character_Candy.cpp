#include "Character_Candy.h"
#include "States\Playing_State.h"

Character_Candy::UniqueStats Character_Candy::getUniqueStats() const
{
	return uniqueStats;
}

void Character_Candy::update(float dt)
{
	setHitboxes();
	setPosition(sf::Vector2f(Position.x + velocity.x*dt, Position.y + velocity.y*dt));
	getSprite().setPosition(Position);
}

Character_Candy::Character_Candy()
{
	setBaseStats("Candy",1250,1);
	setPosition(sf::Vector2f(0, 48*16));
	getSprite().setTexture(Resource_Holder::get().getTexture(Texture_Name::test1));
	//getSprite().setColor(sf::Color::Green);
	setSize({ 16,32 });
	getSprite().setScale(
		getSize().x / getSprite().getLocalBounds().width,
		getSize().y / getSprite().getLocalBounds().height
	);
}
