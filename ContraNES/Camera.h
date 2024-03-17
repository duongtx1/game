#pragma once
#include <Windows.h>

class Camera
{
	static Camera* instance;

	float camx;
	float camy;

	int width;
	int height;

	float vx = 0.2f;
	float vy = 0.2f;

public:

	void Init(int w, int h);
	void setPosCamera(float x, float y);

	float getX() { return camx; }
	float getY() { return camy; }
	int getWidth() { return width; }
	int getHeight() { return height; }

	void Update(DWORD dt);

	static Camera* GetInstance();

};
typedef Camera* LPCAMERA;