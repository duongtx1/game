#pragma once
#include "GameObject.h"
#include "KeyEventHandler.h"
#include "Sprite.h"


#define BILL_WIDTH 14

#define BILL_RUN_SPEED 0.1f
#define BILL_JUMP_SPEED 0.5f

#define BILL_GRAVITY 0.0025f

#define BILL_STATE_IDLE 0
#define BILL_STATE_RUNNING_RIGHT 100
#define BILL_STATE_RUNNING_LEFT 200

#define BILL_STATE_JUMP			300
#define BILL_STATE_RELEASE_JUMP    301

#define BILL_STATE_LIE				400
#define BILL_STATE_LIE_RELEASE		401

#define ID_ANI_BILL_IDLE_RIGHT 500
#define ID_ANI_BILL_IDLE_LEFT 501

#define ID_ANI_RUNNING_RIGHT 600
#define ID_ANI_RUNNING_LEFT 601

#define ID_ANI_JUMPING_RIGHT 700
#define ID_ANI_JUMPING_LEFT 701

#define ID_ANI_LYING_RIGHT 800
#define ID_ANI_LYING_LEFT 801

#define ID_ANI_UP_RIGHT 900
#define ID_ANI_UP_LEFT 901

#define BILL_STATE_UP	1000
#define BILL_STATE_UP_RELEASE 1001	

#define CONTRA_START_VY 0.0f

class CPlayer : public CGameObject, public KeyEventHandler
{
	int isOnGround = 0;
public:
	CPlayer(float x, float y, float vx, float vy) :CGameObject(x, y)
	{
		this->vx = vx;
		this->vy = vy;
	};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* gameObject = NULL);
	void Render();

	void KeyState(BYTE* state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void Stop() {
		vx = 0;
	}
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void OnCollisionWith(LPCOLLISIONEVENT e, DWORD dt);
	int IsCollidable() { return 1; }
};