#pragma once

#include <SFML/Graphics.hpp>
#include "Resource_Manager.h"

//Nazwy tekstur
enum class Texture_Name
{
	test,
	test1,
	animtest,
	test2
};

class Texture_Manager : public Resource_Manager<Texture_Name, sf::Texture>
{

private:

public:
	Texture_Manager();
};