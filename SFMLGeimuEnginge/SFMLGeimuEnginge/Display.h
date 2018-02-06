#pragma once

#include <SFML/Graphics.hpp>
#include "InputHandler.h"


constexpr float boxRatio = 32.f; //32px == 1m

static float timeScale = 1.f;

namespace Display
{

	static std::vector<sf::Vector2f> resolutions;

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

	static sf::Vector2f screenSize = { 1920, 1080 };
	const std::string title = "Jakies cos";
}