#include "Playing_State.h"

#include <iostream>

namespace State
{

	Playing::Playing(Application & application)
		: Game_State(application)
	{
		shape.setSize(sf::Vector2f(200, 200));

		shape.setTexture(&Resource_Holder::get().getTexture(Texture_Name::slime));

		sound.setBuffer(Resource_Holder::get().getSound(Sound_Name::yam));
		sound.play();

		walkAnimation.addFrames({ 0,0,50,50 }, 0.1);
		walkAnimation.addFrames({ 50,0,50,50 }, 0.1);
		walkAnimation.addFrames({ 100,0,50,50 }, 0.1);
		walkAnimation.addFrames({ 150,0,50,50 }, 0.1);
		walkAnimation.addFrames({ 200,0,50,50 }, 0.1);

		walkAnimation.addFrames({ 0,50,50,50 }, 0.1);
		walkAnimation.addFrames({ 50,50,50,50 }, 0.1);
		walkAnimation.addFrames({ 100,50,50,50 }, 0.1);
		walkAnimation.addFrames({ 150,50,50,50 }, 0.1);
		walkAnimation.addFrames({ 200,50,50,50 }, 0.1);
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