#pragma once

#include <SFML\Graphics.hpp>

class Character;

class Input_Handler
{
	Character * characterHandle;

public:


	Input_Handler();

	void setHandle(Character chara);

	void HandleInput();
};

