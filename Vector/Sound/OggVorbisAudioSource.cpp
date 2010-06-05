/** 
 * Project Vector
 * Audioquelle für Ogg Vorbis-Dateien
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#include "OggVorbisAudioSource.h"
#include <vorbis/vorbisenc.h>
#include <limits>

namespace pv {
namespace sound {

	OggVorbisAudioSource::OggVorbisAudioSource(void)
		: format(0), vorbisInfo(NULL), vorbisComment(NULL), opened(false)
	{
	}


	OggVorbisAudioSource::~OggVorbisAudioSource(void)
	{
		closeFile();
	}


	//! Öffnet die Datei
	ogg_int64_t OggVorbisAudioSource::openFile(const irr::core::stringc filePath) {

		// evtl. offene Handles schließen
		closeFile();

		// Datei öffnen
		char* path = const_cast<char*>(filePath.c_str());
		int error = ov_fopen(path, &oggStream);
		if (error) throw errorToString(error);

		// Info und Kommentar laden
		vorbisInfo = ov_info(&oggStream, -1);
		vorbisComment = ov_comment(&oggStream, -1);

		// Aus der Anzahl der Kanäle das Format ermitteln
		if(vorbisInfo->channels == 1)
			format = AL_FORMAT_MONO16;
		else
			format = AL_FORMAT_STEREO16;

		// Als geöffnet markieren
		opened = true;

		// Größe zurückgeben
		return getUncompressedPCMSize();
	}

	//! Lädt die Datei in einen Puffer
	void OggVorbisAudioSource::loadToBuffer(SingleSoundBuffer* soundBuffer) {
		ASSERT(soundBuffer);
		ASSERT(opened);

		// Puffer erzeugen
		ogg_int64_t bufferSize = getUncompressedPCMSize();
		ASSERT(bufferSize);
		ASSERT(bufferSize <= INT_MAX);

		// Kudos: http://opensource.creative.com/pipermail/openal/2007-January/010154.html

		char* audioBuffer = new char[(unsigned int)bufferSize];
		if (!audioBuffer) throw "Out of memory while trying to load Ogg Vorbis sample.";

		// Daten laden
		char* readPointer = audioBuffer;
		ogg_int64_t bytesToRead = bufferSize;
		int section = -1;
		do {
			long bytesRead = ov_read(&oggStream, readPointer, (int)bytesToRead, OGG_ENDIAN, OGG_BYTES_PER_SAMPLE, 1, &section);
			if (bytesRead < 0) throw "Error while reading Ogg Vorbis stream";

			// Anzahl der zu lesenden Bytes reduzieren und Lesezeiger weiterschieben
			bytesToRead -= bytesRead;
			readPointer += bytesRead;
		}
		while (bytesToRead > 0);

		// Umpuffern
		soundBuffer->bufferData(format, audioBuffer, (ALsizei)bufferSize, vorbisInfo->rate);

		// Puffer freigeben
		delete[] audioBuffer;
	}

	//! Schließt die Datei
	void OggVorbisAudioSource::closeFile() {
		if (!opened) return;

		// Streaming?
		if (isAttachedToBuffer()) {
			getAttachedStreamingBuffer()->detachStreamingSource();
		}

		// Ogg-Stream freigeben
		ov_clear(&oggStream);
		opened = false;
	}

	//! Wandelt einen Fehlercode in einen Text um
	irr::core::stringc OggVorbisAudioSource::errorToString(int code) const {
		switch(code)
		{
			case OV_EREAD:
				return irr::core::stringc("Read from media.");
			case OV_ENOTVORBIS:
				return irr::core::stringc("Not Vorbis data.");
			case OV_EVERSION:
				return irr::core::stringc("Vorbis version mismatch.");
			case OV_EBADHEADER:
				return irr::core::stringc("Invalid Vorbis header.");
			case OV_EFAULT:
				return irr::core::stringc("Internal logic fault (bug or heap/stack corruption.");
			default:
				return irr::core::stringc("Unknown Ogg error.");
		}
    }
	
	//! Ermittelt die Größe der unkomprimierten Daten
	ogg_int64_t OggVorbisAudioSource::getUncompressedPCMSize() const {
		if (!opened) return 0;
		return ov_pcm_total(const_cast<OggVorbis_File*>(&oggStream), -1) * vorbisInfo->channels * OGG_BYTES_PER_SAMPLE;
	}

	//! Beginnt mit dem Streaming von vorne
	void OggVorbisAudioSource::rewindStreaming() {
	}

	//! Streamt die Daten aus der Datei in den Puffer
	/**
		* @param buffer	Der zu befüllende Puffer
		* @returns			true, wenn weitere Daten vorliegen, ansonsten false
		*/
	bool OggVorbisAudioSource::streamToBuffer(ALuint buffer, const irr::u32 bufferSize) {
		if (buffer == 0 || bufferSize == 0) return false;

		char *data = new char[bufferSize]; // TODO: Dynamische Allokierung entfernen
		irr::u32 size = 0;
		int  section;
		int  result;
 
		while(size < bufferSize)
		{
			result = ov_read(&oggStream, data + size, bufferSize - size, OGG_ENDIAN, OGG_BYTES_PER_SAMPLE, 1, &section);
    
			if(result > 0)
				size += result;
			else
				if(result < 0) {
					delete[] data;
					throw errorToString(result);
				}
				else
					break;
		}
    
		if(size == 0)
			return false;
 
		alBufferData(buffer, format, data, size, vorbisInfo->rate);
		ALenum error = alGetError();
		if (error != AL_NO_ERROR) throw error;
 
		// Daten freigeben
		delete[] data;

		return true;
	}
}}