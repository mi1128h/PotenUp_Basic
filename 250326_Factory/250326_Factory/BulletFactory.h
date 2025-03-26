#pragma once
#include "Bullet.h"
#include <vector>


class BulletFactory
{
public:
	BulletFactory() {}
	virtual ~BulletFactory();

	void AddBullet();

private:
	std::vector<std::unique_ptr<Bullet>> bulletList;
	virtual std::unique_ptr<Bullet> CreateBullet() = 0;
};

class NormalBulletFactory : public BulletFactory
{
public:
	NormalBulletFactory() {}
	virtual ~NormalBulletFactory();

private:
	virtual std::unique_ptr<Bullet> CreateBullet() override;
};

class SignBulletFactory : public BulletFactory
{
public:
	SignBulletFactory() {}
	virtual ~SignBulletFactory();

private:
	virtual std::unique_ptr<Bullet> CreateBullet() override;
};

class LazerBulletFactory : public BulletFactory
{
public:
	LazerBulletFactory() {}
	virtual ~LazerBulletFactory();

private:
	virtual std::unique_ptr<Bullet> CreateBullet() override;
};