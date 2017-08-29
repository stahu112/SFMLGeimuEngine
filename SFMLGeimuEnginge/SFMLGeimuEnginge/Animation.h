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

	float getLength() const;

private:

	bool playOnce = false;

	bool played = false;
	
	float animLength = 0;

	//Vector klatek
	std::vector<Frame> m_frames;

	sf::Clock m_timer;

	int m_currentFrame = 0;
};

