/* Compile: g++ -lSDL2 MainGame.cpp Game.cpp Bunny.cpp */

#include "Game.h"
#include <ctime>

int main(int argc, char** argv) {
	srand(time(0));
	Game game;
	bool success = game.Initialize();
	if (success) {
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
}