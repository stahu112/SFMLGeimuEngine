#pragma once

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Res\Resource_Holder.h"
#include "Display.h"

enum Input
{
	press1,
	press2,
	press3,
	press4,
	//######
	pressLB,
	pressRB,
	pressLT,
	pressRT,
	//######
	pressUP,
	pressDOWN,
	pressLEFT,
	pressRIGHT,
	//#######
};

enum Character_State
{
	Idle,
	WalkRight,
	WalkLeft,
	RunRight,
	RunLeft,
	BreakRight,
	BreakLefit,
	DashRight,
	DashLeft,
	Falling,
	HangingRight,
	HangingLeft,
	PullingURight,
	PullingULeft,
	PullingDRight,
	PullingDLeft,
	Jumping,
	JumpingRight,
	JumpingLeft
};

enum Stance
{
	FullCalm,
	MidCalm,
	LowCalm,
	FullFight,
	MidFight,
	LowFight
};

class Character
{
private:

	sf::Vector2f pos;

	sf::Vector2f velocity;

public:
	Character();

	sf::RectangleShape shape;

	void update(float dt);

	const sf::Vector2f& getPos() const;
	void setPos(float x, float y);
	Input ProcessInput();

	Animation walkAnimation;
	Character_State m_state = Idle;
	Stance m_stance = FullCalm;
};

