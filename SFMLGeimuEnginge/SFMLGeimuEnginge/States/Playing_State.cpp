#include "Playing_State.h"

#include <iostream>

namespace State
{

	Playing::Playing(Application & application)
		: Game_State(application)
	{
		shape.setSize(sf::Vector2f(200, 200));

		shape.setTexture(&Resource_Holder::get().getTexture(Texture_Name::test));
	}

	void Playing::input()
	{
	
	}

	void Playing::update(float dt)
	{
	
	}

	void Playing::draw()
	{
		Display::draw(shape);
	}

}