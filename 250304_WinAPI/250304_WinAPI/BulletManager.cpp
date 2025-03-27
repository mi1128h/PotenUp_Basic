#include "BulletManager.h"
#include "BulletFactory.h"

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
}

void BulletManager::Init()
{
	bulletFactoryList[(int)BulletType::Basic] = std::make_unique<BasicBulletFactory>();
	bulletFactoryList[(int)BulletType::Bomb] = std::make_unique<BombBulletFactory>();
	bulletFactoryList[(int)BulletType::Bounce] = std::make_unique<BounceBulletFactory>();
	bulletFactoryList[(int)BulletType::Confetti] = std::make_unique<ConfettiBulletFactory>();
}

void BulletManager::Release()
{
}

void BulletManager::Update()
{
	for (auto& bf : bulletFactoryList) {
		bf->Update();
	}
}

void BulletManager::Render(HDC hdc)
{
	for (auto& bf : bulletFactoryList) {
		bf->Render(hdc);
	}
}

void BulletManager::SetBulletValues(float angle, float damage, float explodeTime, int bounceNum, float confettiLife)
{
	for (auto& bf : bulletFactoryList) {
		bf->SetSpecialValues(angle, damage, explodeTime, bounceNum, confettiLife);
	}
}

void BulletManager::Fire(BulletType type, FPOINT position)
{
	bulletFactoryList[(int)type]->UpdateFirePosition(position);

	switch (type) {
	case BulletType::Basic:
	{
		bulletFactoryList[(int)type]->AddBullet(1);
		break;
	}
	case BulletType::Bomb:
	{
		bulletFactoryList[(int)type]->AddBullet(36);
		break;
	}
	case BulletType::Bounce:
	{
		bulletFactoryList[(int)type]->AddBullet(1);
		break;
	}
	case BulletType::Confetti:
	{
		bulletFactoryList[(int)type]->AddBullet(60);
		break;
	}
	}
}