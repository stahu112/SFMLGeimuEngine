#pragma once

#include "Character.h"
#include "Animation.h"
#include "Res\Resource_Holder.h"

class Character_Candy : public Character
{

	enum class AnimationID
	{
		RunR,
		RunL,
		Idle
	};

	Animation * currentAnim = nullptr;

	std::map<AnimationID, Animation> m_animations;

public:
	
	void update(float dt) override;

	void setCurrentAnim(AnimationID id);

	void updateAnim();

	Character_Candy();

};
