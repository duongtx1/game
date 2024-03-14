#pragma once

#include <d3d10.h>
#include <d3dx10.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "debug.h"
#include "KeyEventHandler.h"

#define KEYBOARD_BUFFER_SIZE	1024
#define KEYBOARD_STATE_SIZE 256
#define DIRECTINPUT_VERSION 0x0800

class Keyboard
{
	static Keyboard* __instance;

	LPDIRECTINPUT8			di;
	LPDIRECTINPUTDEVICE8	didv;
	BYTE  keyStates[KEYBOARD_STATE_SIZE];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data
	KeyEventHandler* keyHandler;
public:
	static Keyboard* GetInstance();

	void InitKeyboard(HINSTANCE hInstance, HWND hWnd);
	void SetKeyEventHandler(LPKEYEVENTHANDLER handler);
	void ProcessKeyboard();
};

