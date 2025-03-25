#pragma once
#include "GameObject.h"

class Enemy;
class EnemyManager : public GameObject
{
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void AddEnemy(int size);

private:
	Enemy* enemies;
	vector<Enemy*> enemyList;
	wchar_t szText[128];
};

