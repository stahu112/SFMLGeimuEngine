#include "Character.h"

#include <iostream>


Character::Character()
{
	velocity.x = 0;
	velocity.y = 0;
	shape.setSize(sf::Vector2f(256, 256));
	shape.setTexture(&Resource_Holder::get().getTexture(Texture_Name::animtest));

	walkAnimation.addFrames({ 0,0,115,137 }, 0.1f);
	walkAnimation.addFrames({ 115,0,115,137 }, 0.1f);
	walkAnimation.addFrames({ 115*2,0,115,137 }, 0.1f);
	walkAnimation.addFrames({ 115*3,0,115,137 }, 0.1f);
	walkAnimation.addFrames({ 115*4,0,115,137 }, 0.1f);
	walkAnimation.addFrames({ 115*5,0,115,137 }, 0.1f);
	walkAnimation.addFrames({ 115*6,0,115,137 }, 0.1f);
	walkAnimation.addFrames({ 115*7,0,115,137 }, 0.1f);
}

void Character::update(float dt)
{
	switch (m_state)
	{
	case Idle:
		if (ProcessInput() == pressUP)
		{
			m_state = Jumping;
		}
		break;
	case Character_State::Jumping:
		if (ProcessInput() == pressUP)
		{
			velocity.x = 100;
		}
		else
		{
			velocity.x = 0;
			m_state = Idle;
		}
	}

	pos.x += velocity.x*dt;
	shape.setPosition(pos);
}

const sf::Vector2f & Character::getPos() const
{
	return pos;
}

void Character::setPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

Input Character::ProcessInput()
{
	//TODO Dodac Pada 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) return Input::pressUP;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) return Input::pressDOWN;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) return Input::pressLEFT;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) return Input::pressRIGHT;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) return Input::press1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) return Input::press2;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) return Input::press3;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) return Input::press4;
}

