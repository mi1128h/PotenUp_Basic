#include "LoadingScene.h"
#include "Image.h"

HRESULT LoadingScene::Init()
{
    bg = ImageManager::GetInstance()->AddImage("�ε�_1", L"image/loading.bmp", 852, 480);
    return S_OK;
}

void LoadingScene::Release()
{
}

void LoadingScene::Update()
{
}

void LoadingScene::Render(HDC hdc)
{
    if (bg) bg->Render(hdc);
}
