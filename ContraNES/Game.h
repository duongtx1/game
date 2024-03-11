#pragma once
#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#include <comdef.h>

#include "debug.h"
#include "Keyboard.h"


#define BRICK_WIDTH 3318.0f
#define BRICK_HEIGHT 480.0f

#define BRICK_START_X 0.0f
#define BRICK_START_Y 0.0f


class Game
{
	static Game*	__instance;
	HWND			hWnd;									// Window handle
	HINSTANCE		hInstance;

	ID3D10Device*				pD3DDevice				= NULL;
	ID3D10Texture2D*			texBrick				= NULL;				// Texture object to store brick image
	ID3DX10Sprite*				spriteObject			= NULL;				// Sprite handling object 
	IDXGISwapChain*				pSwapChain				= NULL;
	ID3D10RenderTargetView*		pRenderTargetView		= NULL;
	D3DX10_SPRITE				spriteBrick;

	float brick_x			= BRICK_START_X;
	float brick_y			= BRICK_START_Y;
	int BackBufferWidth		= 0;
	int BackBufferHeight	= 0;

	Keyboard* keyboard;

public:
	void Initialize(HWND hWnd, HINSTANCE hInstance);
	void LoadResource() {};
	void Update(DWORD dt);
	void Render();
	int Run();
	static Game* GetInstance();
	void LoadResources();
	~Game() {};
};

