//Aplikacja

#include "Application.h"

//Konstruktor
Application::Application()
{
	//Inicjuj okno
	Display::init();
	//Wrzuc STATE SPLASH na stos STATE'OW
	pushState(std::make_unique<State::Splash_Screen>(*this));
}

//TODO Liczyc dt zeby gameplay byl niezalezny od framerate'u

//GLOWNA PETLA
void Application::runMainLoop()
{

	sf::Clock DeltaClock;
	sf::Clock GameClock;
	//Kiedy okno jest otwarte
	while (Display::isOpen())
	{
		sf::Time TimeSinceStart = GameClock.getElapsedTime();
		sf::Time dt = DeltaClock.restart();
		//Sprawdz EVENTY
		Display::checkWindowEvents();

		//Wyczysc okno, domyslnie na czarno
		Display::clear();

		//Wywolaj funkcje ze STATE'a
		m_states.top()->input();		//Sterowanie itp.
		m_states.top()->update(dt.asSeconds());	//Aktualizuj stany obiektow
		m_states.top()->draw();			//Rysuj obiekty

		Display::display();		//Wyswietl rzeczy
	}
}

//Wrzuc nowy STATE na stos
void Application::pushState(std::unique_ptr<State::Game_State> state)
{
	m_states.push(std::move(state));
}

//Wyrzuc STATE ze stosu
void Application::popState()
{
	m_states.pop();
}

//Wyrzuc poprzedni STATE i wrzuc nowy na stos
void Application::changeState(std::unique_ptr<State::Game_State> state)
{
	m_states.pop();
	m_states.push(std::move(state));
}
