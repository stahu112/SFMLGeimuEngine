#pragma once

#include <SFML/Graphics.hpp>
#include "Resource_Manager.h"

enum class Font_Name
{
	menuFont
};

class Font_Manager : public Resource_Manager<Font_Name, sf::Font>
{

private:
	

public:
	Font_Manager();
};