//Aplikacja

#include "Application.h"

extern int showFPS, fullON;

//Konstruktor
Application::Application()
{
	//Inicjuj okno
	Display::init();
	//Wrzuc STATE SPLASH na stos STATE'OW
	pushState(std::make_unique<State::Splash_Screen>(*this));
}

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

		float fps = 1.f / dt.asSeconds();

		sf::Text fpst;
		fpst.setString(std::to_string((int)fps));
		fpst.setFont(Resource_Holder::get().getFont(Font_Name::Powerfull));
		fpst.setColor(sf::Color::Red);
		fpst.setScale(0.25, 0.25);
		fpst.setOrigin(fpst.getLocalBounds().width, 0);
		fpst.setPosition(sf::Vector2f(Display::getView().getSize().x / 2 + Display::getView().getCenter().x, 0));

		//EVENTY
		Display::checkWindowEvents();

		//Wyczysc okno, domyslnie na czarno
		Display::clear();

		//Wywolaj funkcje ze STATE'a
		m_states.top()->input();		//Sterowanie itp.
		m_states.top()->update(dt.asSeconds());	//Aktualizuj stany obiektow
		m_states.top()->draw();			//Rysuj obiekty

		if (!InputHandler::down) InputHandler::key = sf::Keyboard::Unknown;
		if (!InputHandler::jDown) InputHandler::jKey = -1;

		if (showFPS) Display::draw(fpst);

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
	returnState();
}

//Wyrzuc poprzedni STATE i wrzuc nowy na stos
void Application::changeState(std::unique_ptr<State::Game_State> state)
{
	m_states.pop();
	m_states.push(std::move(state));
}

void Application::returnState()
{
	m_states.top()->reInit();
}
