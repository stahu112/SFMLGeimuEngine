#pragma once

#include <SFML/Graphics.hpp>

class Game_Object;

class Physics
{

	static float gravity;

	static float drag;

public:

	static void applyGravity(Game_Object & obj, float dt);

	Physics();
};
