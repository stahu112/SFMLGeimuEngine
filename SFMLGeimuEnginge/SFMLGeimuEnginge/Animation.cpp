#include "Animation.h"

Animation::Animation()
{
}

Animation::Animation(bool playOnce) :
	playOnce(playOnce)
{}

//Dodaj klatke animacji, rect to TextureRect, dokumentacja SFML, timeToNextFrame to czas po ktorym zmienia sie klatka animacji
void Animation::addFrames(const sf::IntRect & rect, float timeToNextFrame)
{
	m_frames.emplace_back(rect, timeToNextFrame);
}

sf::IntRect Animation::getFrame()
{
	//Jesli timer > czas po ktorym zmienia sie klatka
	if (m_timer.getElapsedTime().asSeconds() >=
		m_frames.at(m_currentFrame).timeToNextFrame && !played)
	{
		//Nastepna klatka
		m_currentFrame++;
		//Restart timera
		m_timer.restart();

		//Jesli aktualna klatka > dlugosc animacji to zmien aktualna klatke na 0
		if (m_currentFrame == m_frames.size())
		{
			m_currentFrame = 0;
		}
	}

	if (playOnce) played = true;

	//Zwroc rozmiar TextureRect, dokumentacja SFML
	return m_frames.at(m_currentFrame).rect;
}

void Animation::setPlayed(bool stat)
{
	played = stat;
}

void Animation::setPlayOnce(bool stat)
{
	playOnce = stat;
}
