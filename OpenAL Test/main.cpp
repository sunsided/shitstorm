#include <iostream>
#include <al.h>
#include <alc.h>
#include <AL/alut.h>

#pragma comment(lib, "OpenAL32.lib")
#pragma comment(lib, "alut.lib")

using namespace std;

#define NUM_BUFFERS		1

int main() {

	// Initialization
	cout << "+ Erzeuge OpenAL-Device" << endl;
	ALCdevice* Device = alcOpenDevice(NULL);
	if (!Device) {
		cerr << "! OpenAL-Device konnte nicht erzeugt werden" << endl;
		return -1;
	}

	// Kontext erzeugen
	cout << "+ Erzeuge Kontext" << endl;
	ALCcontext* Context = alcCreateContext(Device, NULL);
	if (!Context) {
		cerr << "! OpenAL-Kontext konnte nicht erzeugt werden" << endl;
		return -2;
	}

	// Kontext setzen
	alcMakeContextCurrent(Context);

	// Check for EAX 2.0 support
	cout << "+ Teste EAX 2.0: EAX 2.0 ";
	ALboolean g_bEAX = alIsExtensionPresent("EAX2.0");
	cout << (g_bEAX ? "verfuegbar" : "nicht verfuegbar") << endl;

	// Fehler zurücksetzen
	alGetError();

	// Puffer erzeugen
	cout << "+ Erzeuge " << NUM_BUFFERS << " Puffer" << endl;
	ALuint g_Buffers[NUM_BUFFERS];
	ALenum error = 0;

	alGenBuffers(NUM_BUFFERS, g_Buffers);
	if ((error = alGetError()) != AL_NO_ERROR)
	{
		cerr << "! Puffer konnten nicht erzeugt werden, Code: " << error << endl;
		return error;
	}

	// Lade audiosample
	cout << "+ Lade Audiosample" << endl;

	ALenum format; ALvoid* data;
	ALsizei size, freq; ALboolean loop;
	alutLoadWAVFile("audio/test.wav", &format, &data, &size, &freq, &loop);
	if ((error = alGetError()) != AL_NO_ERROR)
	{
		cerr << "! Sample konnte nicht geladen werden, Code: " << error << endl;
		alDeleteBuffers(NUM_BUFFERS, g_Buffers);
		return error;
	}

	// Kopiere Sample in Puffer 0
	cout << "+ Kopiere Audiosample in Puffer" << endl;
	alBufferData(g_Buffers[0], format, data, size, freq);
	if ((error = alGetError()) != AL_NO_ERROR)
	{
		cerr << "! Sample konnte nicht kopiert werden, Code: " << error << endl;
		alDeleteBuffers(NUM_BUFFERS, g_Buffers);
		return error;
	}

	// Audiosample aus dem Speicher werfen
	cout << "+ Puffer gefuellt, gebe Speicher für Audiosample frei" << endl;
	alutUnloadWAV(format, data, size, freq);
	if ((error = alGetError()) != AL_NO_ERROR)
	{
		cerr << "! Speicher konnte nicht freigegeben werden, Code: " << error << endl;
		alDeleteBuffers(NUM_BUFFERS, g_Buffers);
		return error;
	}

	// Kontext abwählen
	cout << "+ Deaktiviere aktuellen Kontext" << endl;
	Context = alcGetCurrentContext();
	Device = alcGetContextsDevice(Context);
	alcMakeContextCurrent(NULL);

	// Puffer löschen
	cout << "+ Loesche Puffer" << endl;
	alDeleteBuffers(NUM_BUFFERS, g_Buffers);

	// Kontext schließen
	cout << "+ Schliesse OpenAL-Kontext" << endl;
	alcDestroyContext(Context);

	// Device schließen
	cout << "+ Schliesse OpenAL-Device" << endl;
	alcCloseDevice(Device);

	return 0;
}