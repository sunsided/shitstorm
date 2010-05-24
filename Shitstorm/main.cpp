#include "Game.h"

#ifdef _DEBUG
	#pragma comment(lib, "libpald.lib")
	#pragma comment(lib, "libpal_bulletd.lib")
#else
	#pragma comment(lib, "libpal.lib")
	#pragma comment(lib, "libpal_bullet.lib")
#endif

#ifdef _IRR_WINDOWS_
	#pragma comment(lib, "Irrlicht.lib")
	#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

int main(int argc, char** argv) 
{
	int result;

	Game* game = new Game();
	if(SUCCESS != (result = game->createDevice(640, 480, false, true))) return result;
	return game->run();
}
