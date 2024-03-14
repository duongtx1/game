#pragma once
#include "GameObject.h"
#include "KeyEventHandler.h"

class CPlayer : public CGameObject, public KeyEventHandler
{
	float vx;
	float vy;
public:
	CPlayer(float x, float y, float vx, float vy, LPTEXTURE texture) :CGameObject(x, y, texture)
	{
		this->vx = vx;
		this->vy = vy;
	};
	void Update(DWORD dt);

	void KeyState(BYTE* state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
};