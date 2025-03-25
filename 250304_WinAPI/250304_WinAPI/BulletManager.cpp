#include "BulletManager.h"
#include "Bullet.h"

void BulletManager::Init()
{

}

void BulletManager::Release()
{
	for (int i = 0; i < vBullets.size(); ++i) {
		vBullets[i]->Release();
		delete vBullets[i];
		vBullets[i] = NULL;
	}
}

void BulletManager::Update()
{
	for (auto b : vBullets) {
		b->Update();
	}
}

void BulletManager::Render(HDC hdc)
{
	for (auto b : vBullets) {
		b->Render(hdc);
	}
}
