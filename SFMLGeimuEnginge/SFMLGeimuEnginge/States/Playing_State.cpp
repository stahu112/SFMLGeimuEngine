#include "Playing_State.h"

#include <iostream>

namespace State
{

	Playing::Playing(Application & application)
		: Game_State(application)
	{
		shape.setSize(sf::Vector2f(200, 200));

		shape.setTexture(&Resource_Holder::get().getTexture(Texture_Name::slime));

		walkAnimation.addFrames({ 0,0,50,50 }, 0.1);
		walkAnimation.addFrames({ 50,0,50,50 }, 0.1);
		walkAnimation.addFrames({ 100,0,50,50 }, 0.1);
		walkAnimation.addFrames({ 150,0,50,50 }, 0.1);
		walkAnimation.addFrames({ 200,0,50,50 }, 0.1);
	}

	void Playing::input()
	{
	
	}

	void Playing::update(float dt)
	{
		shape.setTextureRect(walkAnimation.getFrame());
	}

	void Playing::draw()
	{
		Display::draw(shape);
	}

}