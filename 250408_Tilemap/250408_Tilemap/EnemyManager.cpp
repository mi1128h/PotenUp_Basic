#include "EnemyManager.h"
#include "Enemy.h"

// 1. WinSizeX, Y�� �縷��濡 ���缭 ����
// 2. ��׶��带 �縷���� ����
// 3. �÷��̾� (rocket.bmp) ����
// 4. �� 10���� �¿� ������ ����
// 5. �̻��� �Ŵ��� ���� - �÷��̾ ���, �� ���
// 6. ���� 1������ ������ �����Ѵ�. (�߰��� �̻��� 1�� �߻�)

HRESULT EnemyManager::Init()
{
	// 1. �迭
	//enemys = new Enemy[10];
	//for (int i = 0; i < 10; i++)
	//{
	//	enemys[i].Init();
	//}

	// 2. vector
	/*
		push_back() �Լ��� ���� : 
	*/
	//for (int i = 0; i < 10; i++)
	//{
	//	vecEnemys.push_back(new Enemy);
	//	vecEnemys[i]->Init();
	//}

	vecEnemys.resize(10);
	for (int i = 0; i < 10; i++)
	{
		vecEnemys[i] = new Enemy();
		vecEnemys[i]->Init(310.0f + 130.0f * (i % 5) , 
			80.0f + 90.0f * (i / 5));
	}

	return S_OK;
}

void EnemyManager::Release()
{
	for (int i = 0; i < 10; i++)
	{
		vecEnemys[i]->Release();
		delete vecEnemys[i];
	}
	vecEnemys.clear();	// ���Ұ� ��� ���ŵǰ� capacity�� �����ȴ�.
}

void EnemyManager::Update()
{
	for (int i = 0; i < vecEnemys.size(); i++)
	{
		vecEnemys[i]->Update();
	}
}

void EnemyManager::Render(HDC hdc)
{
	for (int i = 0; i < vecEnemys.size(); i++)
	{
		vecEnemys[i]->Render(hdc);
	}
}

void EnemyManager::AddEnemy(int size)
{
	for (int i = 0; i < size; i++)
	{
		vecEnemys.push_back(new Enemy());
		vecEnemys.back()->Init();
	}
}
