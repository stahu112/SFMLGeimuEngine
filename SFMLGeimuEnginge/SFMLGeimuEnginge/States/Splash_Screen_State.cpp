#include "Splash_Screen_State.h"

#include "Playing_State.h"
#include "../Application.h"

namespace State
{
	//SPLASH
	Splash_Screen::Splash::Splash(const sf::Texture & texture, float time)
		: m_sprite({ Display::screenSize.x,Display::screenSize.y }),
		m_time(time),
		m_hasSound(false)
	{
		m_sprite.setTexture(&texture);
	}

	Splash_Screen::Splash::Splash(const sf::Texture & texture, sf::SoundBuffer & sbuffer, float time)
		: m_sprite({ Display::screenSize.x,Display::screenSize.y }),
		m_time(time),
		m_sound(sbuffer),
		m_hasSound(true)
	{
		m_sprite.setTexture(&texture);
	}

	void Splash_Screen::Splash::start()
	{
		if (m_hasSound)
		{
			m_sound.play();
		}

		m_timer.restart();
	}

	bool Splash_Screen::Splash::isOver() const
	{
		return m_timer.getElapsedTime().asSeconds() >= m_time;
	}

	void Splash_Screen::Splash::draw()
	{
		Display::draw(m_sprite);
	}

	//SPLASH STATE
	Splash_Screen::Splash_Screen(Application & application)
		: Game_State(application)
	{
		m_splashes.emplace(Resource_Holder::get().getTexture(Texture_Name::test),
			2.0f);
		m_splashes.emplace(Resource_Holder::get().getTexture(Texture_Name::kupa),
			2.0f);

		m_splashes.front().start();
	}

	void Splash_Screen::input()
	{
	}

	void Splash_Screen::update(float dt)
	{
		if (!m_splashes.empty())
		{
			if (m_splashes.front().isOver())
			{
				m_splashes.pop();
				if (!m_splashes.empty())
				{
					m_splashes.front().start();
				}
			}
		}
		else
		{
			m_p_application->changeState(std::make_unique<Playing>(*m_p_application));
		}
	}

	void Splash_Screen::draw()
	{
		if(!m_splashes.empty())
		m_splashes.front().draw();
	}
}