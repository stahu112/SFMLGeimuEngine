#pragma once

namespace Utils
{
	float approach(float goal, float current, float dt)
	{

		dt *= 100;

		float delta = goal - current;

		if (delta > dt) return current + dt;
		if (delta < -dt) return current - dt;

		return goal;
	}
};