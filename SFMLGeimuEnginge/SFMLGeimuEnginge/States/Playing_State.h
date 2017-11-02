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

		void initState() override;
		Level * getCurrentLevel() const;
		Character * getPlayer() const;
		
		void input() override;
		void update(float dt) override;
		void draw() override;

		void resolveCollisions(float dt);
		
		//LEVELS
		void changeLevel(LevelID level);
		void updateLevel(float dt);
		void addLevel(LevelID id, Level level);
		void initLevels();

		//SET
		void setPlayer(Character* chara);
	
	private:

		std::map<LevelID, Level> m_levels;
		Level * currentLevel = nullptr;
		Character * player = nullptr;

	};
}