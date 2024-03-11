#pragma once
#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>
class Game
{
	static Game* __instance;
	HWND hWnd;									// Window handle
	HINSTANCE hInstance;
public:
	void Initialize(HWND hWnd, HINSTANCE hInstance);
	void LoadResource() {};
	void Update(DWORD dt) {};
	void Render() {};
	int Run();
	static Game* GetInstance();
	~Game() {};
};

