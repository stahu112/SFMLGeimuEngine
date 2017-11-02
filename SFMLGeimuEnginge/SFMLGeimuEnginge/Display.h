#pragma once

#include <SFML/Graphics.hpp>
#include "InputHandler.h"
#include "Physics.h"

constexpr bool isDEBUG = true;

namespace Display
{

	struct Settings
	{
		int screenX;
		int screenY;
		int fps;
	};

	void init();
	void reInit();

	void clear();
	void display();
	void draw(sf::Drawable& drawable);

	void setView(sf::View& view);

	void checkWindowEvents();

	bool isOpen();
	bool pollEvents(sf::Event e);

	const sf::Vector2f screenSize(1280, 720);
	const std::string title = "Jakies gowno cos";
}

