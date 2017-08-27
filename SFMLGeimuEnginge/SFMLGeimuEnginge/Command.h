#pragma once

//IT FINALLY FUCKING WORKS HAHAHA

class Character;

	class Command
	{
	public:

		virtual void execute(Character& chara) = 0;
	};


	//ACTUAL COMMANDS
	class JumpCommand : public Command
	{
	public:
		void execute(Character& chara) override;
	};

	class WalkRCommand : public Command
	{
	public:
		void execute(Character& chara) override;
	};

	class WalkLCommand : public Command
	{
	public:
		void execute(Character& chara) override;
	};

	class RunLCommand : public Command
	{
	public:
		void execute(Character& chara) override;
	};

	class RunRCommand : public Command
	{
	public:
		void execute(Character& chara) override;
	};