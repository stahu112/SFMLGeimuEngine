#pragma once

#include "Game_State.h"
#include "../Display.h"
#include "../Application.h"
#include "../Animation.h"

namespace State
{
	class Playing : public Game_State
	{
	public:
		Playing(Application& application);

		void input() override;
		void update(float dt) override;
		void draw() override;

	private:

		sf::RectangleShape shape;

		sf::Sound sound;
		Animation walkAnimation;
	};
}