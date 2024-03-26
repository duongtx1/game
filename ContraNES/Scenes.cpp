#include "Scenes.h"
#include "Animations.h"
#include "Sprites.h"

#include "PlayScene.h"
#include "Keyboard.h"

#define MAX_SCENE_LINE 1024

CScenes* CScenes::__instance = NULL;

CScenes::CScenes()
{
	__instance = this;
}

void CScenes::InitScenes(wstring filePath)
{
	DebugOut(L"[INFO] Start loading Scenes from : \"%s\"\n", filePath);
	ifstream f;
	f.open(filePath);

	// current resource section flag
	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE)) {
		string line(str);
		if (line[0] == '#') continue;
		else {
			vector<string> tokens = split(line);
			size_t size = tokens.size();

			if (size < 2) return;
			int id = atoi(tokens[0].c_str());
			LPCWSTR path = ToLPCWSTR(tokens[1].c_str());

			scenes[id] = new CPlayScene(id, path);
			DebugOut(ToLPCWSTR(str));
		}
	}
	f.close();

	DebugOut(L"[INFO] Done loading Scenes from \"%s\"\n", filePath);
}

LPSCENE CScenes::GetCurrentScene()
{
	return scenes[currentScene];
}

void CScenes::SwitchScene()
{
	if (nextScene < 0 || nextScene == currentScene) return;

	DebugOut(L"[INFO] Switching to scene %d\n", nextScene);
	if (currentScene < 0 == false)
		scenes[currentScene]->Unload();

	//CTextures::GetInstance()->Clear();
	CSprites::GetInstance()->Clear();
	CAnimations::GetInstance()->Clear();

	currentScene = nextScene;
	scenes[nextScene]->Load();

	Keyboard::GetInstance()->SetKeyEventHandler(scenes[nextScene]->GetKeyEventHandler());
}

void CScenes::InitiateSwitchScene(int id)
{
	nextScene = id;
}

CScenes* CScenes::GetInstance()
{
	if (__instance == NULL) __instance = new CScenes();

	return __instance;
}
