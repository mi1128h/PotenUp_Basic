#include "BulletFactory.h"
#include "Bullet.h"

void BulletFactory::AddBullet()
{
	Bullet* bullet = CreateBullet();
	bulletList.push_back(bullet);
	bullet->Notice();
}

Bullet* NormalBulletFactory::CreateBullet()
{
	return new NormalBullet();
}

Bullet* SignBulletFactory::CreateBullet()
{
	return new SignBullet();
}

Bullet* LazerBulletFactory::CreateBullet()
{
	return new LazerBullet();
}
