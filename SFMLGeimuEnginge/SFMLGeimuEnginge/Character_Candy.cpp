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
	spriteSheet.setTexture(Resource_Holder::get().getTexture(Texture_Name::test1));
	mass = 60;
	size = { 16,32 };
	spriteSheet.setScale(
		size.x / spriteSheet.getLocalBounds().width,
		size.y / spriteSheet.getLocalBounds().height
	);
}
