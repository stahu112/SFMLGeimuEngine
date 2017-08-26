#pragma once

#include "Game_State.h"
#include "../Display.h"
#include "../Application.h"
#include "../Animation.h"

namespace State
{
	class Menu : public Game_State
	{
	private:

		sf::RectangleShape backgroundTexture;
		Animation backgroundAnimation;

		bool isAnimated = false;

	public:
		Menu(Application& application);

		void assignBackgroundTex(Texture_Name name);
		void updateAnim();

		void initState() override;
		void input() override;
		void update(float dt) override;
		void draw() override;

	private:
	};
}
