#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include "Resource_Manager.h"

enum class Texture_Name
{
	test,
	slime,
	kupa
};

class Texture_Manager : public Resource_Manager<Texture_Name, sf::Texture>
{

private:

public:
	Texture_Manager();
};