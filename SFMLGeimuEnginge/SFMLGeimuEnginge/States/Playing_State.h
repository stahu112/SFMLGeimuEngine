#pragma once

//STATE PLAYING

#include "Game_State.h"
#include "../Display.h"
#include "../Application.h"
#include "../Animation.h"
#include "../Character.h"

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
		//Dodawac obiekty

		Character player;
		sf::Music music;
	};
}