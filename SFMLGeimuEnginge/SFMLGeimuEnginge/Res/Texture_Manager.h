#pragma once

#include <SFML/Graphics.hpp>
#include "Resource_Manager.h"

//Nazwy tekstur
enum class Texture_Name
{
	test1,
	test2,
	spritesheet,
	spritesheet1,
};

class Texture_Manager : public Resource_Manager<Texture_Name, sf::Texture>
{

private:

public:
	Texture_Manager();
};