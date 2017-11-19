#include "MyColCallback.h"
#include <iostream>


void MyColCallback::BeginContact(b2Contact * contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
	void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();

	if ( (int)fixtureUserDataA == 3)
	{
		state->getPlayer()->onGround = true;
		state->getPlayer()->goalVelocity.x = 0;
	}
	if ((int)fixtureUserDataB == 3)
	{
		state->getPlayer()->onGround = true;
		state->getPlayer()->goalVelocity.x = 0;
	}

	if ((int)fixtureUserDataA == 1)
	{
		if(!state->getPlayer()->onGround) state->getPlayer()->wallR = true;
	}
	if ((int)fixtureUserDataB == 1)
	{
		if (!state->getPlayer()->onGround) state->getPlayer()->wallR = true;
	}

	if ((int)fixtureUserDataA == 2)
	{
		if (!state->getPlayer()->onGround) state->getPlayer()->wallL = true;
	}
	if ((int)fixtureUserDataB == 2)
	{
		if (!state->getPlayer()->onGround) state->getPlayer()->wallL = true;
	}

}

void MyColCallback::EndContact(b2Contact * contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
	void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();

	if ((int)fixtureUserDataA == 3)
	{
		state->getPlayer()->onGround = false;
	}
	if ((int)fixtureUserDataB == 3)
	{
		state->getPlayer()->onGround = false;
	}

	if ((int)fixtureUserDataA == 1)
	{
		state->getPlayer()->wallDone = false;
		state->getPlayer()->wallR = false;
	}
	 if ((int)fixtureUserDataB == 1)
	{
		state->getPlayer()->wallR = false;
		state->getPlayer()->wallDone = false;
	}

	if ((int)fixtureUserDataA == 2)
	{
		state->getPlayer()->wallL = false;
		state->getPlayer()->wallDone = false;
	}
	if ((int)fixtureUserDataB == 2)
	{
		state->getPlayer()->wallL = false;
		state->getPlayer()->wallDone = false;
	}

}
