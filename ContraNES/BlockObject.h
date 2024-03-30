#pragma once
#include "GameObject.h"
class CBlockObject : public CGameObject
{
private:
	int tile_length;
	int isBlock;
public:
	CBlockObject(float x, float y, int tileLength);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int IsCollidable() { return 1; };
	virtual int IsBlocking() { return isBlock; };
	void setIsBlocking(int value) { isBlock = value; };
	void Render() {}
};