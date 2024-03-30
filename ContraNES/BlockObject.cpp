#include "BlockObject.h"
CBlockObject::CBlockObject(float x, float y, int tileLength = 1) :CGameObject(x, y)
{
	tile_length = tileLength;
	isBlock = 1;
}
void CBlockObject::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x,
		top = y;
	right = x + 16 * tile_length,
		bottom = y - 0.5f;
}