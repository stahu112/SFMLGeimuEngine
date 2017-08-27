#include "InputHandler.h"
#include "Display.h"

static JumpCommand jumpCommand;
static WalkLCommand walkLCommand;
static WalkRCommand walkRCommand;
static RunLCommand runLCommand;
static RunRCommand runRCommand;

InputHandler::InputHandler()
{
	W = &jumpCommand;
	A = &walkLCommand;
	D = &walkRCommand;

	LShiftA = &runLCommand;
	LShiftD = &runRCommand;
}

Command* InputHandler::handleInput()
{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) return W;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) return A;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) return S;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) return D;

	return nullptr;
}
