#include "SceneManager.h"
#include "GameObject.h"

GameObject* SceneManager::currentScene = nullptr;
GameObject* SceneManager::loadingScene = nullptr;
GameObject* SceneManager::nextScene = nullptr;

void SceneManager::Init()
{
}

void SceneManager::Release()
{
    for (auto& sceneData : mapScenes)
    {
        if (sceneData.second)
        {
            sceneData.second->Release();
            delete sceneData.second;
            sceneData.second = nullptr;
        }
    }
    mapScenes.clear();
    ReleaseInstance();
}

void SceneManager::Update()
{
    if (currentScene)
    {
        currentScene->Update();
    }
}

void SceneManager::Render(HDC hdc)
{
    if (currentScene)
    {
        currentScene->Render(hdc);
    }
}

HRESULT SceneManager::ChangeScene(string key)
{
    auto iter = mapScenes.find(key); // nextScene
    if (iter == mapScenes.end()) return E_FAIL;
    if (iter->second == currentScene) return S_OK;

    if (SUCCEEDED(iter->second->Init()))
    {
        if (currentScene)
        {
            currentScene->Release();
        }
        currentScene = iter->second;
        return S_OK;
    }
    return E_FAIL;
}

GameObject* SceneManager::AddScene(string key, GameObject* scene)
{
    if (!scene) return nullptr;

    auto iter = mapScenes.find(key);
    if (iter != mapScenes.end())
    {
        return iter->second;
    }

    mapScenes.insert(make_pair(key, scene));

    return scene;
}
