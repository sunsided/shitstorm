#pragma once
#ifndef _OGG_STREAM_H
#define _OGG_STREAM_H

#include <string>
using namespace std;

extern "C" {
#include <ogg/ogg.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisenc.h>
#include <vorbis/vorbisfile.h>

#include <al.h>
#include <alc.h>
}

// Kudos: http://www.devmaster.net/articles/openal-tutorials/lesson8.php


#define OGGSTREAM_BUFFER_SIZE (4096 * 8)

class ogg_stream
{
    public:
 
        void open(string path); // obtain a handle to the file
        void release();         // release the file handle
        void display();         // display some info on the Ogg
        bool playback();        // play the Ogg stream
        bool playing();         // check if the source is playing
        bool update();          // update the stream if necessary
 
    protected:
 
        bool stream(ALuint buffer);   // reloads a buffer
        void empty();                 // empties the queue
        void check();                 // checks OpenAL error state
        string errorString(int code); // stringify an error code

    private:
 
        FILE*           oggFile;       // file handle
        OggVorbis_File  oggStream;     // stream handle
        vorbis_info*    vorbisInfo;    // some formatting data
        vorbis_comment* vorbisComment; // user comments
 
        ALuint buffers[2]; // front and back buffers
        ALuint source;     // audio source
        ALenum format;     // internal format
};

#endif
