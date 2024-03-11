#include "Game.h"

#define MAX_FRAME_RATE 30;
#define TEXTURE_PATH_BRICK L"ContraMapStage1BG.jpg"
// Each color is from 0.0f to 1.0f  ( 0/255 to 255/255 ) 
#define BACKGROUND_COLOR D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f)

Game* Game::__instance = NULL;

void Game::Initialize(HWND hWnd, HINSTANCE hInstance)
{
	this->hWnd = hWnd;
	this->hInstance = hInstance;

	// retrieve client area width & height so that we can create backbuffer height & width accordingly 
	RECT r;
	GetClientRect(hWnd, &r);

	BackBufferWidth = r.right + 1;
	BackBufferHeight = r.bottom + 1;

	// Create & clear the DXGI_SWAP_CHAIN_DESC structure
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// Fill in the needed values
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = BackBufferWidth;
	swapChainDesc.BufferDesc.Height = BackBufferHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	HRESULT hr = S_OK;

	// Create the D3D device and the swap chain
	hr = D3D10CreateDeviceAndSwapChain(NULL,
		D3D10_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		D3D10_SDK_VERSION,
		&swapChainDesc,
		&pSwapChain,
		&pD3DDevice);

	if (hr != S_OK)
	{
		_com_error err(hr);
		LPCTSTR errMsg = err.ErrorMessage();

		DebugOut((wchar_t*)L"[ERROR] D3D10CreateDeviceAndSwapChain has failed %s %d %d %s\n", _W(__FILE__), __LINE__, hr, errMsg);
		return;
	}

	// Get the back buffer from the swapchain
	ID3D10Texture2D* pBackBuffer;
	hr = pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&pBackBuffer);
	if (hr != S_OK)
	{
		DebugOut((wchar_t*)L"[ERROR] pSwapChain->GetBuffer has failed %s %d", _W(__FILE__), __LINE__);
		return;
	}

	// create the render target view
	hr = pD3DDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);

	// release the back buffer
	pBackBuffer->Release();

	// Make sure the render target view was created successfully
	if (hr != S_OK)
	{
		DebugOut((wchar_t*)L"[ERROR] CreateRenderTargetView has failed %s %d", _W(__FILE__), __LINE__);
		return;
	}

	// set the render target
	pD3DDevice->OMSetRenderTargets(1, &pRenderTargetView, NULL);

	// create and set the viewport
	D3D10_VIEWPORT viewPort;
	viewPort.Width = BackBufferWidth;
	viewPort.Height = BackBufferHeight;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	pD3DDevice->RSSetViewports(1, &viewPort);


	// create the sprite object to handle sprite drawing 
	hr = D3DX10CreateSprite(pD3DDevice, 0, &spriteObject);

	// Make sure the sprite creation was successful
	if (hr != S_OK)
	{
		DebugOut((wchar_t*)L"[ERROR] D3DX10CreateSprite has failed %s %d", _W(__FILE__), __LINE__);
		return;
	}

	D3DXMATRIX matProjection;

	// Create the projection matrix using the values in the viewport
	D3DXMatrixOrthoOffCenterLH(&matProjection,
		(float)viewPort.TopLeftX,
		(float)viewPort.Width,
		(float)viewPort.TopLeftY,
		(float)viewPort.Height,
		0.1f,
		10);
	hr = spriteObject->SetProjectionTransform(&matProjection);

	DebugOut((wchar_t*)L"[INFO] InitDirectX has been successful\n");

	keyboard = new Keyboard();
	KeyEventHandler* keyHandler = new CSampleKeyHandler();
	keyboard->InitKeyboard(hInstance, hWnd, keyHandler);
	return;
}


void Game::Update(DWORD dt)
{
	keyboard->ProcessKeyboard();
}

void Game::Render()
{
	if (pD3DDevice != NULL)
	{
		// clear the target buffer
		pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);

		// start drawing the sprites
		spriteObject->Begin(D3DX10_SPRITE_SORT_TEXTURE);

		// The translation matrix to be created
		D3DXMATRIX matTranslation;
		// Create the translation matrix
		D3DXMatrixTranslation(&matTranslation, brick_x, (BackBufferHeight - brick_y), 0.1f);

		// Scale the sprite to its correct width and height
		D3DXMATRIX matScaling;
		D3DXMatrixScaling(&matScaling, BRICK_WIDTH, BRICK_HEIGHT, 1.0f);

		// Setting the sprite�s position and size
		spriteBrick.matWorld = (matScaling * matTranslation);

		spriteObject->DrawSpritesImmediate(&spriteBrick, 1, 0, 0);

		// Finish up and send the sprites to the hardware
		spriteObject->End();
		// display the next item in the swap chain
		pSwapChain->Present(0, 0);
	}
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

/*
	Load game resources. In this example, we only load a brick image
*/
void Game::LoadResources()
{
	ID3D10Resource* pD3D10Resource = NULL;

	// Loads the texture into a temporary ID3D10Resource object
	HRESULT hr = D3DX10CreateTextureFromFile(pD3DDevice,
		TEXTURE_PATH_BRICK,
		NULL,
		NULL,
		&pD3D10Resource,
		NULL);

	// Make sure the texture was loaded successfully
	if (FAILED(hr))
	{
		DebugOut((wchar_t*)L"[ERROR] Failed to load texture file: %s \n", TEXTURE_PATH_BRICK);
		return;
	}

	// Translates the ID3D10Resource object into a ID3D10Texture2D object
	pD3D10Resource->QueryInterface(__uuidof(ID3D10Texture2D), (LPVOID*)&texBrick);
	pD3D10Resource->Release();

	if (!texBrick) {
		DebugOut((wchar_t*)L"[ERROR] Failed to convert from ID3D10Resource to ID3D10Texture2D \n");
		return;
	}

	// Get the texture details
	D3D10_TEXTURE2D_DESC desc;
	texBrick->GetDesc(&desc);

	// Create a shader resource view of the texture
	D3D10_SHADER_RESOURCE_VIEW_DESC SRVDesc;

	// Clear out the shader resource view description structure
	ZeroMemory(&SRVDesc, sizeof(SRVDesc));

	// Set the texture format
	SRVDesc.Format = desc.Format;
	// Set the type of resource
	SRVDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = desc.MipLevels;

	ID3D10ShaderResourceView* gSpriteTextureRV = NULL;

	pD3DDevice->CreateShaderResourceView(texBrick, &SRVDesc, &gSpriteTextureRV);

	// Set the sprites shader resource view
	spriteBrick.pTexture = gSpriteTextureRV;

	// top-left location in U,V coords
	spriteBrick.TexCoord.x = 0;
	spriteBrick.TexCoord.y = 0;

	// Determine the texture size in U,V coords
	spriteBrick.TexSize.x = 1.0f;
	spriteBrick.TexSize.y = 1.0f;

	// Set the texture index. Single textures will use 0
	spriteBrick.TextureIndex = 0;

	// The color to apply to this sprite, full color applies white.
	spriteBrick.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);


	DebugOut((wchar_t*)L"[INFO] Texture loaded Ok: %s \n", TEXTURE_PATH_BRICK);
}
