#pragma once
#include <iostream>

class Bullet
{
public:
	Bullet() {}
	virtual ~Bullet() {}

	virtual void Move() = 0;	// ���� ���� �Լ�
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

void NormalBullet::Move()
{
	std::cout << "�߻� ���� ������ �������� ���ư���~" << std::endl;
}

void NormalBullet::Notice()
{
	std::cout << "�Ϲ� �Ҹ��� ����Ǿ���." << std::endl;
}

void SignBullet::Move()
{
	std::cout << "���� ��� �׸��鼭 ���ư���~" << std::endl;
}

void SignBullet::Notice()
{
	std::cout << "���� �Ҹ��� ����Ǿ���." << std::endl;
}

void LazerBullet::Move()
{
	std::cout << "�߻� ��ġ���� ȭ�� ������ �������� 2�� ���� �����ȴ�." << std::endl;
}

void LazerBullet::Notice()
{
	std::cout << "������ �Ҹ��� ����Ǿ���." << std::endl;
}
