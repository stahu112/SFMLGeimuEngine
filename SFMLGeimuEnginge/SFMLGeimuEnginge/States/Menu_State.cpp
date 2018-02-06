#include "Menu_State.h"
#include "Playing_State.h"
#include <fstream>


extern int showFPS, fullON, globalVolume;

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
		q = globalVolume;
		music = new sf::Music;
		music->openFromFile("Resources/Sound/yam.ogg");
		music->setVolume(q);
		music->play();

		vol = "Volume: ";
		for (int i = 0; i < q*0.1; i++)
		{
			vol += "*";
		}

		font = Resource_Holder::get().getFont(Font_Name::menuFont);

		title.setColor(sf::Color::Black);

		title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
		title.setPosition(sf::Vector2f(Display::screenSize.x/2, 200));

		backgroundTexture.setSize((sf::Vector2f)Display::screenSize);
		assignBackgroundTex(Texture_Name::test1);

		fs = (float)Display::screenSize.x / (float)Display::screenSize.y * 50;

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
		else if (InputHandler::checkUp(sf::Keyboard::S) || InputHandler::checkUp(sf::Keyboard::Down) ||
			InputHandler::checkUp(sf::Keyboard::W) || InputHandler::checkUp(sf::Keyboard::Up)) once = false;
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
			opt[0].setString(vol);
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

		music->setVolume(q);

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

	std::fstream config;

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
					config.open("config.txt", std::ios::out);

					if (config.good())
					{
						config << fullON;
						config << "\n";
						config << showFPS;
						config << "\n";
						config << globalVolume;

						config.close();
					}
					else
					{
						config.close();
						std::cout << "Nie mozna zapisac ustawien" << std::endl;
					}
					exit(0);
				}
			}

		case men::options:
			if (InputHandler::checkUp(sf::Keyboard::Return))
			{
				switch (choice)
				{
				case 0:
					if (volb)
					{
						if (q < 100)
						{
							q += 10;
							globalVolume = q;
							vol += "*";
						}
						else
						{
							q = 0;
							globalVolume = q;
							vol = "Volume: ";
						}
					}
					volb = true;
					break;

				case 1:
					volb = false;
					choice = 0;
					currMenu = men::main;
					if(fullON) Display::setFull(false);
					else Display::setFull(true);
					break;

				case 2:
					volb = false;
					if (showFPS) showFPS = 0;
					else showFPS = 1;
					break;

				case 3:
					currMenu = men::main;
					choice = 0;
					volb = false;
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