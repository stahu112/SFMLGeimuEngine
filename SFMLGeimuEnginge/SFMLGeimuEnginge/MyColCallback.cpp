#include "MyColCallback.h"
#include <iostream>


void MyColCallback::BeginContact(b2Contact * contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
	void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();

	//ONGROUND
	if ( (int)fixtureUserDataA == 3)
	{
		//state->getPlayer()->onGround = true;
		//state->getPlayer()->falling = false;
		state->getPlayer()->numContacts++;
	}
	if ((int)fixtureUserDataB == 3)
	{
		//state->getPlayer()->onGround = true;
		//state->getPlayer()->falling = false;
		state->getPlayer()->numContacts++;
	}

	///////////////////////////////////////////////////////

	//WALLJUMP
	if ((int)fixtureUserDataA == 1)
	{
		state->getPlayer()->numWallRContacts++;
	}
	if ((int)fixtureUserDataB == 1)
	{
		state->getPlayer()->numWallRContacts++;
	}

	if ((int)fixtureUserDataA == 2)
	{
		state->getPlayer()->numWallLContacts++;
		state->getPlayer()->force *= -1;
	}
	if ((int)fixtureUserDataB == 2)
	{
		state->getPlayer()->numWallLContacts++;
		state->getPlayer()->force *= -1;
	}

}

void MyColCallback::EndContact(b2Contact * contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
	void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();


	//ONGROUND
	if ((int)fixtureUserDataA == 3)
	{
		//state->getPlayer()->onGround = false;
		state->getPlayer()->numContacts--;
	}
	if ((int)fixtureUserDataB == 3)
	{
		//state->getPlayer()->onGround = false;
		state->getPlayer()->numContacts--;
	}
	

	///////////////////////////////////////////////////////

	//WALLJUMP
	if ((int)fixtureUserDataA == 1)
	{
		state->getPlayer()->numWallRContacts--;
	}
	 if ((int)fixtureUserDataB == 1)
	{
		state->getPlayer()->numWallRContacts--;
	}

	if ((int)fixtureUserDataA == 2)
	{
		state->getPlayer()->numWallLContacts--;
		state->getPlayer()->force *= -1;
	}
	if ((int)fixtureUserDataB == 2)
	{
		state->getPlayer()->numWallLContacts--;
		state->getPlayer()->force *= -1;
	}

}
