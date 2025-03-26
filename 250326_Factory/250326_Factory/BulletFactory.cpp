#include "BulletFactory.h"
#include "Bullet.h"

BulletFactory::~BulletFactory()
{
	std::cout << "불릿 팩토리가 메모리 해제된다!!" << std::endl;
}

void BulletFactory::AddBullet()
{
	Bullet* bullet = CreateBullet();
	bulletList.push_back(bullet);
	bullet->Notice();
}

NormalBulletFactory::~NormalBulletFactory()
{
	std::cout << "일반 불릿 팩토리가 메모리 해제된다!!" << std::endl;
}

Bullet* NormalBulletFactory::CreateBullet()
{
	return new NormalBullet();
}

SignBulletFactory::~SignBulletFactory()
{
	std::cout << "사인 불릿 팩토리가 메모리 해제된다!!" << std::endl;
}

Bullet* SignBulletFactory::CreateBullet()
{
	return new SignBullet();
}

LazerBulletFactory::~LazerBulletFactory()
{
	std::cout << "레이저 불릿 팩토리가 메모리 해제된다!!" << std::endl;
}

Bullet* LazerBulletFactory::CreateBullet()
{
	return new LazerBullet();
}
