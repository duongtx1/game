#pragma once
#include "GameObject.h"
#include "KeyEventHandler.h"
#include "Sprite.h"

class CPlayer : public CGameObject, public KeyEventHandler
{
	float vx;
	float vy;
	LPSPRITE sprite = NULL;
public:
	CPlayer(float x, float y, float vx, float vy, LPTEXTURE texture) :CGameObject(x, y, texture)
	{
		sprite = new CSprite(0, 0, 25, 34, texture);

		this->vx = vx;
		this->vy = vy;
	};
	void Update(DWORD dt);
	void Render();

	void KeyState(BYTE* state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void Stop() {
		vx = 0;
	}
};