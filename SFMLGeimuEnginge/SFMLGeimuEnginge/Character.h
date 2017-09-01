#pragma once

#include "Game_Object.h"
#include "Display.h"

namespace State { class Playing; };

enum class HitId
{
	H,
	L
};

class Character : public Game_Object
{
	
protected:

	struct Flags
	{
		
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

public:

	sf::FloatRect getHitbox(HitId box) const;
	void setHitboxes();

	sf::Sprite & getSprite();
	
	//Stuff
	Flags & getFlags();

	BaseStats getBaseStats() const;
	void setBaseStats(std::string ID, unsigned BaseHP, unsigned Level);

	//Physics Component

	void draw();

	virtual void update(float dt);

	Character();

	//Commands
	void jump();
	void jump(float d);
	
};

