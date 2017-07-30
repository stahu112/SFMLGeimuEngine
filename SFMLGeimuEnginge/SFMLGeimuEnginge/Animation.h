#pragma once

//W dokumentacji SFML opisane sa wszystkie te glupotki z przestrzeni sf, animacje polegaja na spritesheetach

#include <SFML\Graphics.hpp>
#include <vector>

class Animation
{
	struct Frame
	{
		Frame(const sf::IntRect& rect, float timeToNextFrame)
			: rect(rect),
			timeToNextFrame(timeToNextFrame)
		{}

		const sf::IntRect rect;
		const float timeToNextFrame;
	};

public:

	Animation();
	Animation(bool playOnce);

	void addFrames(const sf::IntRect& rect, float timeToNextFrame);

	sf::IntRect getFrame();

	void setPlayed(bool stat);
	void setPlayOnce(bool stat);

private:

	bool playOnce = false;

	bool played = false;

	//Vector klatek
	std::vector<Frame> m_frames;

	sf::Clock m_timer;

	int m_currentFrame = 0;
};

