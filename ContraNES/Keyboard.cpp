#include "Keyboard.h"
#include "debug.h"

void Keyboard::InitKeyboard(HINSTANCE hInstance, HWND hWnd, KeyEventHandler* handler)
{
	// Keyboard
	HRESULT hr2 = DirectInput8Create(
		hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8, (VOID**)&di, NULL
	);
	if (hr2 != DI_OK)
	{
		DebugOut(L"[ERROR] DirectInput8Create failed!\n");
		return;
	}

	hr2 = di->CreateDevice(GUID_SysKeyboard, &didv, NULL);

	if (hr2 != DI_OK)
	{
		DebugOut(L"[ERROR] CreateDevice failed!\n");
		return;
	}

	hr2 = didv->SetDataFormat(&c_dfDIKeyboard);

	hr2 = didv->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	hr2 = didv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	hr2 = didv->Acquire();
	if (hr2 != DI_OK)
	{
		DebugOut(L"[ERROR] DINPUT8::Acquire failed!\n");
		return;
	}

	keyHandler = handler;

	DebugOut(L"[INFO] Keyboard has been initialized successfully\n");
}

void Keyboard::ProcessKeyboard() {
	HRESULT hr;

	// Collect all key states first
	hr = didv->GetDeviceState(sizeof(keyStates), keyStates);
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			HRESULT h = didv->Acquire();
			if (h == DI_OK)
			{
				DebugOut(L"[INFO] Keyboard re-acquired!\n");
			}
			else return;
		}
		else
		{
			//DebugOut(L"[ERROR] DINPUT::GetDeviceState failed. Error: %d\n", hr);
			return;
		}
	}

	keyHandler->KeyState((BYTE*)&keyStates);

	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	hr = didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
	if (FAILED(hr))
	{
		DebugOut(L"[ERROR] DINPUT::GetDeviceData failed. Error: %d\n", hr);
		return;
	}

	// Scan through all buffered events, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = keyEvents[i].dwOfs;
		int KeyState = keyEvents[i].dwData;
		if ((KeyState & 0x80) > 0) {
			keyHandler->OnKeyDown(KeyCode); 
		}
		else {
			keyHandler->OnKeyUp(KeyCode);
		}
	}
}