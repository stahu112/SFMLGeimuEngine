#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Game_State.h"

#include "../Display.h"

#include "../Res/Resource_Holder.h"

#include <queue>

namespace State
{
	class Splash_Screen : public Game_State
	{
		class Splash
		{
		public:
			Splash(const sf::Texture& texture, float time);
			Splash(const sf::Texture& texture, sf::SoundBuffer& sbuffer, float time);
		
			void start();
			bool isOver() const;
			void draw();

		private:
			sf::RectangleShape m_sprite;
			sf::Sound m_sound;
			float m_time;
			sf::Clock m_timer;
			bool m_hasSound;
		
		};

	public:
		Splash_Screen(Application& application);

		void input() override;
		void update(float dt) override;
		void draw() override;

	private:
		std::queue<Splash> m_splashes;
	};
}