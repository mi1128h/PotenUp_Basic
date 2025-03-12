#pragma once
#include "GameObject.h"

class Tank;
class Enemy;
class RoundManager;
class MainGame : public GameObject
{
private:
	HDC hdc{};
	PAINTSTRUCT ps{};
	HANDLE hTimer{}, hTimer2;
	int mousePosX{}, mousePosY{};
	wchar_t szText[128]{};

	Tank* tank;
	vector<Enemy*> enemies;
	int nDeadEnemies;

	RoundManager* roundManager;

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void RenderInfo(HDC hdc);

	void CreateEnemy();
	void SetGuidedBulletsTarget();
	void RestartGame();
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

