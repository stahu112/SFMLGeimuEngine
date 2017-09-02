#include "Physics.h"
#include "Game_Object.h"

float Physics::gravity = 10.f;
float Physics::drag = 0.f;

float Physics::maxYVelocity = 300.f;

//TODO Liczyc predkosc graniczna

void Physics::applyGravity(Game_Object & obj, float dt)
{

	if (obj.getVelocity().y <= maxYVelocity)
		obj.getVelocity().y += ((gravity * obj.getMass()) - (drag * obj.getMass())) *dt;
	else
		obj.getVelocity().y = maxYVelocity;
}

Physics::Physics()
{
}
