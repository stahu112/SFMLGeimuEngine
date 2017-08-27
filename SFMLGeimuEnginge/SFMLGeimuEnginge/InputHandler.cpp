#include "InputHandler.h"

static JumpCommand jumpCommand;
static WalkLCommand walkLCommand;
static WalkRCommand walkRCommand;
static RunLCommand runLCommand;
static RunRCommand runRCommand;

InputHandler::InputHandler()
{
	W = &jumpCommand;
	A = &walkRCommand;
	D = &walkLCommand;
}

Command* InputHandler::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) return W;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) return A;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) return S;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) return D;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)) return button1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)) return button2;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) return button3;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)) return button4;

	return nullptr;
}
