//State ze SPLASHAMI na start

#include "Splash_Screen_State.h"

#include "Menu_State.h"
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
		//Ustaw teksture splasha
		m_sprite.setTexture(&texture);
	}

	//Przeladowany konstruktor, tu + dzwiek
	Splash_Screen::Splash::Splash(const sf::Texture & texture, sf::SoundBuffer & sbuffer, float time)
		: m_sprite({ Display::screenSize.x,Display::screenSize.y }),
		m_time(time),
		m_sound(sbuffer),
		m_hasSound(true)
	{
		m_sprite.setTexture(&texture);
	}

	//Wyswietl splasha
	void Splash_Screen::Splash::start()
	{
		//Jesli z dzwiekiem to odtworz
		if (m_hasSound)
		{
			m_sound.play();
		}

		//Resetuj timer
		m_timer.restart();
	}

	//Jesli timer > czas wyswietlania splasha to zwraca true
	bool Splash_Screen::Splash::isOver() const
	{
		return m_timer.getElapsedTime().asSeconds() >= m_time;
	}

	void Splash_Screen::Splash::draw()
	{
		Display::draw(m_sprite);
	}
	//###############################

	//SPLASH STATE
	Splash_Screen::Splash_Screen(Application & application)
		: Game_State(application)
	{
		initState();
	}

	void Splash_Screen::initState()
	{
		//Wrzuc splashe na poczatek kolejki
		m_splashes.emplace(Resource_Holder::get().getTexture(Texture_Name::test),
			2.0f);
		m_splashes.emplace(Resource_Holder::get().getTexture(Texture_Name::test2),
			2.0f);

		//Rozpocznij splasha na poczatku kolejki
		m_splashes.front().start();
	}

	//Input state'u
	void Splash_Screen::input()
	{

	}

	void Splash_Screen::update(float dt)
	{
		if (!m_splashes.empty())
		{
			
			//Jesli splash sie skonczyl
			if (m_splashes.front().isOver())
			{
				//Wyrzuc splasha z przodu kolejki
				m_splashes.pop();
				
				//Jesli kolejka nie jest pusta
				if (!m_splashes.empty())
				{
					//Wyswietl splasha z przodu kolejki
					m_splashes.front().start();
				}
			}
		}
		else		//Jesli nie ma wiecej splashy to wepchnij STATE Menu na stos STATE'ow
		{
			m_p_application->changeState(std::make_unique<Playing>(*m_p_application));
		}
	}

	//Jesli kolejka nie jest pusta to rysuj splasha
	void Splash_Screen::draw()
	{
		if(!m_splashes.empty())
		m_splashes.front().draw();
	}
}
	//##################################