#pragma once

#include "Game_Object.h"
#include "Display.h"

namespace State { class Playing; };

enum class HitId
{
	H,
	L
};

enum class CharState
{
	StandingL,
	StandingR,
	WalkL,
	WalkR,
	RunL,
	RunR,
	JumpL,
	JumpR,
	DiveL,
	DiveR
};

class Character : public Game_Object
{
	
protected:

	struct Flags
	{
		bool walkToggle = true;
		unsigned JumpCount = 0;
		bool onGround = false;
		bool collidedPlat = false;
	};

	struct BaseStats
	{
		std::string ID = "Xamindar";
		unsigned BaseHP = 1;
		unsigned Level = 1;
		unsigned EXP = 0;
		unsigned Jumps = 1;

		int walkFactor = 50;
		int runFactor = 100;
		int jumpFactor = 170;
	};

	BaseStats baseStats;
	Flags flags;

	sf::FloatRect lowerHitbox;
	sf::FloatRect higherHitbox;

	sf::Sprite spriteSheet;

public:

	sf::FloatRect getHitbox(HitId box) const;
	void setHitboxes();

	sf::Sprite & getSprite();
	
	CharState currentState = CharState::DiveR;

	//Stuff
	Flags & getFlags();

	BaseStats getBaseStats() const;
	void setBaseStats(std::string ID, unsigned BaseHP, unsigned Level);

	//Physics Component

	void draw();

	virtual void update(float dt) = 0;
	virtual void processStates() = 0;

	Character();

	//Commands
	void jump();
	void jump(float d);
	
};

