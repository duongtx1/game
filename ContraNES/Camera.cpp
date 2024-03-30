#include "Camera.h"

Camera* Camera::instance = NULL;

void Camera::Init(int w, int h, int mw, int mh, bool isVertical)
{
	width = w;
	height = h;
	mapWidth = mw; mapHeight = mh;
	this->isVertical = isVertical;
	if (this->isVertical) {
		camx = 0;
	}
	else {
		camy = 0;
	}
}

void Camera::setPosCamera(float x, float y)
{
	camx = x;
	camy = y;
}

void Camera::Update(DWORD dt, CPlayer* c)
{
	float cx, cy;
	c->GetPosition(cx, cy);

	CGame* game = CGame::GetInstance();

	if (isVertical) {

		camy = cy - game->GetBackBufferHeight() / 2;
		if (camy < 0)
		{
			camy = 0;
		}
		if (cy > mapHeight - height) {
			camy = mapHeight - height;
		}
	}
	else {
		camx = cx - game->GetBackBufferWidth() / 2;

		if (cx < 0) camx = 0;
		if (camx > mapWidth - width - 12) {
			camx = mapWidth - width - 12;
		}
	}

	DebugOut(L"%0.2f\t", camx);
}

D3DXVECTOR2 Camera::getCamPosition() {
	camx = (FLOAT)floor(camx);
	camy = (FLOAT)floor(camy);

	return D3DXVECTOR2(camx, camy);
}


Camera* Camera::GetInstance()
{
	if (instance == NULL) instance = new Camera();
	return instance;
}