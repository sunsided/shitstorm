#include "Game.h"

int main(int argc, char** argv) 
{
	int result;

	Game* game = new Game();
	if(SUCCESS != (result = game->createDevice(640, 480, false, true))) return result;
	return game->run();
}
