#pragma once

#include "Game_Object.h"
#include "Display.h"

namespace State { class Playing; };

class Character : public Game_Object
{
	
	struct Flags
	{
		bool onGround = true;
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

private:
	sf::Sprite spriteSheet;
	sf::Vector2f velocity = {0,0};

public:

	//Sets HITBOX in characters position, with or without new size
	//Returns baseHitbox

	sf::Sprite & getSprite();
	
	//Stuff
	Flags & getFlags();

	BaseStats getBaseStats() const;
	void setBaseStats(std::string ID, unsigned BaseHP, unsigned Level);

	void setVelocity(sf::Vector2f newVel);
	sf::Vector2f & getVelocity();

	//Physics Component

	//Input Component
	virtual void handleInput() = 0;

	//State manager
	virtual void processStates() = 0;

	void draw();

	virtual void update(float dt);

	Character();

	void resetX();
	void resetY();

	//Commands
	void jump();
	
	void walkL();
	void walkR();
	
	void runL();
	void runR();


};

