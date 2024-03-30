#pragma once

#include <Windows.h>
#include <d3dx10.h>

#include "Texture.h"
#include "Sprite.h"
#include "Collision.h"

#define ID_TEX_BBOX -100		// special texture to draw object bounding box
#define BBOX_ALPHA 0.25f		// Bounding box transparency

class CGameObject
{
protected:
	float x, y;
	float vx, vy;

	int nx;
	int state;

	bool isDeleted;
public:
	CGameObject();
	CGameObject(float x, float y) :CGameObject() { this->x = x; this->y = y; this->vx = 0; this->vy = 0; }

	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void GetSpeed(float& vx, float& vy) {
		vx = this->vx; vy = this->vy;
	}

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* gameObject = NULL) {}
	virtual void Render() = 0;

	bool IsDeleted() { return isDeleted; }

	void RenderBoundingBox();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;

	void SetState(int state) { this->state = state; }
	int GetState() { return this->state; }

	//
	// Collision ON or OFF ? This can change depending on object's state. For example: die
	//
	virtual int IsCollidable() { return 0; };

	// When no collision has been detected (triggered by CCollision::Process)
	virtual void OnNoCollision(DWORD dt) {};

	// When collision with an object has been detected (triggered by CCollision::Process)
	virtual void OnCollisionWith(LPCOLLISIONEVENT e, DWORD dt = 0) {};
	virtual int IsBlocking() { return 0; };

	~CGameObject();
};
typedef CGameObject* LPGAMEOBJECT;
