#include "Player.h"
#include "Game.h"

#define CONTRA_VX 0.1f
#define CONTRA_WIDTH 14

void CPlayer::Update(DWORD dt)
{
	x += vx * dt;
	DebugOut(L"%0.2f\n", x);
	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	//if (x <= 0 || x >= BackBufferWidth - CONTRA_WIDTH) {

		//vx = -vx;

		//if (x <= 0)
		//{
			//x = 0;
		//}
		//else if (x >= BackBufferWidth - CONTRA_WIDTH)
		//{
			//x = (float)(BackBufferWidth - CONTRA_WIDTH);
		//}
	//}
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

}

void CPlayer::OnKeyDown(int KeyCode)
{

}

void CPlayer::OnKeyUp(int KeyCode)
{
}
