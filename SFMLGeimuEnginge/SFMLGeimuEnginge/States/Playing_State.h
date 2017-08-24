#pragma once

//STATE PLAYING

#include "Game_State.h"
#include "../Display.h"
#include "../Application.h"
#include "../Animation.h"
#include "../Character.h"
#include "../Level.h"

#include <map>

namespace State
{
	class Playing : public Game_State
	{

	public:
		Playing(Application& application);

		void initState() override;
		
		void input() override;
		void update(float dt) override;
		void draw() override;
		
		//LEVELS
		void changeLevel(LevelID level);
		void processLevel();
		void addLevel();
		void addLevel(std::string& path);
		void initLevels();

	private:
		std::map<LevelID, Level> m_levels;
		Level * currentLevel = nullptr;

		Character chara;

	};
}