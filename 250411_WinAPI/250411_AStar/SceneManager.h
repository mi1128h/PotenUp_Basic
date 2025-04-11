#pragma once
#include "Singleton.h"
#include "config.h"

class GameObject;
class SceneManager : public Singleton<SceneManager>
{
private:
	map<string, GameObject*> mapScenes;

public:
	static GameObject* currentScene;
	static GameObject* loadingScene;
	static GameObject* nextScene;

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	HRESULT ChangeScene(string key);
	GameObject* AddScene(string key, GameObject* scene);
};

