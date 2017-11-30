#include "Play_Menu.h"

namespace State
{
	
	void Play_Menu::reInit()
	{
	}

	void Play_Menu::initState()
	{
		assignBackgroundTex(Texture_Name::test1);

		pauseText.setFont(Resource_Holder::get().getFont(Font_Name::Powerfull));
		pauseText.setString("PAUSED");
		pauseText.setOrigin(pauseText.getGlobalBounds().width / 2, pauseText.getGlobalBounds().height / 2);
		pauseText.setPosition(sf::Vector2f(Display::screenSize.x / 2, Display::screenSize.y / 2));
		pauseText.setFillColor(sf::Color::Black);
	}

	void Play_Menu::input()
	{
		if (InputHandler::checkUp(sf::Keyboard::Escape)) m_p_application->popState();
	}

	void Play_Menu::update(float dt)
	{
		if (isAnimated) { updateAnim(); };
		Display::setView(view);
	}

	void Play_Menu::draw()
	{
		Display::draw(background);
		Display::draw(pauseText);
	}

	Play_Menu::Play_Menu(Application& application) : Game_State(application)
	{
		initState();
	}


	Play_Menu::~Play_Menu()
	{
	}

	void Play_Menu::assignBackgroundTex(Texture_Name name)
	{
		background.setTexture(Resource_Holder::get().getTexture(name));
	}

	void Play_Menu::updateAnim()
	{
		background.setTextureRect(backgroundAnimation.getFrame());
	}

};