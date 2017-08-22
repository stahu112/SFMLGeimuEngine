#pragma once

//STATE PLAYING

#include "Game_State.h"
#include "../Display.h"
#include "../Application.h"
#include "../Animation.h"

#include <map>

namespace State
{
	class Playing : public Game_State
	{

		enum class LevelID
		{
			level0
		};

		//TODO Levels, like splashes on splash screen state
		class Level
		{
			
		};

	public:
		Playing(Application& application);

		void input() override;
		void update(float dt) override;
		void draw() override;

		void changeLevel(LevelID level);
		void processLevel();

		void addLevel(LevelID, );

	private:
		std::map<LevelID, Level> m_levels;
		Level * currentLevel;

	};
}