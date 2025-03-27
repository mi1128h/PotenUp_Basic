#include "BulletFactory.h"

BulletFactory::~BulletFactory()
{
}

void BulletFactory::AddBullet(int cnt)
{
    int i = 0;
    while (i < cnt) {
        std::unique_ptr<Bullet>& bullet = GetBullet();
        
        InitBullet(bullet, i, cnt);
        
        i++;
    }
}

std::unique_ptr<Bullet>& BulletFactory::GetBullet()
{
    for (auto& bullet : bulletList) {
        if (bullet->IsLoaded()) return bullet;
    }

    std::unique_ptr<Bullet> newBullet = CreateBullet();
    bulletList.push_back(move(newBullet));
    return bulletList.back();
}

void BulletFactory::SetSpecialValues(float angle, float damage, float explodeTime, int bounceNum, float confettiLife)
{
    this->angle = angle;
    this->damage = damage;
}

void BulletFactory::Update()
{
    for (auto& bullet : bulletList) {
        bullet->Update();
    }
}

void BulletFactory::Render(HDC hdc)
{
    for (auto& bullet : bulletList) {
        bullet->Render(hdc);
    }
}

BasicBulletFactory::~BasicBulletFactory()
{
}

std::unique_ptr<Bullet> BasicBulletFactory::CreateBullet()
{
    return std::make_unique<Bullet>();
}

void BasicBulletFactory::InitBullet(std::unique_ptr<Bullet>& bullet, int cnt, int totalCnt)
{
    bullet->Init(position, angle, damage);
    bullet->SetValues(0, 360 / totalCnt * cnt, 0, 0);
    bullet->Fire();
}

void BasicBulletFactory::SetSpecialValues(float angle, float damage, float explodeTime, int bounceNum, float confettiLife)
{
    BulletFactory::SetSpecialValues(angle, damage, explodeTime, bounceNum, confettiLife);
}

BombBulletFactory::~BombBulletFactory()
{
}

std::unique_ptr<Bullet> BombBulletFactory::CreateBullet()
{
    return std::make_unique<BombBullet>();
}

void BombBulletFactory::InitBullet(std::unique_ptr<Bullet>& bullet, int cnt, int totalCnt)
{
    bullet->Init(position, angle, damage);
    bullet->SetValues(explodeTime, 360 / totalCnt * cnt, 0, 0);
    bullet->Fire();
}

void BombBulletFactory::SetSpecialValues(float angle, float damage, float explodeTime, int bounceNum, float confettiLife)
{
    BulletFactory::SetSpecialValues(angle, damage, explodeTime, bounceNum, confettiLife);
    this->explodeTime = explodeTime;
}

BounceBulletFactory::~BounceBulletFactory()
{
}

std::unique_ptr<Bullet> BounceBulletFactory::CreateBullet()
{
    return std::make_unique<BounceBullet>();
}

void BounceBulletFactory::InitBullet(std::unique_ptr<Bullet>& bullet, int cnt, int totalCnt)
{
    bullet->Init(position, angle, damage);
    bullet->SetValues(0, 360 / totalCnt * cnt, bounceNum, 0);
    bullet->Fire();
}

void BounceBulletFactory::SetSpecialValues(float angle, float damage, float explodeTime, int bounceNum, float confettiLife)
{
    BulletFactory::SetSpecialValues(angle, damage, explodeTime, bounceNum, confettiLife);
    this->bounceNum = bounceNum;
}

ConfettiBulletFactory::~ConfettiBulletFactory()
{
}

std::unique_ptr<Bullet> ConfettiBulletFactory::CreateBullet()
{
    return std::make_unique<ConfettiBullet>();
}

void ConfettiBulletFactory::InitBullet(std::unique_ptr<Bullet>& bullet, int cnt, int totalCnt)
{
    bullet->Init(position, angle, damage);
    bullet->SetValues(explodeTime, 360 / totalCnt * cnt, 0, confettiLife);
    bullet->Fire();
}

void ConfettiBulletFactory::SetSpecialValues(float angle, float damage, float explodeTime, int bounceNum, float confettiLife)
{
    BulletFactory::SetSpecialValues(angle, damage, explodeTime, bounceNum, confettiLife);
    this->explodeTime = explodeTime;
    this->confettiLife = confettiLife;
}
