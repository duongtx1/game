#pragma once
#include <dinput.h>
#include "KeyEventHandler.h"

#define KEYBOARD_BUFFER_SIZE	1024
#define KEYBOARD_STATE_SIZE 256
#define DIRECTINPUT_VERSION 0x0800

class Keyboard
{
	LPDIRECTINPUT8			di;
	LPDIRECTINPUTDEVICE8	didv;
	BYTE  keyStates[KEYBOARD_STATE_SIZE];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data
	KeyEventHandler* keyHandler;
public:
	void InitKeyboard(HINSTANCE hInstance, HWND hWnd, KeyEventHandler* keyHandler);
	void ProcessKeyboard();
};

