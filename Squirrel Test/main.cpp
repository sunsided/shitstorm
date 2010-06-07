#include <stdio.h>

// Squirrel
#ifdef _MSC_VER
	#ifdef UNICODE
		#define LIB  "U.lib"
	#else
		#define LIB  ".lib"
	#endif

	#ifdef _DEBUG
		#pragma comment(lib,"squirrelD" LIB)
		#pragma comment(lib,"sqstdlibD" LIB)
	#ifdef USE_REMOTE_DEBUGGER
		#pragma comment(lib,"sqdbglibD" LIB)
	#endif
		#pragma comment(lib,"sqplusD" LIB)
	#else // Release
		#pragma comment(lib,"squirrel" LIB)
		#pragma comment(lib,"sqstdlib" LIB)
	#ifdef USE_REMOTE_DEBUGGER
		#pragma comment(lib,"sqdbglib" LIB)
	#endif
		#pragma comment(lib,"sqplus" LIB)
	#endif
#endif

#include <sqplus.h>
#include <Irrlicht.h>

#pragma comment(lib, "Irrlicht.lib")

#pragma comment(lib, "OpenAL32.lib")
#pragma comment(lib, "liboggd.lib")
#pragma comment(lib, "libvorbisd.lib")
#pragma comment(lib, "libvorbisfiled.lib")

#pragma comment(lib, "BulletCollision.lib")
#pragma comment(lib, "BulletDynamics.lib")
#pragma comment(lib, "LinearMath.lib")

void main() {
	return;
}