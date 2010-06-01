#include <iostream>

#pragma comment(lib, "OpenAL32.lib")
#pragma comment(lib, "liboggd.lib")
#pragma comment(lib, "libvorbisd.lib")
#pragma comment(lib, "libvorbisfiled.lib")

using namespace std;

#include "ogg_stream.h"

#include <al.h>
#include <alc.h>

int main(int argc, char** argv) {


	// Initialization
	ALCdevice *Device = NULL;
	ALCcontext *Context = NULL;
	Device = alcOpenDevice(NULL); // select the "preferred device"
	if (Device) {
		Context=alcCreateContext(Device,NULL);
		alcMakeContextCurrent(Context);
	}



	ogg_stream ogg;

	try
    {
        if(argc < 2)
            throw string("oggplayer *.ogg");
    
        ogg.open(argv[1]);
 
        ogg.display();

		cout << "Beginne Wiedergabe ..." << endl;
        if(!ogg.playback())
            throw string("Ogg refused to play.");
        
		cout << "Streame Audio ..." << endl;
        while(ogg.update())
        {
            if(!ogg.playing())
            {
                if(!ogg.playback())
                    throw string("Ogg abruptly stopped.");
                else
                    cout << "Ogg stream was interrupted.\n";
            }
        }
                    
        cout << "Voila.";
        cin.get();
    }
    catch(string error)
    {
        cout << error;
        cin.get();
    }

	ogg.release();



	// Exit
	Context = alcGetCurrentContext();
	Device = alcGetContextsDevice(Context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(Context);
	alcCloseDevice(Device);


	return 0;
}