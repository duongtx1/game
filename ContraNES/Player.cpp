#include "Player.h"
#include "Game.h"
#include "debug.h"

#define CONTRA_VX 0.1f
#define CONTRA_WIDTH 14

void CPlayer::Update(DWORD dt)
{
	x += vx * dt;
	//DebugOut(L"%0.2f\t\t%0.2f\t\n", x, y);
	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	if (x <= 0 || x >= 4000 - CONTRA_WIDTH) {

		vx = -vx;

		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= BackBufferWidth - CONTRA_WIDTH)
		{
			x = (float)(BackBufferWidth - CONTRA_WIDTH);
		}
	}
}

void CPlayer::Render()
{
	sprite->Draw(x, y);
}

void CPlayer::KeyState(BYTE* state)
{
	this->keyStates = state;
	if (IsKeyDown(DIK_RIGHT))
	{
		vx = 0.1f;
	}
	else if (IsKeyDown(DIK_LEFT))
	{
		vx = -0.1f;
	}
	else if (IsKeyDown(DIK_DOWN)) {
		y--;
	}
	else if (IsKeyDown(DIK_UP)) {
		y++;
	}
	else if (IsKeyDown(DIK_A)) {
		Stop();
	}

}

void CPlayer::OnKeyDown(int KeyCode)
{

}

void CPlayer::OnKeyUp(int KeyCode)
{
}
