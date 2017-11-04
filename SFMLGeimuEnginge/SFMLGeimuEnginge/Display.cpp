#include "Display.h"

#include <iostream>
#include <memory>

#include <fstream>

bool showFPS, fullON, vsyncON;

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
			bool _s, _f, _v;

			config >> _f >> _s >> _v;

			showFPS = _s;
			fullON = _f;
			vsyncON = _v;

			config.close();
		}
		else
		{
			std::cout << "Chujnia\n";
			config.close();

			showFPS = false;
			vsyncON = false;
			fullON = false;
		}

		if(fullON) window = std::make_unique<sf::RenderWindow>(sf::VideoMode((int)screenSize.x, (int)screenSize.y), title, sf::Style::Fullscreen);
		else window = std::make_unique<sf::RenderWindow>(sf::VideoMode((int)screenSize.x, (int)screenSize.y), title, sf::Style::Default);

		//Ograniczenie fps do 60 metoda okna z biblioteki SFML
		window->setFramerateLimit(60);

		setVsync(vsyncON);

		window->setMouseCursorVisible(false);

		window->setKeyRepeatEnabled(false);

		window->setJoystickThreshold(1);
	}

	void setFull(bool full)
	{
		window->close();
		if (full) { window->create(sf::VideoMode(1920, 1080), title, sf::Style::Fullscreen); fullON = true; }
		else { window->create(sf::VideoMode(1920, 1080), title, sf::Style::Default);  fullON = false; }
	}

	void setVsync(bool vsync)
	{
		if (vsync) { window->setVerticalSyncEnabled(true); vsyncON = true; }
		else { window->setVerticalSyncEnabled(false); vsyncON = false; }
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