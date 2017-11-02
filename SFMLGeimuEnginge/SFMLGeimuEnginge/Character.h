#pragma once

#include "Game_Object.h"
#include "Display.h"

namespace State { class Playing; };

class Character : public Game_Object
{
	
protected:

	struct Flags
	{
		bool falling = true;
		bool jumping = false;
		bool standing = false;
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

	float top, bot, left, right;
	sf::Vector2f expPos;

	std::vector<sf::Vector2i> tiles;
	sf::Vector2i topLeft, topRight, Right, Left, botLeft, botRight;

	bool appGr = true;

	sf::Vector2f goalVelocity;

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

