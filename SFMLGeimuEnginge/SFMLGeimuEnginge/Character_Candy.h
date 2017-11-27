#pragma once

#include "Character.h"
#include "Animation.h"
#include "Res\Resource_Holder.h"

class Character_Candy : public Character
{
public:

private:

	enum class CState
	{
		RunR,
		RunL,
		Idle,
		Jump,
		Dive,
		Slide,
		Crouch,
		Catapult,
		WallJumpR,
		WallJumpL
	};

	enum class AnimationID
	{
		RunR,
		RunL,
		Idle,
		Jump,
		Dive,
		Slide
	};

	float force = 0, force1 = 0;
	float velChange = 0;
	b2Vec2 vel = { 0, 0 };

	Animation * animation = nullptr;
	AnimationID currentAnim = AnimationID::Idle;

	CState currentState = CState::Idle;

	b2Body* body;

	std::map<AnimationID, Animation> m_animations;

public:

	void input(float dt);

	void update(float dt) override;
	void processStates(float dt) override;

	void setCurrentAnim();
	void changeAnim(AnimationID anim);

	void updateAnim();

	//Inicjuj animacje, stworz cialo fizyczne itd
	void createRigidBody();
	void initAnimations();

	void addAnimations(AnimationID id, Animation & animation);

	Character_Candy(State::Playing & state);

	//Commands
	void jump();

	void wallJump(float dt);

	void pullUp(float dt);
};
