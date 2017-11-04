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

		sf::View view = sf::View(sf::Vector2f(Display::screenSize.x/2, Display::screenSize.y/2), Display::screenSize);

		std::vector<sf::Text> opt;
		sf::Text title = sf::Text("THE BREAKERS", Resource_Holder::get().getFont(Font_Name::Powerfull), 140);

		sf::Font font;

		short int choice = 0, q;
		std::string vol;
		float fs;

		enum class men
		{
			main,
			options,
			load
		};

		men currMenu = men::main;

		bool once = false;

		sf::Music * music;

	public:
		Menu(Application& application);

		void assignBackgroundTex(Texture_Name name);
		void updateAnim();

		void reInit() override;
		void initState() override;
		void input() override;
		void update(float dt) override;
		void draw() override;

		void process();

		void highlight();

	private:
	};
}
