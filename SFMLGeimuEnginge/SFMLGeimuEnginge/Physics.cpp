#include "Physics.h"
#include "Game_Object.h"

float Physics::gravity = 10.f;
float Physics::drag = 0.f;

//TODO Liczyc predkosc graniczna

void Physics::applyGravity(Game_Object & obj, float dt)
{
	obj.getVelocity().y += ( (gravity * obj.getMass()) - (drag * obj.getMass())) *dt;
}

Physics::Physics()
{
}


Physics::~Physics()
{
}
