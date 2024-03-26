#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Keyboard.h"

class CPlayScene : public CScene, public KeyEventHandler
{
protected:
	CPlayer* player;
	CMap* map;

	vector<LPGAMEOBJECT> objects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_MAP(string line);

	void _ParseSectionAnimations(string line);
	void _ParseSectionSprites(string line);

	void LoadAssets(LPCWSTR assetFile);

public:
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
	void OnKeyDown(int KeyCode);
};

typedef CPlayScene* LPPLAYSCENE;

