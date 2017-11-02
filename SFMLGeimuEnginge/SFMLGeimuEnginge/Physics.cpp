#include "Physics.h"
#include "Game_Object.h"

float Physics::gravity = 10.f;
float Physics::drag = 0.f;

float Physics::maxYVelocity = 800.f;

//TODO Liczyc predkosc graniczna

void Physics::applyGravity(Game_Object & obj, float dt)
{

	if (obj.getVelocity().y <= maxYVelocity)
		obj.getVelocity().y += ((gravity * obj.getMass()) - (drag * obj.getMass())) *dt;
	else
		obj.getVelocity().y = maxYVelocity;
}

float Physics::approach(float goal, float current, float dt)
{

	dt *= 1150;

	float delta = goal - current;

	if (delta > dt) return current + dt;
	if (delta < -dt) return current - dt;

	return goal;
}

Physics::Physics()
{
}
