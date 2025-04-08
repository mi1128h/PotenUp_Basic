#pragma once
#include "Singleton.h"
#include "config.h"

class GameObject;
class SceneManager : public Singleton<SceneManager>
{
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

public:
	HRESULT ChangeScene(string key);
	GameObject* AddScene(string key, GameObject* scene);

public:
	static GameObject* currentScene;
	static GameObject* loadingScene;
	static GameObject* nextScene;

private:
	map<string, GameObject*> mapScenes;
};

