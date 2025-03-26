#include "BulletFactory.h"

BulletFactory::~BulletFactory()
{
	std::cout << "불릿 팩토리가 메모리 해제된다!!" << std::endl;
}

void BulletFactory::AddBullet()
{
	std::unique_ptr<Bullet> bullet = CreateBullet();
	bullet->Notice();
	bulletList.push_back(move(bullet));
}

NormalBulletFactory::~NormalBulletFactory()
{
	std::cout << "일반 불릿 팩토리가 메모리 해제된다!!" << std::endl;
}

std::unique_ptr<Bullet> NormalBulletFactory::CreateBullet()
{
	return std::make_unique<NormalBullet>();
}

SignBulletFactory::~SignBulletFactory()
{
	std::cout << "사인 불릿 팩토리가 메모리 해제된다!!" << std::endl;
}

std::unique_ptr<Bullet> SignBulletFactory::CreateBullet()
{
	return std::make_unique<SignBullet>();
}

LazerBulletFactory::~LazerBulletFactory()
{
	std::cout << "레이저 불릿 팩토리가 메모리 해제된다!!" << std::endl;
}

std::unique_ptr<Bullet> LazerBulletFactory::CreateBullet()
{
	return std::make_unique<LazerBullet>();
}
