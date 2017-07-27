#pragma once

#include <SFML/Graphics.hpp>

namespace Display
{
	void init();

	void clear();
	void display();
	void draw(sf::Drawable& drawable);

	void checkWindowEvents();

	bool isOpen();

	const sf::Vector2u screenSize(1280, 720);
	const std::string title = "SFMLGeimu";
}

