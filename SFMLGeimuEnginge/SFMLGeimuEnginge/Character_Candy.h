#pragma once

#include "Character.h"
#include "Animation.h"

class Character_Candy : public Character
{
	struct Flags
	{
		bool onGround = true;
	};

	struct UniqueStats
	{

	};

	enum class AnimationID
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

	std::map<AnimationID, Animation> m_animations;

public:

	UniqueStats getUniqueStats() const;
	//void setUniqueStats(); TODO setUniqueStats

	void handleInput() override;
	
	void processStates() override;
	
	void update(float dt) override;

	Character_Candy();

	//Commands
	void jump();
	void jump(float vel);

	void walkL();
	void walkR();
	void runL();
	void runR();
};
