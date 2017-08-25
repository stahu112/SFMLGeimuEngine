#pragma once

#include "Character.h"

class Character_Candy : public Character
{

	struct uniqueStats
	{

	};

	enum class CState
	{

	};

	CState currentState;

public:

	void handleInput() override;
	
	void processStates() override;
	
	void update(float dt) override;

	Character_Candy();
	
};
