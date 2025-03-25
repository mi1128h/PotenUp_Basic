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

void BulletManager::Fire(BulletType type, FPOINT position, float damage)
{
	int fireSuccess{};
	switch (type) {
	case BulletType::Basic:
	{
		Bullet* bullet = GetBasicBullet();
		bullet->Init(position, 90);
		bullet->SetDamage(damage);
		bullet->Fire();
		break;
	}
	case BulletType::Bomb:
	{
		while (fireSuccess < 36)
		{
			BombBullet* bombBullet = GetBombBullet();
			bombBullet->Init(position, 90);
			bombBullet->SetDamage(damage);
			bombBullet->SetBombValues(10, 10 * fireSuccess);
			bombBullet->Fire();
			fireSuccess++;
		}
		break;
	}
	case BulletType::Bounce:
	{
		BounceBullet* bounceBullet = GetBounceBullet();
		bounceBullet->Init(position, 90);
		bounceBullet->SetDamage(damage);
		bounceBullet->SetBounceNum(5);
		bounceBullet->Fire();
		break;
	}
	case BulletType::Confetti:
	{
		while (fireSuccess < 60)
		{
			ConfettiBullet* confettiBullet = GetConfettiBullet();
			confettiBullet->Init(position, 90);
			confettiBullet->SetDamage(damage);
			confettiBullet->SetConfettiValues(5);
			confettiBullet->Fire();
			fireSuccess++;
		}
	}
		break;
	}
}

Bullet* BulletManager::GetBasicBullet()
{
	for (int i = 0; i < vBasics.size(); ++i) {
		if (vBasics[i]->IsLoaded()) {
			return vBasics[i];
		}
	}

	Bullet* bullet = new Bullet;
	vBullets.push_back(bullet);
	vBasics.push_back(bullet);

	return bullet;
}

BombBullet* BulletManager::GetBombBullet()
{
	for (int i = 0; i < vBombs.size(); ++i) {
		if (vBombs[i]->IsLoaded()) {
			return vBombs[i];
		}
	}

	BombBullet* bullet = new BombBullet;
	vBullets.reserve(vBullets.size() + 36);
	vBombs.reserve(vBombs.size() + 36);
	vBullets.push_back(bullet);
	vBombs.push_back(bullet);

	return bullet;
}

BounceBullet* BulletManager::GetBounceBullet()
{
	for (int i = 0; i < vBounces.size(); ++i) {
		if (vBounces[i]->IsLoaded()) {
			return vBounces[i];
		}
	}

	BounceBullet* bullet = new BounceBullet;
	vBullets.push_back(bullet);
	vBounces.push_back(bullet);

	return bullet;
}

ConfettiBullet* BulletManager::GetConfettiBullet()
{
	for (int i = 0; i < vConfettis.size(); ++i) {
		if (vConfettis[i]->IsLoaded()) {
			return vConfettis[i];
		}
	}

	ConfettiBullet* bullet = new ConfettiBullet;
	vBullets.reserve(vBullets.size() + 60);
	vConfettis.reserve(vConfettis.size() + 60);
	vBullets.push_back(bullet);
	vConfettis.push_back(bullet);

	return bullet;
}
