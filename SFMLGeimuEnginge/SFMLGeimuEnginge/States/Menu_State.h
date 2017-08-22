#pragma once

#include "Game_State.h"
#include "../Display.h"
#include "../Application.h"
#include "../Animation.h"

namespace State
{
	class Menu : public Game_State
	{
	public:
		Menu(Application& application);

		void input() override;
		void update(float dt) override;
		void draw() override;

	private:
	};
}
