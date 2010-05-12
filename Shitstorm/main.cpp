#include "Game.h"

int main(void) 
{
	int result;

	Game* game = new Game();
	if(SUCCESS != (result = game->createDevice(640, 480))) return result;
	return game->run();
}
