#include "Menu_State.h"
#include "Playing_State.h"
#include <fstream>


extern bool showFPS, fullON, vsyncON;



namespace State
{
	Menu::Menu(Application & application)
		: Game_State(application)
	{
		initState();
	}

	void Menu::reInit()
	{
	}

	void Menu::initState()
	{
		music = new sf::Music;
		music->openFromFile("Resources/Sound/yam.ogg");
		music->play();

		font = Resource_Holder::get().getFont(Font_Name::menuFont);

		title.setColor(sf::Color::Black);

		title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
		title.setPosition(sf::Vector2f(Display::screenSize.x/2, 200));

		backgroundTexture.setSize(Display::screenSize);
		assignBackgroundTex(Texture_Name::test1);

		fs = Display::screenSize.x / Display::screenSize.y * 50;

		opt.push_back(sf::Text("NEW GAME", font, fs));
		opt.push_back(sf::Text("LOAD", font, fs));
		opt.push_back(sf::Text("OPTIONS", font, fs));
		opt.push_back(sf::Text("QUIT", font, fs));

		for (int i = 0; i < opt.size(); i++)
		{
			opt[i].setColor(sf::Color(202,202,202,255));
			
			opt[i].setOrigin(opt[i].getLocalBounds().width / 2, opt[i].getLocalBounds().height / 2);

			opt[i].setPosition(sf::Vector2f(Display::screenSize.x/4, Display::screenSize.y/2 + i*fs));
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

		switch (currMenu)
		{
		case men::main:
			opt[0].setString("NEW GAME");
			opt[1].setString("LOAD");
			opt[2].setString("OPTIONS");
			opt[3].setString("QUIT");
			for (int i = 0; i < opt.size(); i++)
			{
				opt[i].setOrigin(opt[i].getLocalBounds().width / 2, opt[i].getLocalBounds().height / 2);

				opt[i].setPosition(sf::Vector2f(Display::screenSize.x / 4, Display::screenSize.y / 2 + i*fs));
			}
			break;
			
		case men::options:
			if(vsyncON) opt[0].setString("Vertical sync: ON");
			else opt[0].setString("Vertical sync: Off");
			if(fullON) opt[1].setString("FullScreen: ON");
			else opt[1].setString("FullScreen: off");
			if(showFPS) opt[2].setString("Show fps: ON");
			else opt[2].setString("Show fps: Off");
			opt[3].setString("BACK");

			for (int i = 0; i < opt.size(); i++)
			{
				opt[i].setOrigin(opt[i].getLocalBounds().width / 2, opt[i].getLocalBounds().height / 2);

				opt[i].setPosition(sf::Vector2f(Display::screenSize.x / 4, Display::screenSize.y / 2 + i*fs));
			}
		}

		highlight();

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

	void Menu::highlight()
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

	void Menu::process()
	{
		switch (currMenu)
		{


		case men::main:
			if (InputHandler::checkUp(sf::Keyboard::Return))
			{
				switch (choice)
				{
				case 0:
					delete music;
					m_p_application->changeState(std::make_unique<Playing>(*m_p_application));
					break;

				case 1:
					//currMenu = men::load;
					choice = 0;
					break;

				case 2:
					currMenu = men::options;
					choice = 0;
					break;

				case 3:
					delete music;
					exit(0);
				}
			}

		case men::options:
			if (InputHandler::checkUp(sf::Keyboard::Return))
			{
				switch (choice)
				{
				case 0:
					if(vsyncON) Display::setVsync(false);
					else Display::setVsync(true);
					break;

				case 1:
					currMenu = men::main;
					choice = 0;
					if(fullON) Display::setFull(false);
					else Display::setFull(true);
					break;

				case 2:
					if (showFPS) showFPS = false;
					else showFPS = true;
					break;

				case 3:
					std::fstream config;
					config.open("config.txt", std::ios::out);

					if (config.good())
					{
						config << fullON << " " << showFPS << " " << vsyncON;

						config.close();
					}
					else
					{
						config.close();
						std::cout << "Nie mozna zapisac ustawien" << std::endl;
					}

					currMenu = men::main;
					choice = 0;
					break;
				}
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