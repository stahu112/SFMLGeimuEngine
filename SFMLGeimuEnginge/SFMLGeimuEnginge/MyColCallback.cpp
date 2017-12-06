#include "MyColCallback.h"
#include <iostream>


void MyColCallback::BeginContact(b2Contact * contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
	void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();

	//ONGROUND
	if ( fixtureUserDataA == "GroundSensor")
	{
		//state->getPlayer()->onGround = true;
		//state->getPlayer()->falling = false;
		state->getPlayer()->numContacts++;
	}
	if (fixtureUserDataB == "GroundSensor")
	{
		//state->getPlayer()->onGround = true;
		//state->getPlayer()->falling = false;
		state->getPlayer()->numContacts++;
	}

	///////////////////////////////////////////////////////

	//WALLJUMP
	if (fixtureUserDataA == "WallR")
	{
		state->getPlayer()->numWallRContacts++;
	}
	if (fixtureUserDataB == "WallR")
	{
		state->getPlayer()->numWallRContacts++;
	}

	if (fixtureUserDataA == "WallL")
	{
		state->getPlayer()->numWallLContacts++;
	}
	if (fixtureUserDataB == "WallL")
	{
		state->getPlayer()->numWallLContacts++;
	}

}

void MyColCallback::EndContact(b2Contact * contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
	void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();


	//ONGROUND
	if (fixtureUserDataA == "GroundSensor")
	{
		//state->getPlayer()->onGround = false;
		state->getPlayer()->numContacts--;
	}
	if (fixtureUserDataB == "GroundSensor")
	{
		//state->getPlayer()->onGround = false;
		state->getPlayer()->numContacts--;
	}
	

	///////////////////////////////////////////////////////

	//WALLJUMP
	if (fixtureUserDataA == "WallR")
	{
		state->getPlayer()->numWallRContacts--;
	}
	 if (fixtureUserDataB == "WallR")
	{
		state->getPlayer()->numWallRContacts--;
	}

	if (fixtureUserDataA == "WallL")
	{
		state->getPlayer()->numWallLContacts--;
	}
	if (fixtureUserDataB == "WallL")
	{
		state->getPlayer()->numWallLContacts--;
	}

}
