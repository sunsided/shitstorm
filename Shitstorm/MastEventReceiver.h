/// ==================================================================================================
/// MastEventReceiver code is © (Copyright) Robert E. Demarest, AKA Mastiff or Mastiff Odit
/// This file may be used in any non-commercial or commercial project as long as the following conditions are met:
/// You may not claim this code as being your own.
/// You may not use this code for any harmful, malicious or otherwise damaging programs.
///
/// This is version 1.2a of the class.
/// This class is designed for use with the Irrlicht Engine, it was written for version 1.3 of the engine.
/// ==================================================================================================

//////////////////////////////////////////////////////////////////////////////////////////////////////
//
// To use this Class just add  #include "MastEventReceiver.cpp"  to the end of your includes list. (or add the class in-line into your program)
// Then create an instance of it like so: MastEventReceiver eventReceiver;
// Then call the initialization fucntion like so: eventReceiver.init();
// Then inside your Main Game Loop place "eventReceiver.endEventProcess();" in the beginning of your game loop, before anything -
// that would require input, then put "eventReceiver.startEventProcess();" at the very end of your Main Game Loop.
// yeah I know it's confusing, but it makes alot more sense in the internals of the class.
//
//////////////////////////////////////////////////////////////////////////////////////////////////////

// Change this to the path where your Irrlicht Header Files are.
#include <irrlicht.h>

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/// ==============================
/// MastEventReceiver
/// ==============================
class MastEventReceiver : public IEventReceiver
{

	protected:
	// Enumeration for UP, DOWN, PRESSED and RELEASED key states. Also used for mouse button states.
	enum keyStatesENUM {UP, DOWN, PRESSED, RELEASED};

	// Enumeration for Event Handling State.
	enum processStateENUM {STARTED, ENDED};

	// Mouse button states.
	keyStatesENUM mouseButtonState[2]; //Left(0), Middle(1) and Right(2) Buttons.

	// Keyboard key states.
	keyStatesENUM keyState[KEY_KEY_CODES_COUNT];

	// Mouse X/Y coordinates and Wheel data.
	struct mouseData
	{
		int X;
		int Y;
		float wheel; //wheel is how far the wheel has moved
	};
	struct mouseData mouse;

	processStateENUM processState; // STARTED = handling events, ENDED = not handling events

	virtual bool OnEvent(const SEvent & event)
	{
		if (processState != STARTED) return false;

		bool eventprocessed = false;

		//////////////////////////////
		// Keyboard Input Event
		//////////////////////////////
		if (event.EventType == EET_KEY_INPUT_EVENT)
		{
			// if key is Pressed Down
			if (event.KeyInput.PressedDown == true)
			{
				// If key was not down before
				if (keyState[event.KeyInput.Key] != DOWN)
				{
					keyState[event.KeyInput.Key] = PRESSED; // Set to Pressed
				}
				else
				{
					// if key was down before
					keyState[event.KeyInput.Key] = DOWN; // Set to Down
				}
			}
			else
			{

					// if the key is down
					if (keyState[event.KeyInput.Key] != UP)
					{
						keyState[event.KeyInput.Key] = RELEASED; // Set to Released
					}
			}

			eventprocessed = true;
		}

		//////////////////////////////
		// Mouse Input Event
		//////////////////////////////

		if (event.EventType == EET_MOUSE_INPUT_EVENT)
		{
			//Mouse changed position
			if (event.MouseInput.Event == EMIE_MOUSE_MOVED)
			{
				mouse.Y = event.MouseInput.Y;
				mouse.X = event.MouseInput.X;
			}

			//Wheel moved.
			if (event.MouseInput.Event == EMIE_MOUSE_WHEEL)
			{
				mouse.wheel += event.MouseInput.Wheel;
			}

			//Left Mouse Button Pressed
			if (event.MouseInput.Event == EMIE_LMOUSE_PRESSED_DOWN)
			{
				//
				if (mouseButtonState[0] == UP || mouseButtonState[0] == RELEASED)
				{
					mouseButtonState[0] = PRESSED;
				}
				else
				{
					mouseButtonState[0] = DOWN;
				}
			}

			//Left Mouse Button Rleased
			if (event.MouseInput.Event == EMIE_LMOUSE_LEFT_UP)
			{
				//
				if (mouseButtonState[0] != UP)
				{
					mouseButtonState[0] = RELEASED;
				}
			}

			//Middle Mouse Button Pressed
			if (event.MouseInput.Event == EMIE_MMOUSE_PRESSED_DOWN)
			{
				//
				if (mouseButtonState[1] == UP || mouseButtonState[1] == RELEASED)
				{
					mouseButtonState[1] = PRESSED;
				}
				else
				{
					mouseButtonState[1] = DOWN;
				}
			}

			//Middle Mouse Button Rleased
			if (event.MouseInput.Event == EMIE_MMOUSE_LEFT_UP)
			{
				//
				if (mouseButtonState[1] != UP)
				{
					mouseButtonState[1] = RELEASED;
				}
			}

			//Right Mouse Button Pressed
			if (event.MouseInput.Event == EMIE_RMOUSE_PRESSED_DOWN)
			{
				//
				if (mouseButtonState[2] == UP || mouseButtonState[2] == RELEASED)
				{
					mouseButtonState[2] = PRESSED;
				}
				else
				{
					mouseButtonState[2] = DOWN;
				}
			}

			//Right Mouse Button Rleased
			if (event.MouseInput.Event == EMIE_RMOUSE_LEFT_UP)
			{
				//
				if (mouseButtonState[2] != UP)
				{
					mouseButtonState[2] = RELEASED;
				}
			}

			eventprocessed = true;
		}


		return eventprocessed;
	}


	//////////////////////
	// Public functions
	//////////////////////
	public:

	inline float mouseWheel()
	{
		return mouse.wheel;
	}

	inline int mouseX()
	{
		return mouse.X;
	}

	inline int mouseY()
	{
		return mouse.Y;
	}

	inline bool leftMouseReleased()
	{
		return (mouseButtonState[0] == RELEASED);
	}

	inline bool leftMouseUp()
	{
		return (mouseButtonState[0] == RELEASED || mouseButtonState[0] == UP);
	}

	inline bool leftMousePressed()
	{
		return (mouseButtonState[0] == PRESSED);
	}

	inline bool leftMouseDown()
	{
		return (mouseButtonState[0] == PRESSED || mouseButtonState[0] == DOWN);
	}

	inline bool middleMouseReleased()
	{
		return (mouseButtonState[1] == RELEASED);
	}
	inline bool middleMouseUp()
	{
		return (mouseButtonState[1] == RELEASED || mouseButtonState[1] == UP);
	}

	inline bool middleMousePressed()
	{
		return (mouseButtonState[1] == PRESSED);
	}

	inline bool middleMouseDown()
	{
		return (mouseButtonState[1] == PRESSED || mouseButtonState[1] == DOWN);
	}

	inline bool rightMouseReleased()
	{
		return (mouseButtonState[2] == RELEASED);
	}
	inline bool rightMouseUp()
	{
		return (mouseButtonState[2] == RELEASED || mouseButtonState[2] == UP);
	}

	inline bool rightMousePressed()
	{
		return (mouseButtonState[2] == PRESSED);
	}

	inline bool rightMouseDown()
	{
		return (mouseButtonState[2] == PRESSED || mouseButtonState[2] == DOWN);
	}

	inline bool keyPressed(unsigned char keycode)
	{
		return (keyState[keycode] == PRESSED);
	}

	inline bool keyDown(unsigned char keycode)
	{
		return (keyState[keycode] == DOWN || keyState[keycode] == PRESSED);
	}

	inline bool keyUp(unsigned char keycode)
	{
		return (keyState[keycode] == UP || keyState[keycode] == RELEASED);
	}

	inline bool keyReleased(unsigned char keycode)
	{
		return (keyState[keycode] == RELEASED);
	}


	// This is used so that the Key States will not be changed during execution of your Main game loop.
	// Place this at the very START of your Main Loop
	inline void endEventProcess()
	{
		processState = ENDED;
	}

	// This is used so that the Key States will not be changed during execution of your Main game loop.
	// Place this function at the END of your Main Loop.
	void startEventProcess()
	{

		processState = STARTED;
		//Keyboard Key States
		for (int i = 0; i < KEY_KEY_CODES_COUNT; i++)
		{
			if (keyState[i] == RELEASED)
			{
				keyState[i] = UP;
			}

			if (keyState[i] == PRESSED)
			{
				keyState[i] = DOWN;
			}
		}
		//Mouse Button States
		for (int i = 0; i <= 2; i++)
		{
			if (mouseButtonState[i] == RELEASED)
			{
				mouseButtonState[i] = UP;
			}

			if (mouseButtonState[i] == PRESSED)
			{
				mouseButtonState[i] = DOWN;
			}
		}
		//Mouse Wheel state
		mouse.wheel = 0.0f;

	}

	void init()
	{
		//KeyBoard States.
		for (int i = 0; i <= KEY_KEY_CODES_COUNT; i++)
		{
			keyState[i] = UP;
		}
		//Mouse states
		for (int i = 0; i <= 2; i++)
		{
			mouseButtonState[i] = UP;
		}
		//Mouse X/Y coordenates.
		mouse.X = 0;
		mouse.Y = 0;
		mouse.wheel = 0.0f;
	}


};
