/*
yo~sero!
dev. by devi_kya
*/
#include "Game.h"
#include "utilities/Logger.h"

int main()
{
	try
	{
		yothello::Game game;
		game.run();
	}
	catch (std::exception& e)
	{
		yothello::Logger::instance().timestamp();
		yothello::Logger::instance().write(e.what());
		return -1;
	}
	return 0;
}