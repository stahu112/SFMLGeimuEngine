#pragma once

#include <SFML/Graphics.hpp>

class Game_Object;

class Physics
{

	static float gravity;

	static float drag;

	static float maxYVelocity;

public:

	static void applyGravity(Game_Object & obj, float dt);

	static float approach(float goal, float current, float dt);

	Physics();
};
