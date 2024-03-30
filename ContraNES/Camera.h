#pragma once
#include <Windows.h>

#include "Player.h"
#include "Game.h"
class Camera
{
	static Camera* instance;

	float camx;
	float camy;

	int width;
	int height;

	int mapWidth, mapHeight;
	bool isVertical;
public:

	void Init(int w, int h, int mw, int mh, bool isVertical);
	void setPosCamera(float x, float y);
	D3DXVECTOR2 getCamPosition();


	// TODO: cai nay o trong class Map
	float getMapWidth() { return mapWidth; }
	float getMapHeight() { return mapHeight; }
	int getWidth() { return width; }
	int getHeight() { return height; }

	void Update(DWORD dt, CPlayer* c);

	static Camera* GetInstance();

};
typedef Camera* LPCAMERA;