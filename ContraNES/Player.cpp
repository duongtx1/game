#include "Player.h"
#include "Game.h"
#include "debug.h"
#include "PlayScene.h"
#include "BlockObject.h"
#include "Camera.h"

#define CONTRA_VX 0.1f
#define CONTRA_WIDTH 14

#define GROUND_Y 100

void CPlayer::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;
	//vy += BILL_GRAVITY * dt;

	/*if (y > GROUND_Y) {
		vy = 0;
		y = GROUND_Y;
	}*/
	//DebugOut(L"%0.2f\t\t%0.2f\t\n", x, y);

	int mapWidth = Camera::GetInstance()->getMapWidth();
	if (x <= 0 || x >= mapWidth - CONTRA_WIDTH) {
		vx = -vx;
		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= mapWidth - CONTRA_WIDTH)
		{
			x = (float)(mapWidth - CONTRA_WIDTH);
		}
	}
	int mapHeight = Camera::GetInstance()->getMapHeight();
	if (y <= 0 || y >= mapHeight - 35) {
		vy = -0;
		if (x <= 0)
		{
			x = 0;
		}
		/*else if (x >= mapHeight - CONTRA_WIDTH)
		{
			x = (float)(mapHeight - CONTRA_WIDTH);
		}*/
	}
	isOnGround = 0;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPlayer::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	if (!isOnGround) {
		if (nx >= 0) {
			aniId = ID_ANI_BILL_IDLE_RIGHT;
		}
		else {
			aniId = ID_ANI_BILL_IDLE_RIGHT;
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
	RenderBoundingBox();
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
	case DIK_1:
		CScenes::GetInstance()->InitiateSwitchScene(1); break;
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
		if (isOnGround) {
			vy = -BILL_JUMP_SPEED;
		}
		break;
		/*case BILL_STATE_RELEASE_JUMP:
			if (vy < 0) vy += BILL_JUMP_SPEED / 2;
			break;*/
	case BILL_STATE_LIE:
		if (y == GROUND_Y) {
			state = BILL_STATE_LIE;
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

void CPlayer::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	if (state == BILL_STATE_IDLE)
	{
		right = x + 24;
		bottom = y - 36;
		return;
	}
	if (state == BILL_STATE_LIE)
	{
		right = x + 33;
		bottom = y - 18;
		return;
	}
	/*if (state == BILL_STATE_SWIM || state == BILL_STATE_SWIM_MOVE)
	{
		right = x + 17;
		bottom = top - 25;
		return;
	}
	if (state == BILL_STATE_DEAD)
	{
		right = x + 21;
		bottom = y - 12;
		return;
	}*/
	right = x + 24;
	bottom = y - 36;
}

void CPlayer::OnCollisionWith(LPCOLLISIONEVENT e, DWORD dt)
{
	if (dynamic_cast<CBlockObject*>(e->obj))
	{
		if (e->ny > 0)
		{
			vy = 0;
			if (state == BILL_STATE_JUMP)
				SetState(BILL_STATE_IDLE);

		}
		else if (e->ny < 0)
		{
			vy = 0;
			isOnGround = 1;
		}
	}
	else
	{
		if (e->ny > 0 && e->obj->IsBlocking())
		{
			vy = 0;
			if (state == BILL_STATE_JUMP)
				SetState(BILL_STATE_IDLE);

		}
		if (e->ny <= 0 && e->obj->IsBlocking())
		{
			vy = 0;
		}

	}
}
