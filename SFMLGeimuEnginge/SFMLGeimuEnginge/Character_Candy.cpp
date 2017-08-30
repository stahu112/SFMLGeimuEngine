#include "Character_Candy.h"
#include "States\Playing_State.h"

Character_Candy::UniqueStats Character_Candy::getUniqueStats() const
{
	return uniqueStats;
}

void Character_Candy::processStates()
{
	switch (currentState)
	{
	//STANDINGR
	case CState::StandingR:
		//setProperAnim

		if (velocity.x == 0 && velocity.y == 0) currentState = CState::StandingR;
		//Walk
		else if (velocity.x > 0 && velocity.y == 0) currentState = CState::WalkR;
		else if (velocity.x < 0 && velocity.y == 0) currentState = CState::WalkL;

		//Jump
		else if (velocity.y < 0)
		{
			currentState = CState::JumpingR;
			flags.onGround = false;
		}

		break;
	
	//STANDINGL
	case CState::StandingL:
		//setProperAnim

		if (velocity.x == 0 && velocity.y == 0) currentState = CState::StandingL;
		//Walk
		else if (velocity.x > 0 && velocity.y == 0) currentState = CState::WalkR;
		else if (velocity.x < 0 && velocity.y == 0) currentState = CState::WalkL;

		//Jump
		else if (velocity.y < 0)
		{
			currentState = CState::JumpingL;
			flags.onGround = false;
		}

		break;

	//WALKR
	case CState::WalkR:

		if ((velocity.x > 0 && velocity.x < baseStats.walkSpeed) && velocity.y == 0) currentState = CState::WalkR;

		//Walk/Stand
		else if (velocity.x == 0 && velocity.y == 0) currentState = CState::StandingR;
		else if (velocity.x < 0 && velocity.y == 0) currentState = CState::WalkL;

		//Run
		else if (velocity.x > baseStats.walkSpeed) currentState = CState::RunR;

		//Jump
		else if (velocity.y < 0)
		{
			currentState = CState::JumpingR;
			flags.onGround = false;
		}

		break;

	//WALKL
	case CState::WalkL:

		if ((velocity.x < 0 && velocity.x >= -baseStats.walkSpeed) && velocity.y == 0) currentState = CState::WalkL;

		//Walk/Stand
		else if (velocity.x == 0 && velocity.y == 0) currentState = CState::StandingL;
		else if (velocity.x > 0 && velocity.y == 0) currentState = CState::WalkR;

		//Run
		else if (velocity.x < -baseStats.walkSpeed) currentState = CState::RunL;

		//Jump
		else if (velocity.y < 0)
		{
			currentState = CState::JumpingL;
			flags.onGround = false;
		}

		break;

	//RUNS
	case CState::RunL:

		if ((velocity.x < -baseStats.walkSpeed && velocity.x >= -baseStats.runSpeed) && velocity.y == 0) currentState = CState::RunL;

		else if (velocity.x < -baseStats.runSpeed && velocity.y == 0) currentState = CState::DashL;
		else if (velocity.x >= -baseStats.walkSpeed && velocity.y == 0) currentState = CState::WalkL;

		//Jump
		else if (velocity.y < 0)
		{
			currentState = CState::JumpingL;
			flags.onGround = false;
		}
		
		break;

	case CState::RunR:

		if ((velocity.x > baseStats.walkSpeed && velocity.x <= baseStats.runSpeed) && velocity.y == 0) currentState = CState::RunR;

		else if (velocity.x > baseStats.runSpeed && velocity.y == 0) currentState = CState::DashR;
		else if (velocity.x <= baseStats.walkSpeed && velocity.y == 0) currentState = CState::WalkR;

		//Jump
		else if (velocity.y < 0)
		{
			currentState = CState::JumpingR;
			flags.onGround = false;
		}

		break;

	//Dashes
	case CState::DashL:

		if (velocity.x <= -baseStats.dashSpeed && velocity.y == 0) currentState = CState::DashL;
		
		else if (velocity.x > -baseStats.dashSpeed && velocity.y == 0) currentState = CState::RunL;

		//DashJump
		else if (velocity.y < 0)
		{
			currentState = CState::DashJumpL;
			flags.onGround = false;
		}

		break;

	case CState::DashR:

		if (velocity.x > baseStats.dashSpeed && velocity.y == 0) currentState = CState::DashR;

		else if (velocity.x <= baseStats.dashSpeed && velocity.y == 0) currentState = CState::RunR;

		//DashJump
		else if (velocity.y < 0)
		{
			currentState = CState::DashJumpR;
			flags.onGround = false;
		}

		break;
	
	//JUMPS

	case CState::JumpingL:

		if (velocity.y < 0) currentState = CState::JumpingL;

		else if (velocity.y > 0) currentState = CState::DivingL;

		break;

	case CState::JumpingR:

		if (velocity.y < 0) currentState = CState::JumpingR;

		else if (velocity.y > 0) currentState = CState::DivingR;

		break;

	case CState::DashJumpL:

		if (velocity.y < 0) currentState = CState::DashJumpL;

		else if (velocity.y > 0) currentState = CState::DashDiveL;

		break;

	case CState::DashJumpR:

		if (velocity.y < 0) currentState = CState::DashJumpR;

		else if (velocity.y > 0) currentState = CState::DashDiveR;

		break;

	//DIVING
	case CState::DivingL:

		if (!flags.onGround) currentState = CState::DivingL;
		else currentState = CState::StandingL;
		break;

	case CState::DivingR:

		if (!flags.onGround) currentState = CState::DivingR;
		else currentState = CState::StandingR;
		break;

	case CState::DashDiveL:

		if (!flags.onGround) currentState = CState::DashDiveL;
		else currentState = CState::StandingL;
		break;

	case CState::DashDiveR:

		if (!flags.onGround) currentState = CState::DashDiveR;
		else currentState = CState::StandingR;
		break;
	}
}

void Character_Candy::update(float dt)
{
	setHitboxes();
	processStates();

	float oldVy = velocity.y;
	if (!flags.onGround)
	{
		velocity.y = oldVy + 1000*dt;	//TODO refactor
	}
	else if(currentState != CState::JumpingL && currentState != CState::JumpingR && currentState != CState::DashJumpL && currentState != CState::DashJumpR)
	{
		velocity.y = 0;
	}
	setPosition(sf::Vector2f(Position.x + velocity.x*dt, Position.y + velocity.y*dt));

	//SETPOSITION
	getSprite().setPosition(Position);
	
	//DRAW
	draw();
}

Character_Candy::Character_Candy()
{
	setBaseStats("Candy",1250,1);
	setPosition(sf::Vector2f(50, 40*16));
	getSprite().setTexture(Resource_Holder::get().getTexture(Texture_Name::test1));
	//getSprite().setColor(sf::Color::Green);
	setSize({ 16,32 });
	getSprite().setScale(
		getSize().x / getSprite().getLocalBounds().width,
		getSize().y / getSprite().getLocalBounds().height
	);
}
