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
	}

	void Menu::input()
	{

	}

	void Menu::update(float dt)
	{

	}

	void Menu::draw()
	{
		std::cout << "MENU" << std::endl;
	}

}