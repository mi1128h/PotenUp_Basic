#include "BattleScene.h"
#include "Image.h"
#include "EnemyManager.h"
#include "CommonFunction.h"

HRESULT BattleScene::Init()
{
	SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);

	backGround = new Image();
	if (FAILED(backGround->Init(TEXT("Image/BackGround.bmp"), WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd,
			TEXT("Image/backGround.bmp ���� ����"), TEXT("���"), MB_OK);
		return E_FAIL;
	}

	enemyManager = new EnemyManager();
	enemyManager->Init();

	return S_OK;
}

void BattleScene::Release()
{
	if (enemyManager)
	{
		enemyManager->Release();
		delete enemyManager;
		enemyManager = nullptr;
	}

	if (backGround)
	{
		backGround->Release();
		delete backGround;
		backGround = nullptr;
	}
}

void BattleScene::Update()
{
	enemyManager->Update();
}

void BattleScene::Render(HDC hdc)
{
	backGround->Render(hdc);
	enemyManager->Render(hdc);
}
