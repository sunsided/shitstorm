#pragma once
#ifndef _ENGINE_H
#define _ENGINE_H

#include <irrlicht.h>
#include "GlobalDefines.h"

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
	Engine(void);
	virtual ~Engine(void);
	int createDevice();
	void run();

protected:
	virtual int setup();
	void setWindowTitle(wchar_t* title);
	virtual void sceneLoop() = 0;

protected:
	IrrlichtDevice* device;
	IVideoDriver* driver;
	ISceneManager* smgr;
	IGUIEnvironment* guienv;
};

#endif