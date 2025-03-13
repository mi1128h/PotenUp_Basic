#include "MainGame.h"
#include "Tank.h"
#include "Enemy.h"
#include "RoundManager.h"
#include "CommonFunction.h"
#include "Image.h"

/*
	실습1. 적 클래스 생성 (화면 밖, 랜덤 위치)
	실습2. 적은 탱크를 향해 다가온다.
	실습3. 미사일 - 적, 적 - 탱크 충돌 처리
	실습4. 5번째 미사일마다 유도미사일 발사
			가장 가까운 적을 따라 가서 맞춘다
*/

void MainGame::Init()
{
	tank = new Tank();
	tank->Init();

	roundManager = new RoundManager();
	roundManager->Init();

	iori = new Image();
	if (FAILED(iori->Init(L"Image/iori_walk.bmp", 612, 104))) {
		MessageBox(g_hWnd, L"파일 로드에 실패", L"경고", MB_OK);
	}
}

void MainGame::Release()
{
	if (tank) {
		tank->Release();
		delete tank;
	}
	for (auto e : enemies) {
		if (e) delete e;
	}
	Enemy::ReleaseBullets();

	if (roundManager) delete roundManager;

	if (iori) {
		iori->Release();
		delete iori;
		iori = NULL;
	}
}

void MainGame::Update()
{
	if (roundManager) {
		if (roundManager->IsGameOver()) return;
	}
	if (tank) tank->Update();

	int deadNum{};
	for (auto e : enemies) {
		if (e) {
			e->Update();
			if (e->IsDead()) deadNum++;
			else {
				tank->CheckCollideEnemy(e);
			}
		}
	}
	nDeadEnemies = deadNum;

	Enemy::UpdateBullets();
	if (tank) Enemy::CheckBulletsCollision(tank);

	SetGuidedBulletsTarget();

	roundManager->CheckGameOver(tank->GetHp());

	if (nDeadEnemies == enemies.size() and !roundManager->canCreateEnemy()) {
		roundManager->setIsClear(true);
	}

	bool newRound = false;
	if (!roundManager->IsGameClear()) {
		newRound = roundManager->IsNewRound();
	}

	if (newRound) {
		tank->Init();
	}

	if (roundManager->IsGameClear()) {
		tank->Skill(SkillType::Confetti);
	}

	idx++;
	idx %= 9;
}

void MainGame::Render(HDC hdc)
{
	if (roundManager)
		if (roundManager->IsGameOver()) return;
	wsprintf(szText, L"Mouse X: %d, Y: %d", mousePosX, mousePosY);
	TextOut(hdc, 20, 160, szText, wcslen(szText));

	if (tank) tank->Render(hdc);
	for (auto e : enemies)
		if (e) e->Render(hdc);
	Enemy::RenderBullets(hdc);
	
	if (iori) {
		iori->Render(hdc, 100, 100, idx);
	}
}

void MainGame::RenderInfo(HDC hdc)
{
	SetBkMode(hdc, TRANSPARENT);
	if (roundManager) {
		wsprintf(szText, L"Round: %d", roundManager->getCurrentRound());
		TextOut(hdc, 20, 20, szText, wcslen(szText));

		HFONT hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, L"Arial");
		HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

		if (roundManager->IsGameClear()) {
			wsprintf(szText, L"Clear");
			TextOut(hdc, WINSIZE_X / 2 - wcslen(szText) / 2 * 25, WINSIZE_Y / 2 - 25, szText, wcslen(szText));
		}
		else if (roundManager->IsGameOver()) {
			wsprintf(szText, L"Game Over");
			TextOut(hdc, WINSIZE_X / 2 - wcslen(szText) / 2 * 25, WINSIZE_Y / 2 - 25, szText, wcslen(szText));
		}

		if (roundManager->IsGameClear() or roundManager->IsGameOver())
		{
			wsprintf(szText, L"Press enter to restart");
			TextOut(hdc, WINSIZE_X / 2 - wcslen(szText) / 2 * 25 + 50, WINSIZE_Y / 2 + 100, szText, wcslen(szText));
			wsprintf(szText, L"Press esc to quit");
			TextOut(hdc, WINSIZE_X / 2 - wcslen(szText) / 2 * 25 + 30, WINSIZE_Y / 2 + 150, szText, wcslen(szText));
		}

		SelectObject(hdc, oldFont);
		DeleteObject(hFont);
	}

	// y 180~
	if (roundManager)
		if (!roundManager->IsGameOver())
			tank->RenderInfo(hdc);
}

void MainGame::CreateEnemy()
{
	if (!tank) return;
	if (!roundManager) return;
	if (roundManager->IsGameOver()) return;
	if (!roundManager->canCreateEnemy()) return;

	float hp = roundManager->getEnemyHp();
	int maxBulletNum = roundManager->getBulletNum();
	float enemySpeed = roundManager->getEnemySpeed();
	float enemySize = roundManager->getEnemySize();
	int fireSpeed = roundManager->getFireInterval();
	float bulletSpeed = roundManager->getBulletSpeed();

	if (nDeadEnemies > 0) {
		for (int i = 0; i < enemies.size(); ++i) {
			if (enemies[i]->IsDead()) {
				enemies[i]->Init(tank);
				enemies[i]->SetValuesByRound(hp, maxBulletNum, enemySpeed, enemySize, fireSpeed, bulletSpeed);
				nDeadEnemies--;
				break;
			}
		}
	}
	else {
		Enemy* enemy = new Enemy;
		enemy->Init(tank);
		enemy->SetValuesByRound(hp, maxBulletNum, enemySpeed, enemySize, fireSpeed, bulletSpeed);
		enemies.push_back(enemy);
	}

	roundManager->IncEnemyCnt();
}

void MainGame::SetGuidedBulletsTarget()
{
	if (!tank) return;
	tank->SetBulletsTarget(enemies);
}

void MainGame::RestartGame()
{
	tank->Init();
	for (auto e : enemies)
	{
		e->Init(tank);
	}
	Enemy::InitLoadedBullets();
	roundManager->Init();
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage) {
	case WM_CREATE:
		hTimer = (HANDLE)SetTimer(hWnd, 0, 100, NULL);
		hTimer2 = (HANDLE)SetTimer(hWnd, 1, 3000, NULL);

		break;
	case WM_TIMER:
		switch (wParam) {
		case 0:
			Update();
			break;

		case 1:
			CreateEnemy();
			break;
		}

		InvalidateRect(g_hWnd, NULL, TRUE);
		break;

	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			if (roundManager->IsGameOver() or roundManager->IsGameClear())
			{
				KillTimer(hWnd, 0);
				KillTimer(hWnd, 1);
				Release();
				PostQuitMessage(0);
			}
			break;
		case 'a': case 'A':
			tank->RotateBarrel(5);
			break;
		case 'd': case 'D':
			tank->RotateBarrel(-5);
			break;
		case VK_SPACE:
			tank->Skill(SkillType::Basic);
			break;
		case 'r': case 'R':
			tank->Skill(SkillType::Bomb);
			break;
		case 'e': case 'E':
			tank->Skill(SkillType::Bounce);
			break;
		case VK_LEFT:
		case VK_RIGHT:
		case VK_UP:
		case VK_DOWN:
			tank->ProccessMoveInput(wParam);
			break;
		case VK_RETURN:
			if (roundManager->IsGameOver() or roundManager->IsGameClear())
			{
				RestartGame();
			}
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
		RenderInfo(hdc);

		EndPaint(g_hWnd, &ps);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 0);
		KillTimer(hWnd, 1);
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
