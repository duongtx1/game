#pragma once

#include <Windows.h>
#include <d3dx10.h>

#include "Texture.h"
#include "Sprite.h"

class CGameObject
{
protected:
	float x;
	float y;

	// This should be a pointer to an object containing all graphic/sound/audio assets for rendering this object. 
	// For now, just a pointer to a single texture
	LPTEXTURE texture;
public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	float GetX() { return x; }
	float GetY() { return y; }

	CGameObject(float x = 0.0f, float y = 0.0f, LPTEXTURE texture = NULL);

	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;

	~CGameObject();
};
typedef CGameObject* LPGAMEOBJECT;

#define ID_ANI_BRICK 10000
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

class CBrick : public CGameObject {
	LPSPRITE sprite;
public:
	CBrick(float x, float y, LPTEXTURE tex) : CGameObject(x, y, tex) {
		sprite = new CSprite(0, 0, 16, 16, texture);
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};