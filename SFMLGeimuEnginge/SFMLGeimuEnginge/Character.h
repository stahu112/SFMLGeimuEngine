#pragma once

#include "Game_Object.h"
#include "Display.h"

namespace State { class Playing; };

class Character : public Game_Object
{
	
protected:

	struct Flags
	{
		bool inAir = true;
		bool staggered = false;
	};

	struct BaseStats
	{
		std::string ID = "Xamindar";
		unsigned BaseHP = 1000;

		int dashFactor = 600;
		int walkFactor = 70;
		int jumpFactor = 170;
	};

	BaseStats baseStats;
	Flags flags;

	sf::Sprite spriteSheet;

public:

	sf::Sprite & getSprite();

	//Stuff
	Flags & getFlags();

	BaseStats getBaseStats() const;
	void setBaseStats(std::string ID, unsigned BaseHP, unsigned Level);

	//Physics Component

	void draw();

	virtual void update(float dt) = 0;

	Character();

};

