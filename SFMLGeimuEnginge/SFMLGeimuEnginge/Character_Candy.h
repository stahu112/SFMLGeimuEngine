#pragma once

#include "Character.h"
#include "Animation.h"
#include "Res\Resource_Holder.h"

class Character_Candy : public Character
{

	struct UniqueStats
	{

	};

	enum class AnimationID
	{
		RunR,
		RunL
	};

	UniqueStats uniqueStats;

	Animation * currentAnim = nullptr;

	std::map<AnimationID, Animation> m_animations;

public:

	UniqueStats getUniqueStats() const;
	//void setUniqueStats(); TODO setUniqueStats
	
	void update(float dt) override;

	Character_Candy();

};
