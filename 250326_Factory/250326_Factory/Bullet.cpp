#include "Bullet.h"

void NormalBullet::Move()
{
	std::cout << "발사 시점 각도로 직선으로 날아간다~" << std::endl;
}

void NormalBullet::Notice()
{
	std::cout << "일반 불릿이 생산되었다." << std::endl;
}

void SignBullet::Move()
{
	std::cout << "사인 곡선을 그리면서 날아간다~" << std::endl;
}

void SignBullet::Notice()
{
	std::cout << "사인 불릿이 생산되었다." << std::endl;
}

void LazerBullet::Move()
{
	std::cout << "발사 위치부터 화면 끝까지 일직선이 2초 동안 유지된다." << std::endl;
}

void LazerBullet::Notice()
{
	std::cout << "레이저 불릿이 생산되었다." << std::endl;
}
