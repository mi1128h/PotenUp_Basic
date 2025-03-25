#include "EnemyManager.h"
#include "Enemy.h"

/*
	1. WinSizeX, Y �� �縷��濡 ���缭 ����
	2. ��׶��带 �縷���� ����
	3. �÷��̾� (rocket.bmp) ����
	4. �� 10���� ������ ����
	5. �̻��� �Ŵ��� ���� - �÷��̾�, �� ���
	6. ���� 1������ ������ �����Ѵ�(�߰��� �̻��� 1�� �߻�)
*/

void EnemyManager::Init()
{
	// 1. �迭
	//enemies = new Enemy[10];
	//for (int i = 0; i < 10; ++i) {
	//	enemies[i].Init(NULL);
	//}
	
	// 2. vector
	// push_back() �Լ��� ����

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
	enemyList.clear();	// capacity�� ����
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
