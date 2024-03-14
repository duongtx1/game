#pragma once
#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>

#include "Texture.h"
#include "GameObject.h"
#include "Keyboard.h"
#include "Player.h"

#define MAX_FRAME_RATE 60
#define BACKGROUND_COLOR D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.0f)


#define CONTRA_START_X 10.0f
#define CONTRA_START_Y 100.0f
#define CONTRA_START_VX 0.1f
#define CONTRA_START_VY 0.1f

#define BRICK_X 10.0f
#define BRICK_Y 120.0f

#define TEXTURE_PATH_BRICK L"brick.png"
#define TEXTURE_PATH_CONTRA L"LanceStandingL.png"

#define TEXTURE_PATH_MISC L"misc.png"
/*
	Our simple game framework
*/
class CGame
{
	static CGame* __instance;
	HWND hWnd;									// Window handle

	int backBufferWidth = 0;					// Backbuffer width & height, will be set during Direct3D initialization
	int backBufferHeight = 0;

	ID3D10Device* pD3DDevice = NULL;
	IDXGISwapChain* pSwapChain = NULL;
	ID3D10RenderTargetView* pRenderTargetView = NULL;
	ID3D10BlendState* pBlendStateAlpha = NULL;			// To store alpha blending state

	ID3DX10Sprite* spriteObject = NULL;				// Sprite handling object 

	HINSTANCE hInstance;

	Keyboard* keyboard;

	CPlayer* player;

	LPTEXTURE texPlayer = NULL;
	LPTEXTURE texBrick = NULL;
	LPTEXTURE texMisc = NULL;
public:
	// Init DirectX, Sprite Handler
	void Init(HWND hWnd, HINSTANCE hInstance);

	//
	// Draw a portion or ALL the texture at position (x,y) on the screen
	// rect : if NULL, the whole texture will be drawn
	//        if NOT NULL, only draw that portion of the texture 
	void Draw(float x, float y, LPTEXTURE tex, RECT* rect = NULL);

	void Draw(float x, float y, LPTEXTURE tex, int l, int t, int r, int b)
	{
		RECT rect;
		rect.left = l;
		rect.top = t;
		rect.right = r;
		rect.bottom = b;
		this->Draw(x, y, tex, &rect);
	}

	LPTEXTURE LoadTexture(LPCWSTR texturePath);

	ID3D10Device* GetDirect3DDevice() { return this->pD3DDevice; }
	IDXGISwapChain* GetSwapChain() { return this->pSwapChain; }
	ID3D10RenderTargetView* GetRenderTargetView() { return this->pRenderTargetView; }
	ID3DX10Sprite* GetSpriteHandler() { return this->spriteObject; }
	ID3D10BlendState* GetAlphaBlending() { return pBlendStateAlpha; };

	int GetBackBufferWidth() { return backBufferWidth; }
	int GetBackBufferHeight() { return backBufferHeight; }

	static CGame* GetInstance();
	void LoadResources();
	void Update(DWORD dt);
	void Render();
	int Run();

	~CGame();
};