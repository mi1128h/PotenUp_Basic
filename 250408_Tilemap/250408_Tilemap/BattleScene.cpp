#include "BattleScene.h"
#include "Image.h"
#include "EnemyManager.h"
#include "CommonFunction.h"

BattleScene::BattleScene()
{
}

BattleScene::~BattleScene()
{
}

HRESULT BattleScene::Init()
{
	SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);

	backGround = new Image();
	if (FAILED(backGround->Init(TEXT("Image/BackGround.bmp"), WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd,
			TEXT("Image/backGround.bmp 생성 실패"), TEXT("경고"), MB_OK);
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
	if(enemyManager) enemyManager->Update();
}

void BattleScene::Render(HDC hdc)
{
	if(backGround) backGround->Render(hdc);

	if(enemyManager) enemyManager->Render(hdc);
}
