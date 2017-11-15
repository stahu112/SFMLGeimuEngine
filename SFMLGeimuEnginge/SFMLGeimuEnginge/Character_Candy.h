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
		Catapult
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

	Animation * animation = nullptr;
	AnimationID currentAnim = AnimationID::Idle;

	CState currentState = CState::Idle;

	b2Body* body;

	std::map<AnimationID, Animation> m_animations;

	bool onGround = true, slide = false, crouch = false;

public:

	void input();

	void update(float dt) override;
	void processStates() override;

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
	void catapult();
};
