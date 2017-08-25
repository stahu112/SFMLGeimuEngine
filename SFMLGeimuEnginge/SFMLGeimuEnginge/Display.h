#pragma once

#include <SFML/Graphics.hpp>

namespace Display
{
	void init();

	void clear();
	void display();
	void draw(sf::Drawable& drawable);

	void setView(sf::View& view);

	void checkWindowEvents();

	bool isOpen();

	const sf::Vector2f screenSize(1280, 720);
	const std::string title = "Najlepsza uber gra";
}

