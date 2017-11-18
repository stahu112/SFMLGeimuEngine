#pragma once

#include <Box2D\Box2D.h>
#include "ColFilters.h"

#include "States\Playing_State.h"

class MyColCallback : public b2ContactListener
{
public:

	State::Playing* state = nullptr;
private:

	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
};