#include "Character_Candy.h"
#include "States\Playing_State.h"

Character_Candy::UniqueStats Character_Candy::getUniqueStats() const
{
	return uniqueStats;
}

void Character_Candy::update(float dt)
{

	if (velocity.x > 0)
	{
		setCurrentAnim(AnimationID::RunR);
		spriteSheet.setTexture(Resource_Holder::get().getTexture(Texture_Name::spritesheet));
	}
	else if (velocity.x < 0)
	{
		setCurrentAnim(AnimationID::RunL);
		spriteSheet.setTexture(Resource_Holder::get().getTexture(Texture_Name::spritesheet1));
	}

	setPosition(Position + velocity*dt);

	updateAnim();
	getSprite().setPosition(Position);
}

void Character_Candy::setCurrentAnim(AnimationID id)
{
	currentAnim = &m_animations.at(id);
}

void Character_Candy::updateAnim()
{
	spriteSheet.setTextureRect(currentAnim->getFrame());
	spriteSheet.setScale(
		size.x / spriteSheet.getLocalBounds().width,
		size.y / spriteSheet.getLocalBounds().height
	);
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

	Animation RunLAnim;
	RunLAnim.addFrames({ 60,0,20,38 }, 0.1f);
	RunLAnim.addFrames({ 40,0,20,38 }, 0.1f);
	RunLAnim.addFrames({ 20,0,20,38 }, 0.1f);
	RunLAnim.addFrames({ 0,0,20,38 }, 0.1f);
	RunLAnim.addFrames({ 60,38,20,38 }, 0.1f);
	RunLAnim.addFrames({ 40,38,20,38 }, 0.1f);
	m_animations.insert(std::make_pair(AnimationID::RunL, RunLAnim));

	setCurrentAnim(AnimationID::RunR);
}
