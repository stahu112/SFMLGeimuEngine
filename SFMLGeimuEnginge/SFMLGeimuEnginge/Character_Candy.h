#pragma once

#include "Character.h"

class Character_Candy : public Character
{
	struct Flags
	{
		bool onGround = true;
	};

	struct UniqueStats
	{
	};

	enum class CState
	{
		//Standing
		StandingL,
		StandingR,

		//Crouching
		CrouchingL,
		CrouchingR,

		//Walking, Running, Dashing
		WalkL,
		WalkR,
		RunL,
		RunR,
		DashL,
		DashR,

		//Jumping, Diving
		JumpingN,
		DivingN,
		JumpingL,
		DivingL,
		JumpingR,
		DivingR
	};

	UniqueStats uniqueStats;

	CState currentState;

public:

	void handleInput() override;
	
	void processStates() override;
	
	void update(float dt) override;

	Character_Candy();
	
};
