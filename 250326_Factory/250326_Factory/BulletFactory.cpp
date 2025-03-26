#include "BulletFactory.h"

BulletFactory::~BulletFactory()
{
	std::cout << "�Ҹ� ���丮�� �޸� �����ȴ�!!" << std::endl;
}

void BulletFactory::AddBullet()
{
	std::unique_ptr<Bullet> bullet = CreateBullet();
	bullet->Notice();
	bulletList.push_back(move(bullet));
}

NormalBulletFactory::~NormalBulletFactory()
{
	std::cout << "�Ϲ� �Ҹ� ���丮�� �޸� �����ȴ�!!" << std::endl;
}

std::unique_ptr<Bullet> NormalBulletFactory::CreateBullet()
{
	return std::make_unique<NormalBullet>();
}

SignBulletFactory::~SignBulletFactory()
{
	std::cout << "���� �Ҹ� ���丮�� �޸� �����ȴ�!!" << std::endl;
}

std::unique_ptr<Bullet> SignBulletFactory::CreateBullet()
{
	return std::make_unique<SignBullet>();
}

LazerBulletFactory::~LazerBulletFactory()
{
	std::cout << "������ �Ҹ� ���丮�� �޸� �����ȴ�!!" << std::endl;
}

std::unique_ptr<Bullet> LazerBulletFactory::CreateBullet()
{
	return std::make_unique<LazerBullet>();
}
