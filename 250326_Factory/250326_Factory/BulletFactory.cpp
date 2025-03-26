#include "BulletFactory.h"
#include "Bullet.h"

BulletFactory::~BulletFactory()
{
	std::cout << "�Ҹ� ���丮�� �޸� �����ȴ�!!" << std::endl;
}

void BulletFactory::AddBullet()
{
	Bullet* bullet = CreateBullet();
	bulletList.push_back(bullet);
	bullet->Notice();
}

NormalBulletFactory::~NormalBulletFactory()
{
	std::cout << "�Ϲ� �Ҹ� ���丮�� �޸� �����ȴ�!!" << std::endl;
}

Bullet* NormalBulletFactory::CreateBullet()
{
	return new NormalBullet();
}

SignBulletFactory::~SignBulletFactory()
{
	std::cout << "���� �Ҹ� ���丮�� �޸� �����ȴ�!!" << std::endl;
}

Bullet* SignBulletFactory::CreateBullet()
{
	return new SignBullet();
}

LazerBulletFactory::~LazerBulletFactory()
{
	std::cout << "������ �Ҹ� ���丮�� �޸� �����ȴ�!!" << std::endl;
}

Bullet* LazerBulletFactory::CreateBullet()
{
	return new LazerBullet();
}
