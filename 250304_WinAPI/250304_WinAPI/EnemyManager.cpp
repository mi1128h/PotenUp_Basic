#include "EnemyManager.h"
#include "Enemy.h"

void EnemyManager::Init()
{
	// 1. 배열
	enemies = new Enemy[10];
	for (int i = 0; i < 10; ++i) {
		enemies[i].Init(NULL);
	}
	
	// 2. vector
	/*
		push_back() 함수의 단점

	*/
	//for (int i = 0; i < 10; ++i) {
	//	enemyList.push_back(new Enemy());
	//	enemyList[i]->Init(NULL);
	//}

	enemyList.resize(10);
	for (int i = 0; i < 10; ++i) {
		enemyList[i] = new Enemy();
		enemyList[i]->Init(NULL);
	}
}

void EnemyManager::Release()
{
	for (Enemy* e : enemyList) {
		if(e) delete e;
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
	for (int i = 0; i < size; ++i) {
		enemyList.push_back(new Enemy());
		enemyList.back()->Init(NULL);
	}
}
