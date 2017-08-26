#include "Menu_State.h"

namespace State
{
	Menu::Menu(Application & application)
		: Game_State(application)
	{
		initState();
	}

	void Menu::initState()
	{
		backgroundTexture.setSize(Display::screenSize);
		assignBackgroundTex(Texture_Name::test);
	}

	//##############
	void Menu::input()
	{

	}

	void Menu::update(float dt)
	{

	}

	void Menu::draw()
	{
		if (isAnimated) { updateAnim(); };
		Display::draw(backgroundTexture);

		
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