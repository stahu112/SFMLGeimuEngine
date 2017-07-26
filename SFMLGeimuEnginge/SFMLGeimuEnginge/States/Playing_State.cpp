#include "Playing_State.h"

#include <iostream>

namespace State
{

	Playing::Playing(Application & application)
		: Game_State(application)
	{}

	void Playing::input()
	{
	}

	void Playing::update(float dt)
	{
	}

	void Playing::draw()
	{
		std::cout << "playing State";;
	}

}