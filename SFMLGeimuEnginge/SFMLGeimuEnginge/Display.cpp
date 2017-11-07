#include "Display.h"

#include <iostream>
#include <memory>
#include "SFMLDebugDraw.h"
#include <fstream>

int showFPS, fullON, globalVolume;

//Przestrzen nazw dla okna
namespace Display
{
	//Wskaznik do okna
	std::unique_ptr<sf::RenderWindow> window;

	std::fstream config;

	//Stworz okno
	void init()
	{
		config.open("config.txt", std::ios::in);
	
		if (config.good())
		{
			int _s, _f, _v;

			config >> _f >> _s >> _v;

			showFPS = _s;
			fullON = _f;
			globalVolume = _v;

			config.close();
		}
		else
		{
			std::cout << "Brak configu, domyslne\n";
			config.close();

			globalVolume = 50;
			showFPS = 0;
			fullON = 0;
		}

		if(fullON) window = std::make_unique<sf::RenderWindow>(sf::VideoMode((int)screenSize.x, (int)screenSize.y), title, sf::Style::Fullscreen);
		else window = std::make_unique<sf::RenderWindow>(sf::VideoMode((int)screenSize.x, (int)screenSize.y), title, sf::Style::Default);

		//Ograniczenie fps do 60 metoda okna z biblioteki SFML
		window->setFramerateLimit(60);

		window->setMouseCursorVisible(false);

		window->setKeyRepeatEnabled(false);

		window->setJoystickThreshold(1);

	}

	void setFull(bool full)
	{
		window->close();
		if (full) { window->create(sf::VideoMode(1920, 1080), title, sf::Style::Fullscreen); fullON = 1; }
		else { window->create(sf::VideoMode(1920, 1080), title, sf::Style::Default);  fullON = 0; }
	}

	//Czysc okno
	void clear()
	{
		window->clear(sf::Color(0,0,0,255));
	}

	//Wyswietl rzeczy
	void display()
	{
		window->display();
	}

	bool pollEvents(sf::Event e)
	{
		return window->pollEvent(e);
	}

	//Sprawdz eventy
	void checkWindowEvents()
	{
		sf::Event e;
		while (window->pollEvent(e))
		{
			InputHandler::updateInput(e);
			//Jesli event = proba zamkniecia okna to zamknij
			//TODO komunikat czy chcesz zamknac, jakis zapis save'a itp.
			if (e.type == sf::Event::Closed)
			{
				window->close();
			}
		}
	}
	
	//Czy okno jest otwarte
	bool isOpen()
	{
		return window->isOpen();
	}

	//Rysuj rzeczy
	void draw(sf::Drawable& drawable)
	{
		window->draw(drawable);
	}

	void setView(sf::View& view)
	{
		window->setView(view);
	}
	const sf::View getView()
	{
		return window->getView();
	}
}