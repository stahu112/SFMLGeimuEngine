#include "Display.h"

#include <iostream>
#include <memory>

//Przestrzen nazw dla okna
namespace Display
{
	//Wskaznik do okna
	std::unique_ptr<sf::RenderWindow> window;
	
	//Stworz okno
	void init()
	{
		//Tworz okno o nazwie "title" i wymiarach z wektora "screenSize" VECTOR Z BIBLIOTEKI SFML =/= VECTOR Z BIBLIOTEKI STL
		window = std::make_unique<sf::RenderWindow>(sf::VideoMode((int)screenSize.x, (int)screenSize.y), title, sf::Style::Close);

		//Ograniczenie fps do 60 metoda okna z biblioteki SFML
		window->setFramerateLimit(60);

		window->setKeyRepeatEnabled(false);

		window->setJoystickThreshold(1);
	}

	//Czysc okno
	void clear()
	{
		window->clear(sf::Color(255,255,255,255));
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
}