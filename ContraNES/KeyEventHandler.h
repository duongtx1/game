#pragma once
#include <Windows.h>
#include <dinput.h>
/*
	Abstract class to define keyboard event handlers
*/
class KeyEventHandler
{
protected:
	BYTE* keyStates;									// DirectInput keyboard state buffer 
public:
	virtual void KeyState(BYTE* state) {}
	virtual void OnKeyDown(int KeyCode) {}
	virtual void OnKeyUp(int KeyCode) {}

	int IsKeyDown(int KeyCode)
	{
		return (keyStates[KeyCode] & 0x80) > 0;
	}
};

typedef KeyEventHandler* LPKEYEVENTHANDLER;
