#pragma once
#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#include <unordered_map>
#include <string>

#include "Animations.h"

using namespace std;

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include "Texture.h"
#include "KeyEventHandler.h"
#include "Player.h"
#include "Map.h"
#include "Scenes.h"

#define MAX_FRAME_RATE 100
#define KEYBOARD_BUFFER_SIZE 1024
#define KEYBOARD_STATE_SIZE 256

#define CONTRA_START_X 0.0f
#define CONTRA_START_Y 0.0f
#define CONTRA_START_VX 0.1f
#define CONTRA_START_VY 0.1f

#define BRICK_X 10.0f
#define BRICK_Y 120.0f

//#define TEXTURE_PATH_CONTRA L"LanceStandingL.png"
#define TEXTURE_PATH_CONTRA L"Contra_Sprites.png"


/*
	Our simple game framework
*/
class CGame : public KeyEventHandler
{
	static CGame* __instance;
	HWND hWnd;									// Window handle

	int backBufferWidth = 0;					// Backbuffer width & height, will be set during Direct3D initialization
	int backBufferHeight = 0;

	ID3D10Device* pD3DDevice = NULL;
	IDXGISwapChain* pSwapChain = NULL;
	ID3D10RenderTargetView* pRenderTargetView = NULL;
	ID3D10BlendState* pBlendStateAlpha = NULL;			// To store alpha blending state

	LPD3DX10SPRITE spriteObject;						// Sprite handling object, BIG MYSTERY: it has to be in this place OR will lead to access violation in D3D11.dll ????

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[KEYBOARD_STATE_SIZE];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;

	float cam_x = 0.0f;
	float cam_y = 0.0f;

	HINSTANCE hInstance;

	ID3D10SamplerState* pPointSamplerState;

	int current_scene;
	int next_scene = -1;
	CPlayer* player;
	CScenes* scenes;

	LPTEXTURE texPlayer = NULL;
	vector<LPGAMEOBJECT> objects;

	/*void _ParseSection_SETTINGS(string line);
	void _ParseSection_SCENES(string line);*/

public:
	// Init DirectX, Sprite Handler
	void Init(HWND hWnd, HINSTANCE hInstance);

	//
	// Draw a portion or ALL the texture at position (x,y) on the screen. (x,y) is at the CENTER of the image
	// rect : if NULL, the whole texture will be drawn
	//        if NOT NULL, only draw that portion of the texture 
	void Draw(float x, float y, LPTEXTURE tex, RECT* rect = NULL, float alpha = 1.0f, int sprite_width = 0, int sprite_height = 0);

	void Draw(float x, float y, LPTEXTURE tex, int l, int t, int r, int b, float alpha = 1.0f, int sprite_width = 0, int sprite_height = 0)
	{
		RECT rect;
		rect.left = l;
		rect.top = t;
		rect.right = r;
		rect.bottom = b;
		this->Draw(x, y, tex, &rect, alpha, sprite_width, sprite_height);
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

	void SetPointSamplerState();

	void SetCamPos(float x, float y) { cam_x = x; cam_y = y; }
	void GetCamPos(float& x, float& y) {
		x = cam_x; y = cam_y;
	}

	//LPSCENE GetCurrentScene() { return scenes[current_scene]; }
	CPlayer* GetPlayer() { return player; }


	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void Update(DWORD dt);
	void Render();
	void Load(LPCWSTR gameFile);

	~CGame();
};
typedef CGame* LPGAME;

