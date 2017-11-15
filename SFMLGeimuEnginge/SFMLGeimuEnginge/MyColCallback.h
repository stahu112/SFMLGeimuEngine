#pragma once

#include <Box2D\Box2D.h>

class MyColCallback : public b2ContactListener
{
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
};