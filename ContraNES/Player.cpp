#include "Player.h"
#include "Game.h"
#include "debug.h"

#define CONTRA_VX 0.1f
#define CONTRA_WIDTH 14

#define GROUND_Y 100

void CPlayer::Update(DWORD dt)
{
	x += vx * dt;
	//y += vy * dt;
	//vy += BILL_GRAVITY * dt;

	/*if (y > GROUND_Y) {
		vy = 0;
		y = GROUND_Y;
	}*/
	DebugOut(L"%0.2f\t\t%0.2f\t\n", x, y);
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
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	if (y < GROUND_Y) {
		if (nx >= 0) {
			aniId = ID_ANI_JUMPING_RIGHT;
		}
		else {
			aniId = ID_ANI_JUMPING_LEFT;
		}
	}
	else
		if (state == BILL_STATE_LIE) {
			if (nx >= 0) {
				aniId = ID_ANI_LYING_RIGHT;
			}
			else {
				aniId = ID_ANI_LYING_LEFT;
			}
		}
		else if (state == BILL_STATE_UP) {
			if (nx >= 0) {
				aniId = ID_ANI_UP_RIGHT;
			}
			else {
				aniId = ID_ANI_UP_LEFT;
			}
		}
		else {
			if (vx == 0) {
				if (nx >= 0) {
					aniId = ID_ANI_BILL_IDLE_RIGHT;
				}
				else {
					aniId = ID_ANI_BILL_IDLE_LEFT;
				}
			}
			else if (vx > 0) {
				aniId = ID_ANI_RUNNING_RIGHT;
			}
			else {
				aniId = ID_ANI_RUNNING_LEFT;
			}
		}

	if (aniId == -1) {
		aniId = ID_ANI_BILL_IDLE_RIGHT;
	}

	animations->Get(aniId)->Render(x, y);
}

void CPlayer::KeyState(BYTE* state)
{
	this->keyStates = state;
	if (IsKeyDown(DIK_D))
	{
		SetState(BILL_STATE_RUNNING_RIGHT);

	}
	else if (IsKeyDown(DIK_A))
	{
		SetState(BILL_STATE_RUNNING_LEFT);

	}
	else if (IsKeyDown(DIK_S)) {
		SetState(BILL_STATE_LIE);
	}
	else if (IsKeyDown(DIK_W)) {
		SetState(BILL_STATE_UP);
	}
	else if (IsKeyDown(DIK_UPARROW)) {
		y--;
	}
	else if (IsKeyDown(DIK_DOWNARROW)) {
		y++;
	}
	else
		Stop();
}

void CPlayer::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_SPACE:
		SetState(BILL_STATE_JUMP); break;

	case DIK_S:
		SetState(BILL_STATE_LIE); break;

	case DIK_W:
		SetState(BILL_STATE_UP); break;
	case DIK_3:
		CScenes::GetInstance()->InitiateSwitchScene(2); break;
	}

}

void CPlayer::OnKeyUp(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_K:
		SetState(BILL_STATE_RELEASE_JUMP); break;
	case DIK_S:
		SetState(BILL_STATE_LIE_RELEASE); break;
	case DIK_W:
		SetState(BILL_STATE_UP_RELEASE); break;
	}
}

void CPlayer::SetState(int state) {
	switch (state)
	{
	case BILL_STATE_RUNNING_RIGHT:
		if (IsKeyDown(DIK_S) || IsKeyDown(DIK_W)) break;
		vx = BILL_RUN_SPEED;
		nx = 1;
		break;
	case BILL_STATE_RUNNING_LEFT:
		if (IsKeyDown(DIK_S) || IsKeyDown(DIK_W)) break;
		vx = -BILL_RUN_SPEED;
		nx = -1;
		break;
	case BILL_STATE_JUMP:
		if (IsKeyDown(DIK_S)) break;
		if (y == GROUND_Y) {
			vy = -BILL_JUMP_SPEED;
		}
		break;
		/*case BILL_STATE_RELEASE_JUMP:
			if (vy < 0) vy += BILL_JUMP_SPEED / 2;
			break;*/
	case BILL_STATE_LIE:
		if (y == GROUND_Y) {
			state = BILL_STATE_IDLE;
			//isLying = true;
			vx = 0; vy = 0;
		}
		break;
	case BILL_STATE_LIE_RELEASE:
		/*	isLying = false;*/
		state = BILL_STATE_IDLE;
		break;
	case BILL_STATE_IDLE:
		vx = 0.0f;
		break;
	case BILL_STATE_UP:
		if (y == GROUND_Y) {
			state = BILL_STATE_IDLE;
			//isLying = true;
			vx = 0; vy = 0;
		}
		break;
	case BILL_STATE_UP_RELEASE:
		/*	isLying = false;*/
		state = BILL_STATE_IDLE;
		break;
	}
	CGameObject::SetState(state);
}