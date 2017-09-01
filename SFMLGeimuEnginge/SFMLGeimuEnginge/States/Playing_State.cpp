#include "Playing_State.h"

#include <iostream>

static Character_Candy Candy;

namespace State
{
	//Inicjuj STATE, testowo potworzone rozne obiekty, przypisane tekstury, dzwieki itp
	Playing::Playing(Application & application)
		: Game_State(application)
	{
		initState();
	}
	
	void Playing::initState()
	{
		setPlayer(&Candy);
		player->setPosition(sf::Vector2f(0, 48*16));
		initLevels();
		changeLevel(LevelID::level0);
	}

	void Playing::initLevels()
	{
		Level level0(
			Texture_Name::test2,
			sf::Vector2u(100, 50),
			false,
			*this
		);

		//TODO zgranie z pliku
		level0.getPlatforms()->emplace_back(
			sf::Vector2f(0, level0.getSize().y * level0.tileSize.y),
			sf::Vector2f(level0.getSize().x * level0.tileSize.x, level0.tileSize.y),
			Texture_Name::test);

		level0.getPlatforms()->emplace_back(sf::Vector2f(
			level0.tileSize.x * 2, level0.getSize().y*level0.tileSize.x - level0.tileSize.y * 2),
			sf::Vector2f(level0.tileSize.x * 10, level0.tileSize.y),
			Texture_Name::test);

		addLevel(LevelID::level0, level0);

	}

	//Sterowanie itp.
	void Playing::input()
	{
		switch (player->currentState)
		{

		case CharState::StandingR:

			//SetAnim
			if (InputHandler::checkDown(sf::Keyboard::Space)) {
				player->currentState = CharState::JumpR; break;
			}

			if (player->getFlags().walkToggle)
			{
				if (InputHandler::checkDown(sf::Keyboard::D)) {
					player->currentState = CharState::RunR; break;
				}
				if (InputHandler::checkDown(sf::Keyboard::A)) {
					player->currentState = CharState::RunL; break;
				}
			}

			else if (InputHandler::checkDown(sf::Keyboard::D)) {
				player->currentState = CharState::WalkR; break;
			}
			else if (InputHandler::checkDown(sf::Keyboard::A)) {
				player->currentState = CharState::WalkL; break;
			}
			break;

		case CharState::StandingL:

			//SetAnim
			if (InputHandler::checkDown(sf::Keyboard::Space)) {
				player->currentState = CharState::JumpL; break;
			}

			if (player->getFlags().walkToggle)
			{
				if (InputHandler::checkDown(sf::Keyboard::D)) {
					player->currentState = CharState::RunR; break;
				}
				if (InputHandler::checkDown(sf::Keyboard::A)) {
					player->currentState = CharState::RunL; break;
				}
			}

			else if (InputHandler::checkDown(sf::Keyboard::D)) {
				player->currentState = CharState::WalkR; break;
			}
			else if (InputHandler::checkDown(sf::Keyboard::A)) {
				player->currentState = CharState::WalkL; break;
			}
			break;

		case CharState::WalkL:

			//SetAnim
			if (InputHandler::checkDown(sf::Keyboard::Space)) {
				player->currentState = CharState::JumpL; break;
			}
			else if (InputHandler::checkUp(sf::Keyboard::A)) {
				player->currentState = CharState::StandingL; break;
			}

			break;

		case CharState::WalkR:

			//SetAnim
			if (InputHandler::checkDown(sf::Keyboard::Space)) {
				player->currentState = CharState::JumpR; break;
			}
			else if (InputHandler::checkUp(sf::Keyboard::D)) {
				player->currentState = CharState::StandingR; break;
			}

			break;

		case CharState::RunL:

			//SetAnim
			if (InputHandler::checkDown(sf::Keyboard::Space)) {
				player->currentState = CharState::JumpL; break;
			}
			else if (InputHandler::checkUp(sf::Keyboard::A)) {
				player->currentState = CharState::StandingL; break;
			}

			break;

		case CharState::RunR:

			//SetAnim
			if (InputHandler::checkDown(sf::Keyboard::Space)) {
				player->currentState = CharState::JumpR; break;
			}
			else if (InputHandler::checkUp(sf::Keyboard::D)) {
				player->currentState = CharState::StandingR; break;
			}
			break;

		case CharState::JumpL:
			if (player->getVelocity().y > 0) {
				player->currentState = CharState::DiveL; break;
			}

		case CharState::JumpR:
			if (player->getVelocity().y > 0) {
				player->currentState = CharState::DiveR; break;
			}

		case CharState::DiveL:

			if (InputHandler::checkDown(sf::Keyboard::Space)) {
				InputHandler::key = sf::Keyboard::Unknown;
			}

			if (player->getVelocity().x == 0) {
				player->currentState = CharState::StandingL; break;
			}
			if (player->getFlags().walkToggle && InputHandler::checkDown(sf::Keyboard::A)) {
				player->currentState = CharState::RunL; break;
			}
			if (InputHandler::checkDown(sf::Keyboard::A)) {
				player->currentState = CharState::WalkL; break;
			}

		case CharState::DiveR:

			if (InputHandler::checkDown(sf::Keyboard::Space)) {
				InputHandler::key = sf::Keyboard::Unknown;
			}

			if (player->getVelocity().x == 0)
			{
				player->currentState = CharState::StandingR; break;
			}
			if (player->getFlags().walkToggle && InputHandler::checkDown(sf::Keyboard::D)) {
				player->currentState = CharState::RunR; break;
			}
			if (InputHandler::checkDown(sf::Keyboard::D)) {
				player->currentState = CharState::WalkR; break;
			}
		}
	}

	//Aktualizuj stany
	//CHUJ DUPA CYCKI NIE PAMIETAM CO TO ROBI
	void Playing::update(float dt)
	{
		updateLevel();
		resolveCollisions();
		player->update(dt);

		std::cout << (unsigned)player->currentState << std::endl;

	}


	//Rysuj obiekty UI
	void Playing::draw()
	{
		player->draw();
	}

	void Playing::resolveCollisions()
	{
		//Platforms
		for (unsigned i = 0; i < currentLevel->getPlatforms()->size(); i++)
		{
			if (Collision::collisionWithPlat(player, HitId::L, currentLevel->getPlatforms()->at(i), HitIdPlat::baseU))
			{
				player->getFlags().onGround = true;
				player->currentState = CharState::DiveR;
			}
		}
	}
	

	
	void Playing::changeLevel(LevelID level)
	{
		currentLevel = &m_levels.at(level);
	}

	void Playing::updateLevel()
	{
		if (currentLevel)
		{
			currentLevel->drawLevel();
			currentLevel->setView();
		}
	}

	//AddLevel
	void Playing::addLevel(LevelID id, Level level)
	{
		m_levels.insert(std::make_pair(id, level));
	}

	void Playing::setPlayer(Character * chara)
	{
		player = chara;
	}

	Level * Playing::getCurrentLevel() const
	{
		return currentLevel;
	}

	Character * Playing::getPlayer() const
	{
		return player;
	}
}
