/** 
 * Project Vector
 * Audioquelle für Ogg Vorbis-Dateien
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#pragma once
#ifndef _OGGVORBISAUDIOSOURCE_H
#define _OGGVORBISAUDIOSOURCE_H

#include "global.h"
#include "SingleSoundBuffer.h"

#include <ogg/ogg.h>
#include <vorbis/vorbisfile.h>

#ifndef OGG_LITTLE_ENDIAN
	#define OGG_LITTLE_ENDIAN 0
#endif

#ifndef OGG_BIG_ENDIAN
	#define OGG_BIG_ENDIAN 1
#endif

#ifndef OGG_ENDIAN
	#define OGG_ENDIAN OGG_LITTLE_ENDIAN
#endif

#ifndef OGG_BYTES_PER_SAMPLE
	#define OGG_BYTES_PER_SAMPLE 2
#endif

namespace pv {
namespace sound {

	//! Audioquelle
	class OggVorbisAudioSource
	{
	public:
		//! Erzeugt eine neue Instanz des Objektes
		OggVorbisAudioSource(void);

		// Destruktor
		virtual ~OggVorbisAudioSource(void);

		//! Öffnet die Datei
		void openFile(const irr::core::stringc filePath); 

		//! Lädt die Datei in einen Puffer
		void loadToBuffer(SingleSoundBuffer* buffer);

		//! Schließt die Datei
		void closeFile();

		//! Ermittelt das Format
		inline ALenum getFormat() const { return format; }

		//! Ermittelt, ob eine Datei geöffnet wurde
		inline bool isOpen() const { return opened; }

		//! Bezieht die vorbis_info-Struktur
		inline struct vorbis_info* getVorbisInfo() const { return vorbisInfo; }

		//! Bezieht die vorbis_info-Struktur
		inline struct vorbis_comment* getVorbisComment() const { return vorbisComment; }

		//! Ermittelt die Größe der unkomprimierten Daten
		ogg_int64_t getUncompressedPCMSize() const;

	protected:

		//! Wandelt einen Fehlercode in einen Text um
		irr::core::stringc errorToString(int code) const;

	private:

		//! Gibt an, ob eine Datei geöffnet wurde
		bool opened;

		//! Der Stream
        OggVorbis_File  oggStream;

		//! Metainfos der Datei
        vorbis_info*    vorbisInfo;

		//! Kommentar der Datei
        vorbis_comment* vorbisComment;

		//! Das Format
		ALenum format;
	};

}}

#endif
