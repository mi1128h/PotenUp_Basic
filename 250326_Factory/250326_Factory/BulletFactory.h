#pragma once
#include <vector>

class Bullet;
class BulletFactory
{
public:
	BulletFactory() {}
	virtual ~BulletFactory() {}

	void AddBullet();

private:
	std::vector<Bullet*> bulletList;
	virtual Bullet* CreateBullet() = 0;
};

class NormalBulletFactory : public BulletFactory
{
public:
	NormalBulletFactory() {}
	virtual ~NormalBulletFactory() {}

private:
	virtual Bullet* CreateBullet() override;
};

class SignBulletFactory : public BulletFactory
{
public:
	SignBulletFactory() {}
	virtual ~SignBulletFactory() {}

private:
	virtual Bullet* CreateBullet() override;
};

class LazerBulletFactory : public BulletFactory
{
public:
	LazerBulletFactory() {}
	virtual ~LazerBulletFactory() {}

private:
	virtual Bullet* CreateBullet() override;
};