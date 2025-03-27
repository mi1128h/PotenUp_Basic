#include "MainGame.h"
#include "Tank.h"
#include "Enemy.h"
#include "RoundManager.h"
#include "CommonFunction.h"
#include "Image.h"
#include "AnimCharacter.h"
#include "AnimBackground.h"
#include "EnemyManager.h"
#include "Rocket.h"

void MainGame::Init()
{
	hdc = GetDC(g_hWnd);

	KeyManager::GetInstance()->Init();

	backBuffer = new Image();
	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y))) {
		MessageBox(g_hWnd, L"backBuffer 생성 실패", L"경고", MB_OK);
	}

	background = new AnimBackground();
	background->Init();

	enemyManager = new EnemyManager;
	enemyManager->Init();

	rocket = new Rocket;
	rocket->Init();
}

void MainGame::Release()
{
	if (enemyManager) {
		enemyManager->Release();
		delete enemyManager;
		enemyManager = NULL;
	}

	if (rocket) {
		rocket->Release();
		delete rocket;
		rocket = NULL;
	}

	if (backBuffer) {
		backBuffer->Release();
		delete backBuffer;
		backBuffer = NULL;
	}

	KeyManager* km = KeyManager::GetInstance();
	if (km) km->Release();

	ImageManager* im = ImageManager::GetInstance();
	if (im) im->Release();
}

void MainGame::Update()
{
	if (enemyManager) {
		enemyManager->Update();
		enemyManager->SetTargetPoint(rocket->GetPos());
	}
	if (rocket) rocket->Update();
	if (background) background->Update();
}

void MainGame::Render()
{
	if (!backBuffer) return;
	// 백버퍼에 복사
	HDC hBackBufferDC = backBuffer->GetMemDC();
	BitBlt(hBackBufferDC, 0, 0, WINSIZE_X, WINSIZE_Y, hdc, 0, 0, WHITENESS);

	if (background) {
		background->Render(hBackBufferDC);
	}

	if (enemyManager) enemyManager->Render(hBackBufferDC);
	if (rocket) rocket->Render(hBackBufferDC);

	// 백버퍼에 있는 내용을 메인 hdc에 복사
	backBuffer->Render(hdc);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage) {
	case WM_MOUSEMOVE:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);
		break;

	case WM_DESTROY:
		Release();
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}
