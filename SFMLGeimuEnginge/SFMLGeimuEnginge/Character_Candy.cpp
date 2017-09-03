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

	spriteSheet.setTextureRect(m_animations.at(AnimationID::RunR).getFrame());
	spriteSheet.setScale(
		size.x / spriteSheet.getLocalBounds().width,
		size.y / spriteSheet.getLocalBounds().height
	);
	getSprite().setPosition(Position);
}

Character_Candy::Character_Candy()
{
	setBaseStats("Candy",1250,1);
	spriteSheet.setTexture(Resource_Holder::get().getTexture(Texture_Name::spritesheet));
	mass = 60;
	size = { 16,32 };
	spriteSheet.setScale(
		size.x / spriteSheet.getLocalBounds().width,
		size.y / spriteSheet.getLocalBounds().height
	);
	
	Animation RunRAnim;
	RunRAnim.addFrames({ 0,0,20,38}, 0.1f);
	RunRAnim.addFrames({ 20,0,20,38 }, 0.1f);
	RunRAnim.addFrames({ 40,0,20,38 }, 0.1f);
	RunRAnim.addFrames({ 60,0,20,38 }, 0.1f);
	RunRAnim.addFrames({ 0,38,20,38 }, 0.1f);
	RunRAnim.addFrames({ 20,38,20,38 }, 0.1f);

	m_animations.insert(std::make_pair(AnimationID::RunR, RunRAnim));
}
