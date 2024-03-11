#include "Game.h"

#define MAX_FRAME_RATE 30;
Game* Game::__instance = NULL;

void Game::Initialize(HWND hWnd, HINSTANCE hInstance)
{
	this->hWnd = hWnd;
	this->hInstance = hInstance;
}

int Game::Run()
{
		MSG msg;
		int done = 0;
		ULONGLONG frameStart = GetTickCount64();
		ULONGLONG tickPerFrame = 1000 / MAX_FRAME_RATE;

		while (!done)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT) done = 1;

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			ULONGLONG now = GetTickCount64();
			ULONGLONG dt = now - frameStart;

			if (dt >= tickPerFrame) {
				frameStart = now;
				Update((DWORD)dt);
				Render();
			}
			else {
				Sleep((DWORD)(tickPerFrame - dt));
			}
		}

		return 1;
}

Game* Game::GetInstance()
{
	if (__instance == NULL) __instance = new Game();
	return __instance;
}
