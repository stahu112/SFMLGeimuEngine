#include "Character_Candy.h"
#include "States\Playing_State.h"

void Character_Candy::processStates()
{
	if (flags.collidedPlat) flags.onGround = true;
	else flags.onGround = false;

	switch (currentState)
	{

		//Standing
	case CharState::StandingL:
		flags.JumpCount = 0;
		break;
	
	case CharState::StandingR:
		flags.JumpCount = 0;
		break;

		//WALK RUN
	case CharState::WalkL:
		flags.JumpCount = 0;
		velocity.x = -baseStats.walkFactor;
		break;

	case CharState::WalkR:
		flags.JumpCount = 0;
		velocity.x = baseStats.walkFactor;
		break;

	case CharState::RunL:
		flags.JumpCount = 0;
		velocity.x = -baseStats.runFactor;
		break;

	case CharState::RunR:
		flags.JumpCount = 0;
		velocity.x = baseStats.runFactor;
		break;
		
		//JUMP DIVE
	case CharState::JumpL:
		flags.onGround = false;
		if (flags.JumpCount < baseStats.Jumps)
		{
			velocity.y = -baseStats.jumpFactor;
			flags.JumpCount++;
		}
		break;

	case CharState::JumpR:
		flags.onGround = false;
		if (flags.JumpCount < baseStats.Jumps)
		{
			velocity.y = -baseStats.jumpFactor;
			flags.JumpCount++;
		}
		break;

	case CharState::DiveL:
		break;
		
	case CharState::DiveR:
		break;
	}
}

Character_Candy::UniqueStats Character_Candy::getUniqueStats() const
{
	return uniqueStats;
}

void Character_Candy::update(float dt)
{
	processStates();

	setHitboxes();

	if(!flags.onGround) Physics::applyGravity(*this, dt);

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
