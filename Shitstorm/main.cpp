#include "Game.h"

int main(void) 
{
	Game* game = new Game();

	int result = game->createDevice();
	if(SUCCESS != result) return result;
	
	game->run();
	return SUCCESS;
}
