#include "Display.h"

#include <memory>

namespace Display
{

	std::unique_ptr<sf::RenderWindow> window;

	void init()
	{
		window = std::make_unique<sf::RenderWindow>(sf::VideoMode(screenSize.x, screenSize.y), title);
	}

	void clear()
	{
		window->clear();
	}

	void display()
	{
		window->display();
	}

	void checkWindowEvents()
	{
		sf::Event e;

		while (window->pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				window->close();
			}
		}
	}

	bool isOpen()
	{
		return window->isOpen();
	}

	void draw(sf::Drawable& drawable)
	{
		window->draw(drawable);
	}
}