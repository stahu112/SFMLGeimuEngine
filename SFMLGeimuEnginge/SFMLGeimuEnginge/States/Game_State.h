#pragma once

//Bazowa klasa dla GAME STATE'ow

#include "../Res/Resource_Holder.h"

class Application;

namespace State
{
	class Game_State
	{
	public:
		Game_State(Application& application);


		virtual void initState() = 0;
		virtual void reInit() = 0;
		virtual void input() = 0;
		virtual void update(float dt) = 0;
		virtual void draw() = 0;


	protected:
		//Do apki
		Application* m_p_application;

	};
}