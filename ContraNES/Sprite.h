#pragma once

#include "Texture.h"

class CSprite
{
	int id;				// Sprite ID in the sprite database

	int left;
	int top;
	int right;
	int bottom;

	LPTEXTURE texture;
	D3DX10_SPRITE sprite;
	D3DXMATRIX matScaling;
public:
	CSprite(int left, int top, int right, int bottom, LPTEXTURE tex, int id = 0);

	void Draw(float x, float y);
};

typedef CSprite* LPSPRITE;