#pragma once
#ifndef _ENGINE_H
#define _ENGINE_H

#include <irrlicht.h>
#include "GlobalDefines.h"
#include "GameTimer.h"

#ifdef _IRR_WINDOWS_
	#pragma comment(lib, "Irrlicht.lib")
	#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Engine
{
public:
	//! Konstruktor
	Engine(void);

	//! Destruktor
	virtual ~Engine(void);
	
	//! Erzeugt das Spielfenster
	/**
	* @param width			Gibt die horizontale Auflösung an
	* @param height			Gibt die vertikale Auflösung an
	* @param fullscreen		Gibt an, ob die Anwendung im Vollbild- oder im Fenstermodus laufen soll
	* @param stencilBuffer	Gibt an, ob ein Stencilbuffer verwendet werden soll
	*/
	int createDevice(int width = 640, int height = 480, bool fullscreen = false, bool stencilBuffer = false);
	
	//! Startet den Spiel-Loop
	int run();


protected:
	//! Wird während des Konstruierens aufgerufen
	/** Diese Funktion sollte von der Spielklasse überladen werden. */
	virtual int setup();
	
	//! Setzt den Titel des Fensters
	/**
	* @param title			Der Titeltext
	*/
	void setWindowTitle(const wchar_t *title);
	
	//! Der eigentliche Spiel-Loop
	/** Diese Funktion muss von der Spielklasse überladen werden.
	* 
	* @param deltaT			Die seit dem letzten Szenenstart vergangene Zeit
	*/
	virtual void sceneLoop(int deltaT) = 0;
	
	//! Liefert die Anzahl der Frames pro Sekunde
	u32 getFps();

private:
	//! Die Größe des Fensters / Auflösung des Bildschirms
	dimension2d<u32> screenSize;

protected:
	//! Das Irrlicht-Device
	IrrlichtDevice* device;

	//! Der Videotreiber
	IVideoDriver* driver;

	//! Der Szenenmanager
	ISceneManager* smgr;

	//! Die GUI
	IGUIEnvironment* guienv;

	//! Der Timer für die Delta-T-Berechnung
	GameTimer* timer;
};

#endif