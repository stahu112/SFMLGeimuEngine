#pragma once

#include "Game_Object.h"
#include "Display.h"

namespace State { class Playing; };

enum class HitId
{
	L,
	H
};

enum class CState
{
	//Standing
	StandingL,
	StandingR,

	//Crouching
	CrouchingL,
	CrouchingR,

	//Walking, Running, Dashing
	WalkL,
	WalkR,
	RunL,
	RunR,
	DashL,
	DashR,

	//Jumping, Diving
	JumpingL,
	DivingL,
	JumpingR,
	DivingR,

	//DASHJUMP
	DashJumpL,
	DashJumpR,
	DashDiveL,
	DashDiveR
};

class Character : public Game_Object
{
	
protected:

	struct Flags
	{
		bool onGround = false;
	};

	struct BaseStats
	{
		std::string ID = "Xamindar";
		unsigned BaseHP = 1;
		unsigned Level = 1;
		unsigned EXP = 0;
	};

	BaseStats baseStats;
	Flags flags;

	sf::FloatRect lowerHitbox;
	sf::FloatRect higherHitbox;

	sf::Sprite spriteSheet;
	sf::Vector2f velocity = {0,0};

	CState currentState = CState::StandingR;

public:

	//Sets HITBOX in characters position, with or without new size
	//Returns baseHitbox

	CState getCurrentState();

	sf::FloatRect getHitbox(HitId box) const;
	void setHitboxes();

	sf::Sprite & getSprite();
	
	//Stuff
	Flags & getFlags();

	BaseStats getBaseStats() const;
	void setBaseStats(std::string ID, unsigned BaseHP, unsigned Level);

	void setVelocity(sf::Vector2f newVel);
	sf::Vector2f & getVelocity();

	//Physics Component

	//State manager
	virtual void processStates() = 0;

	void draw();

	virtual void update(float dt);

	Character();

	//Commands
	void jump();
	
	void walkL();
	void walkR();
	
	void runL();
	void runR();


};

