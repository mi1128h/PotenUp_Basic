#pragma once
#include <iostream>

class Bullet
{
public:
	Bullet() {}
	virtual ~Bullet() {}

	virtual void Move() = 0;	// 순수 가상 함수
	virtual void Notice() = 0;
};

class NormalBullet : public Bullet
{
public:
	NormalBullet() {}
	virtual ~NormalBullet() {}

private:
	virtual void Move() override;
	virtual void Notice() override;
};

class SignBullet : public Bullet
{
public:
	SignBullet() {}
	virtual ~SignBullet() {}

private:
	virtual void Move() override;
	virtual void Notice() override;
};

class LazerBullet : public Bullet
{
public:
	LazerBullet() {}
	virtual ~LazerBullet() {}

private:
	virtual void Move() override;
	virtual void Notice() override;
};