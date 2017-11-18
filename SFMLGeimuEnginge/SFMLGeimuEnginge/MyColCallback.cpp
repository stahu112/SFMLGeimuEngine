#include "MyColCallback.h"
#include <iostream>


void MyColCallback::BeginContact(b2Contact * contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
	void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();

	std::cout << "Begin" << std::endl;

	if ( (int)fixtureUserDataA == 3)
	{
		state->getPlayer()->onGround = true;
	}
	if ((int)fixtureUserDataB == 3)
	{
		state->getPlayer()->onGround = true;
	}

}

void MyColCallback::EndContact(b2Contact * contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
	void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();

	std::cout << "End" << std::endl;

	if ((int)fixtureUserDataA == 3)
	{
		state->getPlayer()->onGround = false;
	}
	if ((int)fixtureUserDataB == 3)
	{
		state->getPlayer()->onGround = false;
	}

}
