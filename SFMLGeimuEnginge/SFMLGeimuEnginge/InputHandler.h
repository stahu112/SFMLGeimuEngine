#pragma once

#include <SFML/Graphics.hpp>
#include "Command.h"

class InputHandler
{

	Command* W;
	Command* A;
	Command* S;
	Command* D;

	Command* LShiftA;
	Command* LShiftD;
	
	Command* button1;
	Command* button2;
	Command* button3;
	Command* button4;

public:
	InputHandler();
	
	Command* handleInput();

};

