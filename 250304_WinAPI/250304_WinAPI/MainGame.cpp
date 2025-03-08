#include "MainGame.h"
#include "Tank.h"

/*
	�ǽ�1. �̻��� �� �� ���
	�ǽ�2. �̻��� ������ ���
	�ǽ�3. ��ų��1 (360�� �̻���) ���
	�ǽ�4. ��ų��2 (��ü ��ȹ) ���
*/

void MainGame::Init()
{
	tank = new Tank();
	tank->Init();
}

void MainGame::Release()
{
	if (tank) {
		tank->Release();
		delete tank;
	}
}

void MainGame::Update()
{
	if(tank) tank->Update();
}

void MainGame::Render(HDC hdc)
{
	wsprintf(szText, L"Mouse X: %d, Y: %d", mousePosX, mousePosY);
	TextOut(hdc, 20, 160, szText, wcslen(szText));

	if(tank) tank->Render(hdc);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage) {
	case WM_CREATE:


		hTimer = (HANDLE)SetTimer(hWnd, 0, 100, NULL);

		break;
	case WM_TIMER:
		Update();

		InvalidateRect(g_hWnd, NULL, TRUE);
		break;

	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		case 'a': case 'A':
			tank->RotateBarrel(5);
			break;
		case 'd': case 'D':
			tank->RotateBarrel(-5);
			break;
		case VK_SPACE:
			tank->Skill(SkillType::None);
			break;
		case 'r': case 'R':
			tank->Skill(SkillType::Bomb);
			break;
		case 'e': case 'E':
			tank->Skill(SkillType::Bounce);
			break;
		}


		InvalidateRect(g_hWnd, NULL, TRUE);
		break;

	case WM_MOUSEMOVE:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);

		InvalidateRect(g_hWnd, NULL, TRUE);
		break;

	case WM_LBUTTONDOWN:

		InvalidateRect(g_hWnd, NULL, TRUE);
		break;

	case WM_PAINT:
		hdc = BeginPaint(g_hWnd, &ps);

		Render(hdc);

		EndPaint(g_hWnd, &ps);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 0);
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
