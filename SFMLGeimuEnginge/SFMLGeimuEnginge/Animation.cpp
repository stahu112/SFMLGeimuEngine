#include "Animation.h"

void Animation::addFrames(const sf::IntRect & rect, float timeToNextFrame)
{
	m_frames.emplace_back(rect, timeToNextFrame);
}

sf::IntRect Animation::getFrame()
{
	if (m_timer.getElapsedTime().asSeconds() >=
		m_frames.at(m_currentFrame).timeToNextFrame)
	{
		m_currentFrame++;
		m_timer.restart();

		if (m_currentFrame == m_frames.size())
		{
			m_currentFrame = 0;
		}
	}

	return m_frames.at(m_currentFrame).rect;
}
