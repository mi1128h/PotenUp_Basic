#include "Bullet.h"

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
