#pragma once

//STATE PLAYING


#include "Game_State.h"
#include "../Display.h"
#include "../Application.h"
#include "../Animation.h"
#include "../Character.h"
#include "../Level.h"
#include "../Character_Candy.h"

#include <map>

namespace State
{
	class Playing : public Game_State
	{

	public:
		Playing(Application& application);

		void reInit() override;
		void initState() override;
		Level * getCurrentLevel() const;
		Character * getPlayer() const;
		
		b2World * getWorld();

		void input() override;
		void update(float dt) override;
		void draw() override;

		//LEVELS
		void changeLevel(LevelID level);
		void updateLevel(float dt);
		void addLevel(LevelID id, Level level);
		void initLevels();

	private:

		b2World * world;
		std::map<LevelID, Level> m_levels;
		Level * currentLevel = nullptr;
		Character * player = nullptr;

	};
}