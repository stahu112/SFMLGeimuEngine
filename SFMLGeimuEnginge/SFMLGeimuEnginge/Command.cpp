#include "Command.h"

#include "Character.h"

	//ACTUAL COMMANDS
void JumpCommand::execute(Character& chara)
{
	chara.jump();
}

void WalkLCommand::execute(Character& chara)
{
	chara.walkL();
}

void WalkRCommand::execute(Character& chara)
{
	chara.walkR();
}

void RunLCommand::execute(Character& chara)
{
	chara.runL();
}

void RunRCommand::execute(Character& chara)
{
	chara.runR();
}
