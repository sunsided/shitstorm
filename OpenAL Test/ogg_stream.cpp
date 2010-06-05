#include "ogg_stream.h"
#include <iostream>

void ogg_stream::open(string path)
{
    int result;
    
	char* filepath = const_cast<char*>(path.c_str());
	if (ov_fopen(filepath, &oggStream))
	/*
    if(!(oggFile = fopen(path.c_str(), "rb")))
        throw string("Could not open Ogg file.");

	fseek(oggFile, 0, 1);
 
    if((result = ov_open(oggFile, &oggStream, NULL, 0)) < 0)
	*/
    {
        fclose(oggFile);
 
        throw string("Could not open Ogg stream. ") + errorString(result);
    }

    vorbisInfo = ov_info(&oggStream, -1);
    vorbisComment = ov_comment(&oggStream, -1);
 
    if(vorbisInfo->channels == 1)
        format = AL_FORMAT_MONO16;
    else
        format = AL_FORMAT_STEREO16;

    alGenBuffers(2, buffers); // "front" und "back" buffer
    check();
    alGenSources(1, &source);
    check();
    
    alSource3f(source, AL_POSITION,        0.0, 0.0, 0.0);
    alSource3f(source, AL_VELOCITY,        0.0, 0.0, 0.0);
    alSource3f(source, AL_DIRECTION,       0.0, 0.0, 0.0);
    alSourcef (source, AL_ROLLOFF_FACTOR,  0.0          );
    alSourcei (source, AL_SOURCE_RELATIVE, AL_TRUE      );
}



void ogg_stream::release()
{
    alSourceStop(source);
    empty();
    alDeleteSources(1, &source);
    check();
    alDeleteBuffers(2, buffers);
    check();
 
    ov_clear(&oggStream);
}



void ogg_stream::display()
{
    cout
        << "version         " << vorbisInfo->version         << "\n"
        << "channels        " << vorbisInfo->channels        << "\n"
        << "rate (hz)       " << vorbisInfo->rate            << "\n"
        << "bitrate upper   " << vorbisInfo->bitrate_upper   << "\n"
        << "bitrate nominal " << vorbisInfo->bitrate_nominal << "\n"
        << "bitrate lower   " << vorbisInfo->bitrate_lower   << "\n"
        << "bitrate window  " << vorbisInfo->bitrate_window  << "\n"
        << "\n"
        << "vendor " << vorbisComment->vendor << "\n";
        
    for(int i = 0; i < vorbisComment->comments; i++)
        cout << "   " << vorbisComment->user_comments[i] << "\n";
        
    cout << endl;
}



bool ogg_stream::playback()
{
    if(playing())
        return true;
        
	// Ersten Puffer füllen
    if(!stream(buffers[0]))
        return false;
 
	// Zweiten Puffer füllen
    if(!stream(buffers[1]))
        return false;
    
	// Beide Puffer einhängen
    alSourceQueueBuffers(source, 2, buffers);

	// Quelle abspielen
    alSourcePlay(source);
    
    return true;
}



bool ogg_stream::playing()
{
    ALenum state;
    
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    
    return (state == AL_PLAYING);
}



bool ogg_stream::update()
{
    int processed;
    bool active = true;
 
    alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);
 
    while(processed--)
    {
        ALuint buffer;
        
        alSourceUnqueueBuffers(source, 1, &buffer);
        check();
 
        active = stream(buffer);
 
        alSourceQueueBuffers(source, 1, &buffer);
        check();
    }
 
    return active;
}


bool ogg_stream::stream(ALuint buffer)
{
    char data[OGGSTREAM_BUFFER_SIZE];
    int  size = 0;
    int  section;
    int  result;
 
    while(size < OGGSTREAM_BUFFER_SIZE)
    {
        result = ov_read(&oggStream, data + size, OGGSTREAM_BUFFER_SIZE - size, 0, 2, 1, & section);
    
        if(result > 0)
            size += result;
        else
            if(result < 0)
                throw errorString(result);
            else
                break;
    }
    
    if(size == 0)
        return false;
 
    alBufferData(buffer, format, data, size, vorbisInfo->rate);
    check();
 
    return true;
}



void ogg_stream::empty()
{
    int queued;
    
    alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);
    
    while(queued--)
    {
        ALuint buffer;
    
        alSourceUnqueueBuffers(source, 1, &buffer);
        check();
    }
}



void ogg_stream::check()
{
    int error = alGetError();
 
    if(error != AL_NO_ERROR)
        throw string("OpenAL error was raised.");
}


string ogg_stream::errorString(int code)
{
    switch(code)
    {
        case OV_EREAD:
            return string("Read from media.");
        case OV_ENOTVORBIS:
            return string("Not Vorbis data.");
        case OV_EVERSION:
            return string("Vorbis version mismatch.");
        case OV_EBADHEADER:
            return string("Invalid Vorbis header.");
        case OV_EFAULT:
            return string("Internal logic fault (bug or heap/stack corruption.");
        default:
            return string("Unknown Ogg error.");
    }
}
