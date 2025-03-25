#include "EnemyManager.h"
#include "Enemy.h"

/*
	1. WinSizeX, Y 를 사막배경에 맞춰서 변경
	2. 백그라운드를 사막으로 변경
	3. 플레이어 (rocket.bmp) 구현
	4. 적 10마리 움직임 구현
	5. 미사일 매니저 구현 - 플레이어, 적 사용
	6. 적이 1마리씩 밑으로 돌격한다(중간에 미사일 1발 발사)
*/

void EnemyManager::Init()
{
	// 1. 배열
	//enemies = new Enemy[10];
	//for (int i = 0; i < 10; ++i) {
	//	enemies[i].Init(NULL);
	//}
	
	// 2. vector
	// push_back() 함수의 단점

	//for (int i = 0; i < 10; ++i) {
	//	enemyList.push_back(new Enemy());
	//	enemyList[i]->Init(NULL);
	//}

	enemyList.resize(10);
	for (int i = 0; i < 10; ++i) {
		enemyList[i] = new Enemy();
		enemyList[i]->Init(150.0f + 80.0f * (i % 5), 200.0f + 80.0f * (i / 5));
	}
}

void EnemyManager::Release()
{
	for (Enemy* e : enemyList) {
		e->Release();
		delete e;
	}
	enemyList.clear();	// capacity는 유지
}

void EnemyManager::Update()
{
	for (Enemy* e : enemyList) {
		e->Update();
	}
}

void EnemyManager::Render(HDC hdc)
{
	for (Enemy* e : enemyList) {
		e->Render(hdc);
	}
}

void EnemyManager::AddEnemy(int size)
{
	//for (int i = 0; i < size; ++i) {
	//	enemyList.push_back(new Enemy());
	//	enemyList.back()->Init(NULL);
	//}
}
