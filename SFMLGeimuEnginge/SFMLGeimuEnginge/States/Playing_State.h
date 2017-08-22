#pragma once

//STATE PLAYING

#include "Game_State.h"
#include "../Display.h"
#include "../Application.h"
#include "../Animation.h"
#include "../Character.h"

#include <map>

namespace State
{
	class Playing : public Game_State
	{

		enum class LevelID
		{
			level0
		};

		//TODO Levele jak splashe przy splash screen state
		class Level
		{
		public:
			int test;
		};

	public:
		Playing(Application& application);

		void initState() override;
		void input() override;
		void update(float dt) override;
		void draw() override;
		void changeLevel(LevelID level);
		void processLevel();

	private:
		std::map<LevelID, Level> m_levels;
		Level * currentLevel;

		Character chara;

	};
}