#include "Enemy.h"
#include "CommonFunction.h"
#include "Tank.h"

void Enemy::Init(Tank* tank)
{
	position.x = uid_0_WINSIZEX(dre);
	position.y = 50;
	target = tank;
	hp = 1;
	size = 20;
	speed = 10;
	damage = 3;
}

void Enemy::Release()
{
}

void Enemy::Update()
{
	if (hp <= 0) return;

	Move();
}

void Enemy::Render(HDC hdc)
{
	if (hp <= 0) return;
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	RenderEllipseAtCenter(hdc, position.x, position.y, size, size);
	
	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);
}

void Enemy::Move()
{
	POINT targetPos = target->GetPos();
	float dx = targetPos.x - position.x;
	float dy = targetPos.y - position.y;
	float moveAngle = atan2f(dy, dx);

	position.x += cosf(moveAngle) * speed;
	position.y += sinf(moveAngle) * speed;
}
