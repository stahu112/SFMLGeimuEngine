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

}
