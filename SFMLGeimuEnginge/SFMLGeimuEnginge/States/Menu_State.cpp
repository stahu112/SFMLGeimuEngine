#include "Menu_State.h"
#include "Playing_State.h"

namespace State
{
	Menu::Menu(Application & application)
		: Game_State(application)
	{
		initState();
	}

	void Menu::reInit()
	{
		music.play();
	}

	void Menu::initState()
	{

		music.openFromFile("Resources/Sound/hm.ogg");
		music.play();

		font = Resource_Holder::get().getFont(Font_Name::menuFont);

		title.setColor(sf::Color::Black);

		title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
		title.setPosition(sf::Vector2f(Display::screenSize.x/2, 200));

		backgroundTexture.setSize(Display::screenSize);
		assignBackgroundTex(Texture_Name::test1);

		opt.push_back(sf::Text("NEW GAME", font, 100));
		opt.push_back(sf::Text("LOAD", font, 100));
		opt.push_back(sf::Text("OPTIONS", font, 100));
		opt.push_back(sf::Text("QUIT", font, 100));

		for (int i = 0; i < opt.size(); i++)
		{
			opt[i].setColor(sf::Color(202,202,202,255));
			
			opt[i].setOrigin(opt[i].getLocalBounds().width / 2, opt[i].getLocalBounds().height / 2);

			opt[i].setPosition(sf::Vector2f(550, 500 + i*140));

		}

	}

	//##############
	void Menu::input()
	{
		
		if (InputHandler::checkUp(sf::Keyboard::Unknown)) once = false;

		if (choice < 0) choice = 0;
		if (choice > 3) choice = 3;

		if ((InputHandler::checkDown(sf::Keyboard::W) || InputHandler::checkDown(sf::Keyboard::Up)) && !once)
		{
			choice--;
			once = true;
		}
		else if ((InputHandler::checkDown(sf::Keyboard::S) || InputHandler::checkDown(sf::Keyboard::Down)) && !once)
		{
			choice++;
			once = true;
		}
	}

	void Menu::update(float dt)
	{
		//(102, 102, 102, 255)

		Display::setView(view);

		mainM();

		process();

	}

	void Menu::draw()
	{
		if (isAnimated) { updateAnim(); };
		Display::draw(backgroundTexture);

		Display::draw(title);

		for (int i = 0; i < opt.size(); i++)
		{
			Display::draw(opt[i]);
		}
	}

	void Menu::mainM()
	{
		switch (choice)
		{
		case 0:
			opt[0].setFillColor(sf::Color::Black);

			opt[1].setColor(sf::Color(202, 202, 202, 255));
			opt[2].setColor(sf::Color(202, 202, 202, 255));
			opt[3].setColor(sf::Color(202, 202, 202, 255));
			break;
		case 1:
			opt[1].setFillColor(sf::Color::Black);

			opt[0].setColor(sf::Color(202, 202, 202, 255));
			opt[2].setColor(sf::Color(202, 202, 202, 255));
			opt[3].setColor(sf::Color(202, 202, 202, 255));
			break;
		case 2:
			opt[2].setFillColor(sf::Color::Black);

			opt[0].setColor(sf::Color(202, 202, 202, 255));
			opt[1].setColor(sf::Color(202, 202, 202, 255));
			opt[3].setColor(sf::Color(202, 202, 202, 255));
			break;
		case 3:
			opt[3].setFillColor(sf::Color::Black);

			opt[0].setColor(sf::Color(202, 202, 202, 255));
			opt[1].setColor(sf::Color(202, 202, 202, 255));
			opt[2].setColor(sf::Color(202, 202, 202, 255));
			break;
		}
	}

	void Menu::optionM()
	{

	}

	void Menu::process()
	{
		if (InputHandler::checkDown(sf::Keyboard::Return))
		{
			switch (choice)
			{
			case 0:
				m_p_application->pushState(std::make_unique<Playing>(*m_p_application));
				music.stop();
				break;

			case 1:
				break;

			case 2:
				break;

			case 3:
				exit(0);
			}
		}
	}

	//######################
	void Menu::assignBackgroundTex(Texture_Name name)
	{
		backgroundTexture.setTexture(&Resource_Holder::get().getTexture(name));
	}

	void Menu::updateAnim()
	{
		backgroundTexture.setTextureRect(backgroundAnimation.getFrame());
	}

}