#include "MainGame.h"
#include "CommonFunction.h"
#include "Image.h"
#include "Timer.h"
#include "TilemapTool.h"
#include "BattleScene.h"

HRESULT MainGame::Init()
{
	ImageManager::GetInstance()->Init();
	KeyManager::GetInstance()->Init();
	SceneManager::GetInstance()->Init();

	SceneManager::GetInstance()->AddScene("전투씬_1", new BattleScene());
	SceneManager::GetInstance()->AddScene("타일맵툴", new TilemapTool());
	SceneManager::GetInstance()->ChangeScene("타일맵툴");

	hdc = GetDC(g_hWnd);

	backBuffer = new Image();
	if (FAILED(backBuffer->Init(TILEMAPTOOL_X, TILEMAPTOOL_Y)))
	{
		MessageBox(g_hWnd, 
			TEXT("백버퍼 생성 실패"), TEXT("경고"), MB_OK);
	}
	
	tilemapTool = new TilemapTool();
	tilemapTool->Init();

	return S_OK;
}

void MainGame::Release()
{
	if (tilemapTool)
	{
		tilemapTool->Release();
		delete tilemapTool;
		tilemapTool = nullptr;
	}

	if (backBuffer)
	{
		backBuffer->Release();
		delete backBuffer;
		backBuffer = nullptr;
	}

	ReleaseDC(g_hWnd, hdc);

	KeyManager::GetInstance()->Release();
	ImageManager::GetInstance()->Release();
	SceneManager::GetInstance()->Release();
}

void MainGame::Update()
{
	SceneManager::GetInstance()->Update();
	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render()
{
	// 백버퍼에 먼저 복사
	HDC hBackBufferDC = backBuffer->GetMemDC();

	SceneManager::GetInstance()->Render(hBackBufferDC);

	wsprintf(szText, TEXT("Mouse X : %d, Y : %d"), g_ptMouse.x, g_ptMouse.y);
	TextOut(hBackBufferDC, 20, 60, szText, wcslen(szText));

	TimerManager::GetInstance()->Render(hBackBufferDC);

	// 백버퍼에 있는 내용을 메인 hdc에 복사
	backBuffer->Render(hdc);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'a': case 'A':
			SceneManager::GetInstance()->ChangeScene("전투씬_1");
			break;
		case 'd': case 'D':
			SceneManager::GetInstance()->ChangeScene("타일맵툴");
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);

		break;
	case WM_LBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		
		break;
	case WM_DESTROY:
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
