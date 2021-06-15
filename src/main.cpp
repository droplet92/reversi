/*
Reversi
author: dev2_kya
*/
#include "Game.h"
#include "utilities/Logger.h"

int main()
{
	try
	{
		reversi::Game game;
		game.run();
	}
	catch (std::exception& e)
	{
		reversi::Logger::instance().timestamp();
		reversi::Logger::instance().write(e.what());
		return -1;
	}
	return 0;
}