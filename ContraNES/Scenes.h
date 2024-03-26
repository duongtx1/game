#pragma once
#include <unordered_map>

#include "Scene.h"
#include "debug.h"

class CScenes
{
private:
	static CScenes* __instance;

	unordered_map<int, LPSCENE> scenes;
	int currentScene = -1;
	int nextScene = 1;
public:
	CScenes();

	void InitScenes(wstring filePath);

	LPSCENE GetCurrentScene();
	void SwitchScene();

	void InitiateSwitchScene(int id);


	static CScenes* GetInstance();

};

