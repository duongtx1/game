#include "Camera.h"
#include "Player.h"
#include "Game.h"

Camera* Camera::instance = NULL;

void Camera::Init(int w, int h)
{
	width = w;
	height = h;
}

void Camera::setPosCamera(float x, float y)
{
	camx = x;
	camy = y;
}

void Camera::Update(DWORD dt)
{
	/*CPlayer* player = CGame::GetInstance()->GetPlayer();
	if (player->GetX() > camx + width / 2)
		camx += vx * dt;*/

		//int mapwidth = game->GetCurrentScene().GetMapWidth();
		//if (camx > mapwidth - width)
			//camx = mapwidth - width;
}


Camera* Camera::GetInstance()
{
	if (instance == NULL) instance = new Camera();
	return instance;
}