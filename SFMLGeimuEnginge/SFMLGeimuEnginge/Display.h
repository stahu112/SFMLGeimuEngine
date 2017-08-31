#pragma once

#include <SFML/Graphics.hpp>
#include "InputHandler.h"
#include "Collision.h"
#include "Physics.h"

namespace Display
{
	void init();

	void clear();
	void display();
	void draw(sf::Drawable& drawable);

	void setView(sf::View& view);

	void checkWindowEvents();

	bool isOpen();
	bool pollEvents(sf::Event e);

	const sf::Vector2f screenSize(1280, 720);
	const std::string title = "Najlepsza uber gra";
}

