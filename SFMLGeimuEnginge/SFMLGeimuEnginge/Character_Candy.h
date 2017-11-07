#pragma once

#include "Character.h"
#include "Animation.h"
#include "Res\Resource_Holder.h"

class Character_Candy : public Character
{
public:

private:

	enum class AnimationID
	{
		RunR,
		RunL,
		Idle,
		Jump,
		Dive
	};

	Animation * currentAnim = nullptr;

	b2Body* body;

	std::map<AnimationID, Animation> m_animations;

public:

	void update(float dt) override;

	void setCurrentAnim(AnimationID id);

	void updateAnim();

	Character_Candy(State::Playing & state);

};
