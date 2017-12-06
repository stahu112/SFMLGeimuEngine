#include "Character.h"

#include <iostream>
#include "States\Playing_State.h"

void Character::draw()
{
	Display::draw(sprite);
}


Character::Character()
{	
}