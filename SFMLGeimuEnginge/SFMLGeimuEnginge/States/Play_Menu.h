#pragma once
#include "Game_State.h"
#include "../Display.h"
#include "../Application.h"

namespace State
{

	class Play_Menu : public Game_State
	{

		sf::Sprite background;

		bool isAnimated = false;
		Animation backgroundAnimation;
		sf::Text pauseText;

		sf::View view = sf::View(sf::Vector2f(Display::screenSize.x / 2, Display::screenSize.y / 2), Display::screenSize);

	public:

		void updateAnim();

		void reInit() override;
		void initState() override;
		void input() override;
		void update(float dt) override;
		void draw() override;

		Play_Menu(Application& application);
		~Play_Menu();
		void assignBackgroundTex(Texture_Name name);
	};

};