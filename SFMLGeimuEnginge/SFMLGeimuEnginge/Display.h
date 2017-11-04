#pragma once

#include <SFML/Graphics.hpp>
#include "InputHandler.h"
#include "Physics.h"

namespace Display
{

	void init();
	void setFull(bool full);

	void clear();
	void display();
	void draw(sf::Drawable& drawable);

	void setView(sf::View& view);
	const sf::View getView();

	void checkWindowEvents();

	bool isOpen();
	bool pollEvents(sf::Event e);

	const sf::Vector2f screenSize(1920, 1080);
	const std::string title = "Jakies cos";
}